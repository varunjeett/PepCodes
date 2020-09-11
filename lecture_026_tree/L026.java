import java.util.ArrayList;
import java.util.LinkedList;

import java.util.Arrays;

public class L026 {

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

    public static class VOpair {

        TreeNode t;
        int level;

        VOpair(TreeNode t1, int level1) {
            this.t = t1;
            this.level = level1;
        }

    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {

        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1 };
        TreeNode root = constructTree(arr);
        display(root);
        view(root);

    }

    public static void view(TreeNode root) {

        // topView(root);
        // bottomView(root);
        DiagonalView(root);
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

    public static int leftmax = 0;
    public static int rightmax = 0;

    public static void width(TreeNode root, int level) {

        if (root == null) {
            return;
        }

        width(root.left, level - 1);
        width(root.right, level + 1);

        leftmax = Math.min(leftmax, level);

        rightmax = Math.max(rightmax, level);

    }

    public static void topView(TreeNode root) {

        leftmax = 0;
        rightmax = 0;

        width(root, 0);

        int[] arr = new int[rightmax - leftmax + 1];

        for (int i = 0; i < arr.length; i++) {
            arr[i] = (int) -1e8;
        }

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmax));

        while (q.size() != 0) {

            int cursize = q.size();

            while (cursize-- > 0) {

                VOpair rvtx = q.removeFirst();

                if (arr[rvtx.level] == (int) -1e8) {
                    arr[rvtx.level] = rvtx.t.val;
                }

                if (rvtx.t.left != null)
                    q.addLast(new VOpair(rvtx.t.left, rvtx.level - 1));
                if (rvtx.t.right != null)
                    q.addLast(new VOpair(rvtx.t.right, rvtx.level + 1));
            }
        }

        for (int ele : arr) {
            System.out.println(ele);
        }

        return;

    }

    public static void bottomView(TreeNode root) {

        leftmax = 0;
        rightmax = 0;

        width(root, 0);

        int[] arr = new int[rightmax - leftmax + 1];

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmax));

        while (q.size() != 0) {

            int cursize = q.size();

            while (cursize-- > 0) {

                VOpair rvtx = q.removeFirst();

                arr[rvtx.level] = rvtx.t.val;

                if (rvtx.t.left != null)
                    q.addLast(new VOpair(rvtx.t.left, rvtx.level - 1));
                if (rvtx.t.right != null)
                    q.addLast(new VOpair(rvtx.t.right, rvtx.level + 1));
            }
        }

        for (int ele : arr) {
            System.out.println(ele);
        }

        return;

    }

    public static int leftmaxD = 0;

    public static void widthD(TreeNode root, int level) {

        if (root == null) {
            return;
        }

        widthD(root.left, level - 1);
        widthD(root.right, level + 0);

        leftmaxD = Math.min(leftmaxD, level);

    }

    public static void DiagonalView(TreeNode root) {

        leftmaxD = 0;

        widthD(root, 0);

        ArrayList<TreeNode>[] arr = new ArrayList[-leftmaxD + 1];

        for (int i = 0; i < (1 - leftmaxD); i++) {
            arr[i] = new ArrayList<TreeNode>();
        }

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmaxD));

        while (q.size() != 0) {

            int cursize = q.size();

            while (cursize-- > 0) {

                VOpair rvtx = q.removeFirst();

                arr[rvtx.level].add(rvtx.t);

                if (rvtx.t.left != null)
                    q.addLast(new VOpair(rvtx.t.left, rvtx.level - 1));
                if (rvtx.t.right != null)
                    q.addLast(new VOpair(rvtx.t.right, rvtx.level + 0));
            }
        }
        int count = 0;
        for (ArrayList<TreeNode> al : arr) {
            System.out.print("Diagonal " + (count++) + " -> ");
            for (TreeNode tt : al) {
                System.out.print(tt.val + " , ");
            }
            System.out.println();
        }

        return;

    }

    public static void DiagonalViewSum(TreeNode root) {

        leftmaxD = 0;

        widthD(root, 0);

        int[] arr = new int[-leftmaxD + 1];

        LinkedList<VOpair> q = new LinkedList<>();

        q.addLast(new VOpair(root, -leftmaxD));

        while (q.size() != 0) {

            int cursize = q.size();

            while (cursize-- > 0) {

                VOpair rvtx = q.removeFirst();

                arr[rvtx.level] += rvtx.t.val;

                if (rvtx.t.left != null)
                    q.addLast(new VOpair(rvtx.t.left, rvtx.level - 1));
                if (rvtx.t.right != null)
                    q.addLast(new VOpair(rvtx.t.right, rvtx.level + 0));
            }
        }
        int count = 0;
        for (TreeNode tt : al) {
            System.out.print("Diagonal " + (count++) + " -> ");

            System.out.print(tt.val + " , ");

            System.out.println();
        }

        return;

    }

}