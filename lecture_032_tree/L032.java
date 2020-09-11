import java.util.Stack;
import java.util.ArrayList;

public class L032 {

    public static class TreeNode {

        int data;
        TreeNode left;
        TreeNode right;

        TreeNode() {

            this.data = 0;
            this.left = null;
            this.right = null;

        }

        TreeNode(int ele) {

            this.data = ele;
            this.left = null;
            this.right = null;

        }

        TreeNode(TreeNode n) {

            this.data = n.data;
            this.left = n.left;
            this.right = n.right;

        }
    }

    public static class tpair {

        TreeNode node;
        boolean sd = false;
        boolean ld = false;
        boolean rd = false;

        tpair(TreeNode n) {
            this.node = new TreeNode(n);
        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {
        // int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,
        //         -1 };
        // TreeNode root = constructTree(arr);
        // display(root);
        // // itrPreTraverse(root);
        // morris_in(root);
        // morris_pre(root);

        
        TreeNode root2 = constructTree(arr2);
        // display(root2);

        set2(root2);
        
    }

    public static void set2(TreeNode root) {
        String ans=serialize(root);
        System.out.println(ans);
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

        str = str + (root.left == null ? "." : root.left.data);
        str = str + " <- " + root.data + " -> ";
        str = str + (root.right == null ? "." : root.right.data);

        System.out.println(str);// pre order

        display(root.left);

        // System.out.println(str); //in order

        display(root.right);

        // System.out.println(str); //post order

        return;
    }

    public static void itrPreTraverse(TreeNode root) {
        if (root == null)
            return;

        tpair t = new tpair(root);
        Stack<tpair> st = new Stack<>();
        st.push(t);

        while (st.size() != 0) {

            tpair rvtx = st.peek();

            if (rvtx.sd && rvtx.ld && rvtx.rd) {
                st.pop();
                continue;
            }

            if (!rvtx.ld) { // left

                if (rvtx.node.left != null)
                    st.push(new tpair(rvtx.node.left));

                rvtx.ld = true;
                continue;
            }

            if (!rvtx.sd) { // self
                System.out.print(rvtx.node.data + ",");
                rvtx.sd = true;
            }

            if (!rvtx.rd) { // right

                if (rvtx.node.right != null)
                    st.push(new tpair(rvtx.node.right));

                rvtx.rd = true;
                continue;
            }
        }

        return;
    }

    public static boolean findRightMost(TreeNode temp, TreeNode root) {

        while (temp.right != null && temp.right != root) {
            temp = temp.right;
        }

        if (temp.right == null) {
            temp.right = root;
            return true;
        } 
        else {
            temp.right = null;
            return false;
        }
    }

    public static void morris_in(TreeNode root) {
        System.out.println();
        if (root == null)
            return;

        TreeNode node = root;

        while (node != null) {
            TreeNode temp = node.left;
            if (temp == null) {
                System.out.print(node.data + ",");
                node = node.right;
                continue;
            } 
            else {
                boolean check = findRightMost(temp, node);
                // check is false, thread was there , so break the thread(done in the function)
                // and print, and move to right

                // check is true, made thread in the function itself, move to left.=============
                if (!check) {
                    // breaking the exisiting thread
                    System.out.print(node.data + ",");
                    node = node.right;
                    continue;
                } 
                else {
                    node = node.left;
                    continue;
                }
            }

        }

    }

    public static void morris_pre(TreeNode root) {
        System.out.println();
        if (root == null)
            return;

        TreeNode node = root;

        while (node != null) {
            TreeNode temp = node.left;
            if (temp == null) 
            {
                System.out.print(node.data + ",");      //when no left tree exists.
                node = node.right;
                continue;
            } 
            else {
                boolean check = findRightMost(temp, node);
                // check is false, thread was there , so break the thread(done in the function)
                // and print, and move to right

                // check is true, made thread in the function itself, move to left.=============
                if (!check) {
                    // breaking the exisiting thread
                    node = node.right;
                    continue;
                } else {
                    System.out.print(node.data+",");    //print when thread is created.
                    node = node.left;
                    continue;
                }
            }

        }

    }

    public static TreeNode construct(ArrayList<Integer> al) {
        if(al.size()==0)
            return null;
        
        int val=al.get(0);
        TreeNode root=new TreeNode(val);
        
        ArrayList<Integer> leftAl=new ArrayList<>();
        ArrayList<Integer> rightAl=new ArrayList<>();

        for(int i=1; i<al.size(); i++) {
            int ele=al.get(i);
            if(ele < val) {
                leftAl.add(ele);
            }
            else
            {
                rightAl.add(ele);
            }
        }
        
        root.left=construct(leftAl);
        root.right=construct(rightAl);
        return root;
    }
    public static TreeNode constructBST(int[] arr){
        //Write your code here and return the root of the constructed BST
        int n=arr.length;
        if(n==0)
            return null;

        ArrayList<Integer> al=new ArrayList<>();
        for(int ele:arr)
            al.add(ele);
        
        return construct(al);
        // return null;
    }

    public static String serialize(TreeNode root) {
        if(root==null) {
            return "X,";
        }
        String str="";
        String left=serialize(root.left);
        String right=serialize(root.right);
        str=root.data+","+left+right;
        return str;
    }

    // public static TreeNode deserialize(String ans) {


    // }

}