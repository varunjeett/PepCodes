//complete avl implementation.==================================

public class L030 {

    public static class TreeNode {

        int val = 0;
        int hei = 0;
        int bal = 0;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode() {
        }

        TreeNode(int ele) {
            this.val = ele;
        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {

        int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
        TreeNode root = constructTree(arr, 0, arr.length - 1);
        display(root);
        System.out.println();

        // addEle(root, 100);
        // display(root);
        // System.out.println();

        // addEle(root, 110);
        // display(root);
        // System.out.println();

        // addEle(root, 120);
        // display(root);
        // System.out.println();

        //returned root ko catch krna is very important..========================
        root=removeEle(root, 50);
        display(root);
        System.out.println();

        root=removeEle(root, 10);
        display(root);
        System.out.println();

        root=addEle(root, 110);
        display(root);
        System.out.println();

        root=removeEle(root, 40);
        display(root);
        System.out.println();

        root=addEle(root, 130);
        display(root);
        System.out.println();

        search(root, 130);
        search(root, 30);
        search(root, 20);



    }

    public static void display(TreeNode root) {
        if (root == null) {
            return;
        }

        String str = "";

        str += root.left == null ? "." : root.left.val;
        str += " <-- " + root.val + "(" + root.bal + " , " + root.hei + ")" + " --> ";
        str += root.right == null ? "." : root.right.val;

        System.out.println(str);

        display(root.left);
        display(root.right);

        return;
    }

    public static TreeNode constructTree(int[] arr, int si, int ei) {

        if (si > ei) {
            return null;
        }

        int mid = si + (ei - si) / 2;
        TreeNode root = new TreeNode(arr[mid]);
        root.left = constructTree(arr, si, mid - 1);
        root.right = constructTree(arr, mid + 1, ei);
        update(root);
        return root;
    }

    public static void update(TreeNode root) {
        if (root == null)
            return;

        int lch = root.left == null ? -1 : root.left.hei;
        int rch = root.right == null ? -1 : root.right.hei;

        root.hei = Math.max(lch, rch) + 1;
        root.bal = lch - rch;

        return;
    }

    public static TreeNode rotate(TreeNode root) {
        
        if (root == null)
            return null;

        update(root);

        if (root.bal > 1 || root.bal < -1) {

            if (root.bal == 2) // LL or LR depending upon left child
            {
                if (root.left.bal == 1) // LL
                {
                    root = ll_rotate(root);
                } 
                else if (root.left.bal == -1) // LR
                {
                    root.left = rr_rotate(root.left);
                    root = ll_rotate(root);
                }
            }

            else if (root.bal == -2) // RR or RL depending upon right child
            {
                if (root.right.bal == -1) // RR
                {
                    root = rr_rotate(root);
                } 
                else if (root.right.bal == 1) // RL
                {
                    root.right = ll_rotate(root.right);
                    root = rr_rotate(root);
                }
            }

        }

        return root;

    }

    public static TreeNode ll_rotate(TreeNode a) {
        TreeNode b = a.left;
        TreeNode b_right = b.right;
        b.right = a;
        a.left = b_right;

        update(a);
        update(b);

        return b;
    }

    public static TreeNode rr_rotate(TreeNode a) {
        TreeNode b = a.right;
        TreeNode b_left = b.left;
        b.left = a;
        a.right = b_left;

        update(a);
        update(b);

        return b;
    }

    public static TreeNode addEle(TreeNode root, int data) {

        if (root == null)
        {
            System.out.println("Adding: "+ data);
            return new TreeNode(data);
        }

        else if (data < root.val) {
            root.left = addEle(root.left, data);
        } else {
            root.right = addEle(root.right, data);
        }

        root = rotate(root);
        return root;
    }

    public static TreeNode removeEle(TreeNode root, int data) {
        if (root == null)
            return null;

        else if (data < root.val) {
            root.left = removeEle(root.left, data);
        } 
        else if (data > root.val) {
            root.right = removeEle(root.right, data);
        } 
        else {
            
            System.out.println("Removing: "+ data);

            if (root.left == null || root.right == null)
                return root.left == null ? root.right : root.left;

            TreeNode temp = root.left;
            while (temp.right != null) {
                temp = temp.right;
            }

            root.val = temp.val;
            root.left = removeEle(root.left, temp.val);
        }

        root = rotate(root);
        return root;
    }

    public static void search(TreeNode root, int data)
    {
        if(root==null)
        {
            System.out.println("NOT FOUND");
            return;
        }
        else if(data < root.val)
            search(root.left, data);
        else if(data > root.val)
            search(root.right, data);
        else
        {
            System.out.println("FOUND: " + root.val);
        }

        return;
    }

}