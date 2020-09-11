import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

//generic tree is like a directed acyclic graph.=============================
public class L031 {

    public static class Node {
        int val;
        List<Node> child;

        Node() {
            this.val = 0;
            this.child = new ArrayList<>();
        }

        Node(int ele) {
            this.val = ele;
            this.child = new ArrayList<>();
        }

    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {
        int[] arr = { 10, 20, 30, -1, 40, -1, 50, -1, -1, 60, 70, -1, 80, 90, -1, 100, -1, -1, 110, -1, -1, 120, 130,
                -1, -1, -1 };
        Node root = constructTree(arr);
        display(root);
        // set1(root);
        set2(root);
    }

    public static void set1(Node root) {

        System.out.println(find(root, 90));
        System.out.println(height(root));
        System.out.println(size(root));
        dia = -1;
        diameter(root);
        System.out.println(dia);

        ArrayList<Integer> ans = new ArrayList<>();
        rootToNode(root, 130, ans);
        System.out.println(ans);

    }

    public static void set2(Node root) {

        // linearize(root);
        // display(root);

        flatten(root);
        display(root);
    }

    public static Node constructTree(int[] arr) {
        Stack<Node> st = new Stack<>();

        for (int i = 0; i < arr.length - 1; i++) {
            if (arr[i] != -1) {
                st.push(new Node(arr[i]));
            } else {
                Node rvtx = st.pop();
                st.peek().child.add(rvtx);
            }
        }

        System.out.println(st.peek().val);

        return st.pop();
    }

    public static void display(Node root) {

        System.out.print(root.val + " -> ");
        for (Node n : root.child) {
            System.out.print(n.val + ",");
        }
        System.out.println();
        for (Node n : root.child) {
            display(n);
        }
        return;

    }

    public static boolean find(Node root, int ele) {
        if (root.val == ele)
            return true;

        boolean res = false;
        for (Node n : root.child) {
            res = res || find(n, ele);
        }

        return true;
    }

    public static int size(Node root) {
        int sz = 0;
        for (Node n : root.child) {
            sz += size(n);
        }
        return sz + 1;
    }

    public static int height(Node root) {
        int hei = -1;
        for (Node n : root.child) {
            hei = Math.max(hei, height(n));
        }
        return hei + 1;
    }

    public static int dia = -1;

    public static int diameter(Node root) {

        int first = -1;
        int second = -1;
        for (Node n : root.child) {
            int val = diameter(n);
            if (val > first) {
                second = first;
                first = val;
            } else if (val > second) {
                second = val;
            }
        }

        dia = Math.max(dia, second + first + 2);
        return first + 1;
    }

    public static boolean rootToNode(Node root, int data, ArrayList<Integer> ans) {
        if (root.val == data) {
            ans.add(root.val);
            return true;
        }
        boolean res = false;
        for (int i = 0; i < root.child.size(); i++) {
            res = res || rootToNode(root.child.get(i), data, ans);
        }

        if (res) {
            ans.add(root.val);
        }

        return res;

    }

    public static void linearize(Node root) // converting to linked list type structure.==========
    {
        if (root.child.size() == 0)
            return;

        for (Node n : root.child) {
            linearize(n);
        }

        // assume this for a simple tree ==========================
        for (int i = 0; i < root.child.size() - 1; i++) {
            int j = i + 1;
            Node temp = root.child.get(i);
            while (temp.child.size() != 0) {
                temp = temp.child.get(0);
            }
            temp.child.add(root.child.get(j));
        }
        while (root.child.size() != 1) {
            root.child.remove(root.child.size() - 1);
        }

        return;

    }

    public static void flatten(Node root, List<Node> ll) {

        for (Node n : root.child) {
            flatten(n, ll);
        }

        ll.add(root);

        return;
    }

    public static void flatten(Node root) {

        if (root.child.size() == 0)
            return;

        // getting all the grandchilds of the root.=====================
        List<Node> ll = new ArrayList<>();
        for (Node n : root.child) {
            for (Node nn : n.child) {
                flatten(nn, ll);
            }
        }

        root.child.addAll(ll); // adding them in the root

        // removing all the childs of childs, so that only root contains all the
        // elements.=====================
        for (Node n : root.child) {
            n.child.clear();
        }

        return;

    }

    public static boolean isMirror(Node root1, Node root2) {
        if (root1.child.size() != root2.child.size() || root1.val != root2.val) {
            return false;
        }

        boolean res = true;
        
        for (int i = 0, j = root1.child.size() - 1; j >= 0; i++, j--) {
            res = res && isMirror(root1.child.get(i), root1.child.get(j));
        }

        return res;


    }

    public static boolean isSymmteric(Node root1, Node root2) {
        if (root1.child.size() != root2.child.size() /*|| root1.val != root2.val*/ ) {
            return false;
        }

        boolean res = true;
        
        for (int i = 0, j = root1.child.size() - 1; j >= 0; i++, j--) {
            res = res && isSymmteric(root1.child.get(i), root2.child.get(j));
        }

        return res;
    }
}