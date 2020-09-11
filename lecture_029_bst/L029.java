public class L029 {
    public static void main(String[] args) {
        solve();
    }

    public static class TreeNode {
        int val = 0;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int data) {
            this.val = data;
        }

        TreeNode() {
        }
    }

    public static TreeNode constructTree(int[] arr, int st, int end) {

        if (st > end) {
            return null;
        }

        TreeNode root = new TreeNode(arr[(st + end) / 2]);

        root.left = constructTree(arr, st, ((st + end) / 2) - 1);

        root.right = constructTree(arr, ((st + end) / 2) + 1, end);

        return root;
    }

    public static void display(TreeNode root) {
        if (root == null) {
            return;
        }

        String str = "";

        str = str + (root.left == null ? "." : (root.left.val));
        str = str + " <- " + (root.val) + " -> ";
        str = str + (root.right == null ? "." : (root.right.val));

        System.out.println(str);

        display(root.left);

        display(root.right);
        return;

    }

    public static void solve() {

        int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130 };
        TreeNode root = constructTree(arr, 0, arr.length - 1);
        display(root);
        set1(root);
    }

    public static TreeNode pred = null;
    public static TreeNode succ = null;

    public static void inOrder_pre_succ(TreeNode root, int data) {

        pred = null;
        succ = null;
        TreeNode curr = root;

        while (curr != null) {

            if (curr.val == data) {

                if (curr.left == null) {
                    System.out.println(pred != null ? pred.val : "-1");
                } else {
                    TreeNode leftele = curr.left;
                    while (leftele.right != null) {
                        leftele = leftele.right;
                    }
                    System.out.println(leftele.val);
                }

                if (curr.right == null) {
                    System.out.println(succ != null ? succ.val : "-1");
                } else {
                    TreeNode rightele = curr.right;
                    while (rightele.left != null) {
                        rightele = rightele.left;
                    }
                    System.out.println(rightele.val);
                }

                break;

            }

            else if (curr.val > data) {
                succ = curr; // left mein jate hue successor, kyuki jis node se left jare ha vo bda ha data
                             // se, aur bda element successor hota ha
                curr = curr.left;
            }

            else {
                pred = curr; // right mein jate hue predessor set,kyuki jis node se right jare ha vo chota ha
                             // data se, aur chota element predessor hota ha
                curr = curr.right;
            }

        }

        return;

    }


    //creating tree from preOrder iterative.========================================
    TreeNode bstFromPreorder(int[] preorder) {
        int n = preorder.length;
        if (n == 0)
            return null;
        Stack<TreeNode> st = new Stack<>();
        TreeNode root = new TreeNode(preorder[0]);
        st.push(root);
        int i = 1; // zeroth is already pushed
        while (i < n) {
            TreeNode node = new TreeNode(preorder[i++]);

            TreeNode temp = null;
            while (!st.empty() && st.peek().val < node.val) {
                temp = st.pop(); // last popped value will contain the parent of node as it will jst smaller than
                                 // node, hence attach node on right of temp
            }
            if (temp != null)
                temp.right = node;
            else {
                st.peek().left = node;
            }

            st.push(node);
        }

        return root;

    }

    public static void set1(TreeNode root) {

        inOrder_pre_succ(root, 100);
        return;
    }
}