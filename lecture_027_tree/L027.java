//TREE TO DLL AND SINGLY LINKED LIST.=================================

public class L027 {

    public static class TreeNode {

        int val;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int ele) {
            this.val = ele;
        }

        TreeNode() {

        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {
        int[] arr = { 11, 6, 4, -1, 5, -1, -1, 8, -1, 10, -1, -1, 19, 17, -1, -1, 43, 31, -1, -1, 49, -1, -1 };
        TreeNode root = constructTree(arr);
        display(root);

        System.out.println();
        // set2(root);

        flatten_left(root);
        display(root);
        System.out.println();

        flatten_right(root);
        display(root);

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
        str += ((root.left != null) ? root.left.val : ".");
        str += " <- " + root.val + " -> ";
        str += ((root.right != null) ? root.right.val : ".");
        System.out.println(str);

        display(root.left);
        display(root.right);

        return;

    }

    public static void set2(TreeNode root) {
        DLL(root);

        while (head != null) {

            System.out.print(head.val + " , ");
            head = head.right;

        }
    }

    public static TreeNode head = null;
    public static TreeNode prev = null;

    // dll inorder
    public static void DLL(TreeNode root) {
        if (root == null) {
            return;
        }

        DLL(root.left);

        if (head == null) {
            head = root;
        } else {
            prev.right = root;
            root.left = prev;
        }
        prev = root;

        DLL(root.right);

        return;
    }

    public static TreeNode lastNode = null;

    public static void lastOfPreOrder(TreeNode root) {
        if (root == null)
            return;
        lastNode = root;
        lastOfPreOrder(root.left);
        lastOfPreOrder(root.right);
        return;
    }

    // flatten to right in preORDER
    public static void flatten_right(TreeNode root) {
        if (root == null || (root.left == null && root.right == null))
            return;

        lastNode = root;
        lastOfPreOrder(root.left);
        TreeNode joint = lastNode;

        flatten_right(root.left);
        flatten_right(root.right);
        
        if(joint!=null)     //as the left st may be null,
        {
            joint.right = root.right;
            root.right = root.left;
            root.left = null;
        }
        return;
    }

    // flatten to left in preORDER
    public static void flatten_left(TreeNode root) {
        if (root == null || (root.left == null && root.right == null))
            return;

        lastNode = root;
        lastOfPreOrder(root.left);
        TreeNode joint = lastNode;

        flatten_left(root.left);
        flatten_left(root.right);
        
        joint.left = root.right;
        root.right = null;

        return;
    }

}