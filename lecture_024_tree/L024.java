import java.util.ArrayList;

public class L024 {

    public static class Treenode {

        int val;
        Treenode left;
        Treenode right;

        Treenode(int ele) {

            this.val = ele;
            this.left = null;
            this.right = null;

        }

        Treenode() {

            this.val = 0;
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
        // ArrayList<Treenode> printIt = nodeToRootPath( root , 10000 );
        // for(Treenode t: printIt) {
        // System.out.print(t.val + " -> ");
        // }

        // Treenode lca=LCA(root,20,40);
        // System.out.println("lca ->" + ( lca==null ? "-1" : lca.val) );

        // KnodesDown(root,30,2);
        // KnodesUpDown01(root, 50);
        KnodesUpDown02(root, 50, 5);

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

        str = str + (root.left == null ? "." : root.left.val);
        str = str + " <- " + (root.val) + " -> ";
        str = str + (root.right == null ? "." : root.right.val);

        System.out.println(str);

        display(root.left);
        display(root.right);

        return;
    }

    public static ArrayList<Treenode> nodeToRootPath(Treenode root, int ele) {

        if (root == null) {
            ArrayList<Treenode> base = new ArrayList<Treenode>();
            return base;
        }

        if (root.val == ele) {
            ArrayList<Treenode> base = new ArrayList<Treenode>();
            base.add(root);
            return base;
        }

        ArrayList<Treenode> left = nodeToRootPath(root.left, ele);
        if (left.size() != 0) {
            left.add(root);
            return left;
        }

        ArrayList<Treenode> right = nodeToRootPath(root.right, ele);
        if (right.size() != 0) {
            right.add(root);
            return right;
        }

        return new ArrayList<Treenode>();
    }

    public static Treenode LCA(Treenode root, int p, int q) {

        ArrayList<Treenode> p_ans = nodeToRootPath(root, p);
        ArrayList<Treenode> q_ans = nodeToRootPath(root, q);

        if (p_ans.size() == 0 || q_ans.size() == 0)
            return null;

        int prev = p_ans.size() - 1;

        int i = p_ans.size() - 2;
        if (i < 0)
            return p_ans.get(prev);

        int j = q_ans.size() - 2;
        if (j < 0)
            return p_ans.get(prev);

        while (i >= 0 && j >= 0 && p_ans.get(i).val == q_ans.get(j).val) {
            i--;
            j--;
            prev--;
        }

        return p_ans.get(prev);

    }

    public static Treenode ans = null;

    public static boolean LCA_byfind(Treenode root, int p, int q) {

        if (root == null) {
            return false;
        }

        boolean self = false;

        if (root.val == p || root.val == q) {
            self = true;
        }

        boolean left = LCA_byfind(root.left, p, q);
        if (ans != null) {
            return true;
        }

        boolean right = LCA_byfind(root.right, p, q);
        if (ans != null) {
            return true;
        }

        if (left && self == true || right && self == true || right && left == true) {
            ans = root;
        }

        return self || left || right;

    }

    public static void printKDown(Treenode root, int k, Treenode blocknode) {

        if (root == null || root == blocknode) {
            return;
        }

        if (k == 0) {
            System.out.print(root.val + " , ");
        }

        printKDown(root.left, k - 1, blocknode);
        printKDown(root.right, k - 1, blocknode);

        return;

    }

    public static boolean KnodesDown(Treenode root, int target, int k) {

        if (root == null)
            return false;

        if (root.val == target) {
            // print the node at k depth
            printKDown(root, k, null);
            return true;
        }
        boolean res = false;

        res = res || KnodesDown(root.left, target, k) || KnodesDown(root.right, target, k);

        return res;
    }

    public static int level = 4;

    public static boolean KnodesUpDown01(Treenode root, int target) {

        if (root == null) {

            return false;
        }

        if (root.val == target) {
            printKDown(root, level, null);
            level--;
            return true;
        }

        boolean res = false;

        res = res || KnodesUpDown01(root.left, target);
        if (res) {
            printKDown(root, level, root.left);
            level--;
            return res;
        }

        res = res || KnodesUpDown01(root.right, target);
        if (res) {
            printKDown(root, level, root.right);
            level--;
            return res;
        }

        return res;
    }

    public static int KnodesUpDown02(Treenode root, int target, int level) {
        if (root == null) {
            return -1;
        }
        
        if (root.val == target) {
            printKDown(root, level, null);
            return 1;
        }

        int left = KnodesUpDown02(root.left, target, level);

        if (left != -1) {
            if (level - left >= 0) {
                printKDown(root, level - left, root.left);
            }
            return left + 1;
        }

        int right = KnodesUpDown02(root.right, target, level);
        if (right != -1) {
            if (level - left >= 0) {
                printKDown(root, level - right, root.right);
            }
            return right + 1;
        }

        return -1;

    }

    public static boolean pathSum(TreeNode root, int sum) {

        if (root == null) {
            return false;
        }

        if (root.left == null && root.right == null) 
        {
            if (sum - root.val == 0)
                return true;
            return false;
        }

        return pathSum(root.left, sum - root.val) || pathSum(root.right, sum - root.val);
    }


    public static boolean hasPathSum(TreeNode root, int sum) {
        if (root == null)
            return false;
        return pathSum(root, sum);
    }

    // diameter series.================================================
    public static int height(Treenode root) {

        if (root == null)
            return -1;

        int leftH = height(root.left);

        int rightH = height(root.right);

        return Math.max(leftH, rightH) + 1;
    }

    public static int diameter01(Treenode root) {

        if (root = null)
            return 0;

        int ld = diameter01(root.left);
        int rd = diameter01(root.right);

        int lh = height(root.left);
        int rh = height(root.right);

        return Math.max(Math.max(ld, rd), lh + rh + 2);

    }

    public static class pair_ {
        int dia;
        int hei;

        pair_(int d, int h) {
            this.dia = d;
            this.hei = h;
        }
    }

    public static pair_ diameter02(Treenode root) {
        if (root = null)
            return new pair_(0, -1);

        pair_ l_val = diameter02(root.left);
        pair_ r_val = diameter02(root.right);

        pair_ pair_root = new pair_(0, -1);

        pair_root.dia = Math.max(Math.max(l_val.dia, r_val.dia), l_val.hei + r_val.hei + 2);
        pair_root.hei = Math.max(r_val.hei, l_val.hei) + 1;

        return pair_root;
    }


    public static int dia_global = 0; // stores the result of childs
    public static int diameter03(Treenode root) {
        if (root = null)
            return -1;

        int l_val = diameter03(root.left);
        int r_val = diameter03(root.right);

        dia_global = Math.max(dia_global, l_val + r_val + 2);  //calculate and compare current result

        return Math.max(l_val, r_val) + 1;
    }

    public static int maxtillnow = 0;
    public static int leafToLeaf(Treenode root) {
        maxtillnow = 0;
        findSum(root);
        return maxtillnow;
    }

    public static int findSum(Treenode root) {
        
        if(root==null) return 0;

        int leftMaxNodeToLeaf=findSum(root.left);
        int rightMaxNodeToLeaf=findSum(root.right); 
        
        if(root.left!=null && root.right!=null) {
            maxtillnow= Math.max(maxtillnow,leftMaxNodeToLeaf+rightMaxNodeToLeaf+root.val);
            return Math.max(leftMaxNodeToLeaf, rightMaxNodeToLeaf) + root.val);
        }
        
        if(root.left==null)
           return rightMaxNodeToLeaf+root.val;
        else
        return leftMaxNodeToLeaf+root.val;    
    }

    public int maxtillnow2 = (int) -1e8;
    public int maxPathSum(TreeNode root) {

        maxtillnow2 = (int) -1e8;
        findSum2(root);
        return maxtillnow2;
    }

    public int findSum2(TreeNode root) {

        if (root == null)
            return (int) -1e8;

        int leftMaxNodeToNode = findSum2(root.left);
        int rightMaxNodeToNode = findSum2(root.right);

        int max_ = Math.max(leftMaxNodeToNode, rightMaxNodeToNode) + root.val;

        maxtillnow2 = Math.max(Math.max(Math.max(maxtillnow2, leftMaxNodeToNode + rightMaxNodeToNode + root.val), root.val), max_);

        return Math.max(max_, root.val);

    }

}