import java.util.ArrayList;
import java.util.LinkedList;

public class L025 {

    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int ele) {
            this.val = ele;
            this.left = null;
            this.right = null;
        }

        TreeNode() {
            this.val = 0;
            this.left = null;
            this.right = null;
        }

    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {

        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,-1 };
        TreeNode root = constructTree(arr);
        display(root);
        levelOrder(root);
        // view(root);
    }

    public static int idx = 0;

    public static TreeNode constructTree(int[] arr) {

        if (arr[idx] == -1) {
            idx++;
            return null;

        }

        TreeNode root = new TreeNode(arr[idx]);
        idx++;
        root.left = constructTree(arr);
        root.right = constructTree(arr);

        return root;
    }

    public static void display(TreeNode root) {
        if (root == null) {
            return;
        }

        String str = "";

        str = str + (root.left == null ? "." : root.left.val);
        str = str + " <- " + root.val + " -> ";
        str = str + (root.right == null ? "." : root.right.val);

        System.out.println(str);

        display(root.left);
        display(root.right);

        return;
    }

    public static void levelOrder(TreeNode root) {
        // levelOrder01(root);
        // levelOrder02(root);
        // levelOrder03(root);
        // levelOrder04(root);
        // verticalOrder(root);
        // System.out.println();
        // verticalOrderSum(root);
    }

    public static void view(TreeNode root) {
        ArrayList<Integer> al;

        al = leftview(root);
        System.out.println(al);

        // al=rightview(root);
        // System.out.println(al);

        // al=verticalview(root);
        // System.out.println(al);

    }

    // levelorder.============================================================================

    public static void levelOrder01(TreeNode root) {

        LinkedList<TreeNode> q = new LinkedList<>();
        q.addLast(root);

        while (!q.isEmpty()) {
            TreeNode rvtx = q.getFirst();
            q.removeFirst();
            System.out.print(rvtx.val + " , ");
            if (rvtx.left != null)
                q.addLast(rvtx.left);
            if (rvtx.right != null)
                q.addLast(rvtx.right);
        }
        return;
    }

    public static void levelOrder02(TreeNode root) {
        LinkedList<TreeNode> q1 = new LinkedList<>();
        LinkedList<TreeNode> q2 = new LinkedList<>();
        q1.addLast(root);

        int count = 0;
        System.out.print("Level " + count + " -> ");

        while (!q1.isEmpty()) {
            TreeNode rvtx = q1.getFirst();
            q1.removeFirst();

            System.out.print(rvtx.val + " , ");
            if (rvtx.left != null)
                q2.addLast(rvtx.left);
            if (rvtx.right != null)
                q2.addLast(rvtx.right);

            if (q1.isEmpty()) {
                LinkedList<TreeNode> temp = new LinkedList<>();
                temp = q2;
                q2 = q1;
                q1 = temp;
                count++;
                System.out.println();
                System.out.print("Level " + count + " -> ");
            }
        }
        return;

    }

    public static void levelOrder03(TreeNode root) {

        LinkedList<TreeNode> q = new LinkedList<>();
        q.addLast(root);
        q.addLast(null);

        int count = 0;
        System.out.print("Level " + count + " -> ");

        while (q.size() != 1) {
            TreeNode rvtx = q.getFirst();
            q.removeFirst();

            System.out.print(rvtx.val + " , ");
            if (rvtx.left != null)
                q.addLast(rvtx.left);
            if (rvtx.right != null)
                q.addLast(rvtx.right);

            if (q.getFirst() == null) {
                q.removeFirst();
                q.addLast(null);
                count++;
                System.out.println();
                System.out.print("Level " + count + " -> ");
            }
        }
        return;
    }

    public static void levelOrder04(TreeNode root) {

        LinkedList<TreeNode> q = new LinkedList<>();
        q.addLast(root);

        int level = 0;

        while (q.size() != 0) {

            int cursize = q.size();
            System.out.print("Level: " + level + " -> ");

            while (cursize-- > 0) {

                TreeNode rvtx = q.removeFirst();
                System.out.print(rvtx.val + ",");
                if (rvtx.left != null)
                    q.addLast(rvtx.left);
                if (rvtx.right != null)
                    q.addLast(rvtx.right);

            }
            level++;
            System.out.println();
        }
    }

    public static int leftmax = 0;
    public static int rightmax = 0;

    public static void findWidth(TreeNode root, int level) {
        if (root == null) {
            return;
        }

        findWidth(root.left, level - 1);
        findWidth(root.right, level + 1);

        leftmax = Math.min(leftmax, level);
        rightmax = Math.max(rightmax, level);

    }

    public static class VOpair {

        TreeNode t;
        Integer i;

        VOpair(TreeNode t1, Integer i1) {
            this.t = t1;
            this.i = i1;
        }
    }

    public static void verticalOrder(TreeNode root) {
        
        leftmax = 0;
        rightmax = 0;
        findWidth(root, 0);

        int size = rightmax - leftmax + 1;
        ArrayList<TreeNode>[] arr = new ArrayList[size];

        for (int i = 0; i < size; i++) {
            arr[i] = new ArrayList<TreeNode>();
        }

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmax));

        while (!q.isEmpty()) {

            VOpair rvtx = q.getFirst();
            q.removeFirst();

            arr[rvtx.i].add(rvtx.t);

            if (rvtx.t.left != null)
                q.addLast(new VOpair(rvtx.t.left, rvtx.i - 1));
            if (rvtx.t.right != null)
                q.addLast(new VOpair(rvtx.t.right, rvtx.i + 1));
        }

        for (int i = 0; i < size; i++) {
            ArrayList<TreeNode> al = arr[i];
            System.out.print("level " + i + " -> ");
            for (TreeNode t : al) {
                System.out.print(t.val + " , ");
            }
            System.out.println();
        }
    }

    public static void verticalOrderSum(TreeNode root) {
        leftmax = 0;
        rightmax = 0;
        findWidth(root, 0);

        int size = rightmax - leftmax + 1;
        int[] arr = new int[size];

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmax));

        while (!q.isEmpty()) {

            VOpair rvtx = q.getFirst();
            q.removeFirst();

            arr[rvtx.i] += rvtx.t.val;

            if (rvtx.t.left != null)
                q.addLast(new VOpair(rvtx.t.left, rvtx.i - 1));
            if (rvtx.t.right != null)
                q.addLast(new VOpair(rvtx.t.right, rvtx.i + 1));
        }

        for (int i = 0; i < size; i++) {

            System.out.println("level " + i + " -> " + arr[i]);

        }
    }

    // view.==========================================================================

    public static ArrayList<Integer> leftview(TreeNode root) {
        ArrayList<Integer> ans = new ArrayList<>();
        if (root == null)
            return ans;

        LinkedList<TreeNode> q = new LinkedList<>();
        q.add(root);

        while (q.size() != 0) {
            int cursize = q.size();
            ans.add(q.peekFirst().val);

            while (cursize-- > 0) {
                TreeNode rvtx = q.poll();

                if (rvtx.left != null)
                    q.addLast(rvtx.left);
                if (rvtx.right != null)
                    q.addLast(rvtx.right);
            }
        }

        return ans;
    }

    public static void rightview(TreeNode root) {

        LinkedList<TreeNode> q = new LinkedList<>();

        q.addLast(root);
        TreeNode prev = null;

        while (q.size() != 0) {

            int cursize = q.size();

            while (cursize-- > 0) {

                TreeNode rvtx = q.removeFirst();

                if (rvtx.left != null)
                    q.addLast(rvtx.left);
                if (rvtx.right != null)
                    q.addLast(rvtx.right);
                prev = rvtx;
            }
            System.out.println(prev.val);
        }

    }

    public static void verticalview(TreeNode root) {
        leftmax = 0;
        rightmax = 0;
        findWidth(root, 0);

        int size = rightmax - leftmax + 1;
        ArrayList<TreeNode>[] arr = new ArrayList[size];

        for (int i = 0; i < size; i++) {
            arr[i] = new ArrayList<TreeNode>();
        }

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmax));

        while (!q.isEmpty()) {

            VOpair rvtx = q.getFirst();
            q.removeFirst();

            arr[rvtx.i].add(rvtx.t);

            if (rvtx.t.right != null)
                q.addLast(new VOpair(rvtx.t.right, rvtx.i + 1));
            if (rvtx.t.left != null)
                q.addLast(new VOpair(rvtx.t.left, rvtx.i - 1));

        }

        for (int i = 0; i < size; i++) {
            ArrayList<TreeNode> al = arr[i];
            System.out.println("level " + i + " -> " + al.get(0).val);
        }
    }

}