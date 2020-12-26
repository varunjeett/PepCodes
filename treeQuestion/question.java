public class question {

    // tilt of binary tree
    class Solution {
        int total = 0;// maintain total tilt sum

        public int sum(TreeNode root) {// return the sum of the tree
            if (root == null)
                return 0;

            int ll = sum(root.left);
            int rr = sum(root.right);
            total += Math.abs(ll - rr);// tilt for that node
            return ll + rr + root.val;
        }

        public int findTilt(TreeNode root) {
            if (root == null)
                return 0;
            total = 0;
            sum(root);
            return total;
        }
    }

    // binary tree cameras , covering type questions

    // If a node has its children covered and has a parent, then it is strictly
    // better to place the camera at this node's parent.
    // If a node has children that are not covered by a camera, then we must place a
    // camera here.
    // Additionally, if a node has no parent and it is not covered, we must place a
    // camera here.

    public class camera {
        int ans;
        Set<TreeNode> covered;

        public int minCameraCover(TreeNode root) {
            ans = 0;
            covered = new HashSet();
            covered.add(null); // so that we never need to add camera for null childs, keeping it covered.

            dfs(root, null);
            return ans;
        }

        public void dfs(TreeNode node, TreeNode par) {
            if (node != null) {
                dfs(node.left, node);
                dfs(node.right, node);

                if ((par == null && !covered.contains(node)) || !covered.contains(node.left)
                        || !covered.contains(node.right)) {
                    ans++;
                    covered.add(node);
                    covered.add(par);
                    covered.add(node.left);
                    covered.add(node.right);
                }
            }
        }
    }

    // binary tree clone with random pointer

    // step1
    public static void addClone(TreeNode root) {
        if (root == null) {
            return;
        }

        TreeNode cloner = new TreeNode(root.data);
        TreeNode tmp = root.left;
        cloner.left = tmp;
        root.left = cloner;
        addClone(tmp);
        addClone(root.right);

    }

    // step2
    public static void addRandom(TreeNode root) {
        if (root == null) {
            return;
        }

        TreeNode rand = root.random;
        if (rand != null) {
            root.left.random = rand.left;
        }

        addRandom(root.left.left);
        addRandom(root.right);

    }

    // step3
    public static void seperate(TreeNode root) {
        if (root == null) {
            return;
        }

        TreeNode aleft = root.left.left;
        TreeNode aright = root.right;

        if (aleft != null) {
            root.left.left = aleft.left;
        }

        if (aright != null) {
            root.left.right = aright.left;
        }

        root.left = aleft;
        root.right = aright;

        seperate(aleft);
        seperate(aright);

    }

    public static TreeNode cloneTreeNode(TreeNode root) {

        // add code here.
        if (root == null) {
            return null;
        }

        addClone(root);
        addRandom(root);
        TreeNode nhead = root.left;
        seperate(root);
        return nhead;
    }

}

// 979. Distribute Coins in Binary Tree

// If the leaf of a tree has 0 coins (an excess of -1 from what it needs), then
// we should push a coin from its parent onto the leaf.
// If it has say, 4 coins (an excess of 3), then we should push 3 coins off the
// leaf.
// In total, the number of moves from that leaf to or from its parent is excess
// = Math.abs(num_coins - 1).
// Afterwards, we never have to consider this leaf again in the rest of our
// calculation.

class Solution {
    int total = 0;

    public int find(TreeNode root) {
        if (root == null)
            return 0;

        int lx = find(root.left);
        int rx = find(root.right);

        int cx = Math.abs(lx + rx + root.val - 1);
        total += cx;

        return (lx + rx + root.val - 1);

    }

    public int distributeCoins(TreeNode root) {
        if (root == null)
            return 0;

        total = 0;
        find(root);
        return total;
    }

}

// 1372. Longest ZigZag Path in a Binary Tree
class Solution {

    int mx;

    // {current node se left ki taraf,current node se right ki taraf}
    public int[] find(TreeNode root) {

        // return no of edges
        if (root == null)
            return new int[] { -1, -1 };

        int[] ll = find(root.left);

        int[] rr = find(root.right);

        int cur_max = Math.max(1 + ll[1], 1 + rr[0]);
        mx = Math.max(mx, cur_max);

        return new int[] { 1 + ll[1], 1 + rr[0] };
    }

    public int longestZigZag(TreeNode root) {

        if (root == null)
            return 0;

        mx = 0;
        find(root);
        return mx;
    }

}

// 1609. Even Odd Tree

class Solution {

    public boolean isEvenOddTreeDFS(TreeNode root) {
        if (root == null)
            return true;
        HashMap<Integer, Integer> map = new HashMap<>();
        boolean ans = isEvenOddTreeHelper(root, map, 0);
        return ans;
    }

    private boolean isEvenOddTreeHelper(TreeNode root, HashMap<Integer, Integer> map, int currLevel) {
        if (root == null)
            return true;
        if (currLevel % 2 == 0 && root.val % 2 == 0)
            return false;
        if (currLevel % 2 == 1 && root.val % 2 == 1)
            return false;
        if (map.containsKey(currLevel)) {
            int prevKey = map.get(currLevel);
            if (currLevel % 2 == 0) {
                // odd and should be in increasing order
                if (prevKey >= root.val)
                    return false;
            } else {
                // even and should be in decreasing order
                if (prevKey <= root.val)
                    return false;
            }
        }
        map.put(currLevel, root.val);
        return isEvenOddTreeHelper(root.left, map, currLevel + 1)
                && isEvenOddTreeHelper(root.right, map, currLevel + 1);
    }
}