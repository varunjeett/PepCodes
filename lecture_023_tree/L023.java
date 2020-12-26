import java.util.ArrayList;

public class L023 {
    public static class Treenode {
        int data;
        Treenode left;
        Treenode right;

        Treenode(int ele) {
            this.data = ele;
            this.left = null;
            this.right = null;
        }

        Treenode() {
            this.data = 0;
            this.left = null;
            this.right = null;
        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {

        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,
                -1 };
        Treenode root = constructTree(arr);
        display(root);
        
        System.out.println(jpTest(root,40));  
    
        // System.out.println(find(root, 100));
        // System.out.println(sizeOFtree(root));
        // System.out.println(heigthOFtree(root));
        // System.out.println(maxOFtree(root));
        // System.out.println(minOFtree(root));

        // NodeToRootPath01(root,100);

        // for(Treenode t:path) {
        // System.out.print( t.data + " -> ");
        // }

        // ArrayList<Treenode> printAns = NodeToRootPath02(root, 100);

        // for (Treenode t : printAns) {
        //     System.out.print(t.data + " -> ");
        // }

    }

    public static int idx = 0;

    public static Treenode constructTree(int[] arr) {

        if (arr[idx] == -1) {
            idx++;
            return null;
        }

        Treenode root = new Treenode(arr[idx]);
        idx++;
        root.left = constructTree(arr);
        root.right = constructTree(arr);

        return root;
    }

    public static void display(Treenode root) {

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

    public static boolean find(Treenode root, int ele) {

        if (root == null) {
            return false;
        }

        if (root.data == ele) {
            return true;
        }

        boolean res = false;

        res = find(root.left, ele) || find(root.right, ele);

        return res;
    }

    public static int sizeOFtree(Treenode root) {

        if ((root == null)) {
            return 0;
        }

        int l_size = sizeOFtree(root.left);
        int r_size = sizeOFtree(root.right);

        return l_size + r_size + 1;

    }

    public static int heigthOFtree(Treenode root) {

        if (root == null) {
            return -1;
        }

        int l_h = heigthOFtree(root.left);
        int r_h = heigthOFtree(root.right);

        return Math.max(l_h, r_h) + 1;

    }

    public static int maxOFtree(Treenode root) {
        if (root == null) {
            return -100000;
        }
        int left_max = maxOFtree(root.left);
        int right_max = maxOFtree(root.right);

        return Math.max(Math.max(left_max, right_max), root.data);
    }

    public static int minOFtree(Treenode root) {
        if (root == null) {
            return 100000;
        }
        int left_min = minOFtree(root.left);
        int right_min = minOFtree(root.right);

        return Math.min(Math.min(left_min, right_min), root.data);
    }

    public static ArrayList<Treenode> path = new ArrayList<>();

    public static boolean NodeToRootPath01(Treenode root, int ele) {

        if (root == null) {
            return false;
        }

        if (root.data == ele) {
            path.add(root);
            return true;
        }

        boolean res = false;

        res = res || NodeToRootPath01(root.left, ele) || NodeToRootPath01(root.right, ele);

        if (res) {
            path.add(root);
        }

        return res;
    }

    public static ArrayList<Treenode> NodeToRootPath02(Treenode root, int ele) {

        if (root == null) {
            return new ArrayList<Treenode>();
        }

        if (root.data == ele) {
            ArrayList<Treenode> base = new ArrayList<Treenode>();
            base.add(root);
            return base;
        }

        ArrayList<Treenode> leftans = NodeToRootPath02(root.left, ele);
        if (leftans.size() != 0) {
            leftans.add(root);
            return leftans;
        }

        ArrayList<Treenode> rightans = NodeToRootPath02(root.right, ele);
        if (rightans.size() != 0) {
            rightans.add(root);
            return rightans;
        }

        return new ArrayList<Treenode>();

    }


    public static int jpTest(Treenode root,int k)
    {
        mintill=(int)1e9;
        closest(root, k);
        return mintill;
    }

    public static int mintill=(int)1e9;
    public static Treenode ans=null;
    public static int closest(Treenode root, int data)
    {
        if(root==null)
            return -1;

        if(root.data==data)
        {
            mintill=Math.min(mintill, getLeaf(root,null));
            return 1;
        }

        int l=closest(root.left, data);
        if(l!=-1)
        {
            mintill=Math.min(mintill, (getLeaf(root,root.left)+1));
            return l+1;
        }
        
        int r=closest(root.right, data);
        if(r!=-1)
        {
            mintill=Math.min(mintill, (getLeaf(root,root.right)+1));
            return r+1;
        }

        return -1;
    }

    public static int getLeaf(Treenode root,Treenode block)
    {
        if(root.left==null && root.right==null)
        {
            return 0;
        }

        int mn=(int)+1e9;
        if(root.left!=null && root.left!=block)
        {
            mn=Math.min(mn, getLeaf(root.left, block));
        }

        if(root.right!=null && root.right!=block)
        {
            mn=Math.min(mn, getLeaf(root.left, block));
        }

        return mn+1;
    }

}
