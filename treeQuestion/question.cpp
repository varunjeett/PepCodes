//binary tree to DLL
static Node *head = nullptr;
static Node *last = nullptr;

void dll(Node *root)
{
    if (root == nullptr)
        return;

    dll(root->left);

    if (head == nullptr)
        head = root;
    else
    {
        last->right = root;
        root->left = last;
    }
    last = root;

    dll(root->right);

    return;
}

Node *bToDLL(Node *root)
{
    if (root == nullptr || (root->left == nullptr && root->right == nullptr))
        return root;

    head = nullptr;
    last = nullptr;
    dll(root);
    return head;
}

//116. Populating Next Right Pointers in Each Node
//iterative BFS
class Solution
{
public:
    Node *connect(Node *root)
    {
        if (root == nullptr)
            return nullptr;
        queue<Node *> q;
        q.push(root);
        q.push(nullptr);

        while (q.size() != 1)
        {
            Node *rvtx = q.front();
            q.pop();

            rvtx->next = q.front();
            if (rvtx->left != nullptr)
                q.push(rvtx->left);
            if (rvtx->right != nullptr)
                q.push(rvtx->right);
            if (q.front() == nullptr)
            {
                q.pop();
                q.push(nullptr);
            }
        }

        return root;
    }
};

//2nd approach : by recursion.======================================
class Solution
{
public:
    void setPointer(Node *root)
    {
        if (!root->left && !root->right)
            return;
        //set left child next
        root->left->next = root->right;

        //set right child next depending upon root's next
        if (root->next != nullptr)
            root->right->next = root->next->left; //POINT RIGHT CHILD NEXT TO ROOT SIBLING LEFT
        else
            root->right->next = nullptr;

        setPointer(root->left);
        setPointer(root->right);

        return;
    }
    Node *connect(Node *root)
    {
        if (root == nullptr)
            return nullptr;
        setPointer(root);
        return root;
    }
};

//flatten a binary tree:
class Solution
{
public:
    TreeNode *rightOfLeft(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *cur = root;
        while (cur->right != nullptr)
            cur = cur->right;

        return cur;
    }

    void flatten(TreeNode *root)
    {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return;

        flatten(root->left);
        flatten(root->right);

        TreeNode *rOfLeft = rightOfLeft(root->left);
        if (rOfLeft != nullptr)
        {
            if (root->right == nullptr)
            {
                root->right = root->left;
                root->left = nullptr;
            }
            else
            {
                rOfLeft->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
        }

        return;
    }
};

//2nd similiar approach.
class Solution
{
public:
    void flatten(TreeNode *root)
    {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return;
        //reversing the whole left and right ST as the whole left ST has to be on the right
        TreeNode *temp = root->right;
        root->right = root->left;
        root->left = temp;

        flatten(root->left);
        flatten(root->right);

        //getting the rightmost and joining it with the left ST(actually right as we reversed it)
        TreeNode *cur = root;
        while (cur->right != nullptr)
            cur = cur->right;
        cur->right = root->left;
        root->left = nullptr;

        return;
    }
};

//vertical order traversal.
//made the comparator outside of the solution class.
int range;
struct myComp
{
    bool operator()(const pair<TreeNode *, int> &t, const pair<TreeNode *, int> &o)
    {
        int r1 = t.second / range;
        int c1 = t.second % range;

        int r2 = o.second / range;
        int c2 = o.second % range;

        if (r1 == r2 && c1 == c2)
            return t.first->val > o.first->val; //decreasing , this > other

        if (r1 == r2)
            return c1 > c2;

        return r1 > r2;
    }
};

class Solution
{
public:
    int ll;
    int rr;

    void width(TreeNode *root, int val)
    {
        if (root == nullptr)
            return;

        ll = min(ll, val); //left mein minimum chahiye
        rr = max(rr, val); //right mein maximum chahiye

        width(root->left, val - 1);
        width(root->right, val + 1);

        return;
    }

    vector<vector<int>> verticalTraversal(TreeNode *root)
    {
        ll = +1e8;
        rr = -1e8;
        range = 0;

        if (root == nullptr)
            return {{}};

        width(root, 0);
        range = rr - ll + 1;
        vector<vector<int>> arr(range, vector<int>());

        priority_queue<pair<TreeNode *, int>, vector<pair<TreeNode *, int>>, myComp> q;
        q.push({root, (-ll)}); //adding ll to add the nodes so that from -2 .... 3 becomes 0 to 5.

        while (q.size() != 0)
        {
            int sz = q.size();
            while (sz-- > 0)
            {
                pair<TreeNode *, int> rvtx = q.top();
                q.pop();

                int r = rvtx.second / range;
                int c = rvtx.second % range;

                arr[c].push_back(rvtx.first->val);

                if (rvtx.first->left != nullptr)
                    q.push({rvtx.first->left, (r + 1) * range + (c - 1)});
                if (rvtx.first->right != nullptr)
                    q.push({rvtx.first->right, (r + 1) * range + (c + 1)});
            }
        }

        return arr;
    }
};

//important optimization
void inRange01(TreeNode *root, int a, int b, vector<int> &ans)
{
    count++;
    if (root == nullptr)
        return;

    if (a <= root->val) //if(a > root->val), then all left values will be smaller than a,(out of range),hence no need to traverse
        inRange01(root->left, a, b, ans);

    if (a <= root->val && root->val <= b)
        ans.push_back(root->val);

    if (b > root->val) //if(b < root->val), then all right values will be greater than b,(out of range),hence no need to traverse
        inRange01(root->right, a, b, ans);

    return;
}

//java code
//think about two scenario, values swapped were adjacent in the sorted array and other is apart. in apart we have two fluctuations. so we note them.
class Solution
{
    TreeNode a, b, c;
    TreeNode prev;

    boolean recoverINORDER(TreeNode root)
    {
        if (root == null)
            return true;

        if (!recoverINORDER(root.left))
            return false;

        //condition gets false.=========================
        if (prev.val > root.val)
        {
            if (a != null)
            { //first time
                c = root;
                return false; //no need to traverse more.
            }
            else //second time
            {
                a = prev;
                b = root;
                //dont return true here.
                // as there maybe the second fluctation in the right ST of the current root,if we will skip it if we'll skip the second fluctuation
            }
        }

        prev = root;

        if (!recoverINORDER(root.right))
            return false;

        return true;
    }

    void recoverTree(TreeNode root)
    {
        if (root == null || (root.left == null && root.right == null))
            return;

        prev = new TreeNode((int)Integer.MIN_VALUE);
        a = null;
        b = null;
        c = null;
        recoverINORDER(root);
        if (c == null)
        {
            int temp = a.val;
            a.val = b.val;
            b.val = temp;
        }
        else
        {
            int temp = a.val;
            a.val = c.val;
            c.val = temp;
        }
        return;
    }
}

//creating tree from preOrder iterative.========================================
TreeNode bstFromPreorder(int[] preorder)
{
    int n = preorder.length;
    if (n == 0)
        return null;
    
    Stack<TreeNode> st = new Stack<>();
    TreeNode root = new TreeNode(preorder[0]);
    st.push(root);
    int i = 1; // zeroth is already pushed
    while (i < n)
    {
        TreeNode node = new TreeNode(preorder[i++]);

        TreeNode temp = null;
        while (!st.empty() && st.peek().val < node.val)
        {
            temp = st.pop(); // last popped value will contain the parent of node as it will jst smaller than
                             // node, hence attach node on right of temp
        }
        if (temp != null)
            temp.right = node;
        else
        {
            st.peek().left = node;
        }

        st.push(node);
    }

    return root;
}

//creating tree from preorder , by recursive.==============================

//by using the above approach we can make a binary search tree from post order traversal.
//iterate arrray backwards and call for right ST first and then left ST.

int idx;
TreeNode *createBst(vector<int> &preorder, int lb, int rb)
{
    if (idx >= preorder.size() || lb > preorder[idx] || preorder[idx] > rb)
        return nullptr;

    TreeNode *root = new TreeNode(preorder[idx++]);

    root->left = createBst(preorder, lb, root->val);

    root->right = createBst(preorder, root->val, rb);

    return root;
}

TreeNode *bstFromPreorder(vector<int> &preorder)
{
    if (preorder.size() == 0)
        return nullptr;
    idx = 0;
    return createBst(preorder, -1e9, +1e9);
}

//leetcode 222: count nodes for a complete tree.=================================
//exploit the property of complete tree.
class Solution
{
public
    int leftHeight(TreeNode root)
    {
        if (root == null)
            return -1;
        return leftHeight(root.left) + 1;
    }

public
    int rightHeight(TreeNode root)
    {
        if (root == null)
            return -1;
        return rightHeight(root.right) + 1;
    }

public
    int countNodes(TreeNode root)
    {
        if (root == null)
            return 0;
        int lh = leftHeight(root);
        int rh = rightHeight(root);
        if (lh == rh) //it is a complete binary tree with left and right heigt equal we can calculate nodes from formula.
            return (int)Math.pow(2, lh + 1) - 1;
        else
            return countNodes(root.left) + countNodes(root.right) + 1; /*call recursively for the left and right St and plus 1, the left or right St maybe a full binary tree and we'll use formula for that*/
    }
}

// check if the tree is a mirror
class Solution
{

public
    boolean isSymmetric(TreeNode root1, TreeNode root2)
    {
        if (root1 == null && root2 == null)
            return true;
        if (root1 == null || root2 == null || root1.val != root2.val)
            return false;

        return isSymmetric(root1.left, root2.right) && isSymmetric(root1.right, root2.left);
    }

public
    boolean isSymmetric(TreeNode root)
    {
        if (root == null || (root.left == null && root.right == null))
            return true;
        return isSymmetric(root.left, root.right);
    }
}

//same tree.======================================
class Solution
{
public
    boolean isSameTree(TreeNode p, TreeNode q)
    {
        if (p == null && q == null)
        {
            return true;
        }
        if (p == null || q == null || p.val != q.val)
        {
            return false;
        }

        return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }
}

// 662. Maximum Width of Binary Tree

//Important trick : dont use normal width concept,

//for each node, for its level, the left child is 2*level+1 and right child is 2*level+2

//in each level , maintain the first and the last node's level, consider them as array indices and calculate length.=======
class Solution
{
public:
    int widthOfBinaryTree(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        queue<pair<TreeNode *, long>> q;
        q.push({root, 0});
        long ans = 1;

        while (q.size() != 0)
        {
            int sz = q.size();
            long first = -1; //the levels could go beyond the range of the
            long last = -1;
            while (sz-- > 0)
            {
                pair<TreeNode *, int> p = q.front();
                q.pop();
                long level = p.second;

                if (first == -1)
                {
                    first = level;
                }
                last = level;

                if (p.first->left != nullptr)
                {
                    q.push({p.first->left, 2 * level + 1});
                }
                if (p.first->right != nullptr)
                {
                    q.push({p.first->right, 2 * level + 2});
                }
            }
            ans = max(ans, last - first + 1);
        }

        return ans;
    }
};

//Maintain the stack as recursion stack, keep the minimum on top before the query comes.
//to get the ceil value, go to right's leftmost for a node.
class BSTIterator
{
    Stack<TreeNode> st;
public
    BSTIterator(TreeNode root)
    {
        st = new Stack<>();
        TreeNode temp = root;
        while (temp != null)
        {
            st.push(temp);
            temp = temp.left;
        }
    }

    /** @return the next smallest number */
public
    int next()
    { //for the next query , we need to set the minimum on stack top. so next minimum of the current item
        //will be found on the leftmost of the right of the cureent stack top.
        TreeNode rvtx = st.pop();
        TreeNode temp = rvtx.right;
        while (temp != null)
        {
            st.push(temp);
            temp = temp.left;
        }
        return rvtx.val;
    }

    /** @return whether we have a next smallest number */
public
    boolean hasNext()
    {
        return (st.size() != 0);
    }
}

//serialize and deserialize,=====================================
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (root == nullptr)
        {
            return "X,";
        }

        string str = "";
        string left = serialize(root->left);
        string right = serialize(root->right);
        str = to_string(root->val) + "," + left + right;
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        //0 for no child, 1 for left child, 2 for right child
        if (data == "X,")
            return nullptr;
        stack<pair<TreeNode *, int>> st;
        int i = 0;
        int hd = 0;
        while (data[i] != ',')
            hd = hd * 10 + (data[i++] - '0');
        TreeNode *head = new TreeNode(hd);
        st.push({head, 0});
        i++;

        while (i < data.length())
        {

            TreeNode *child;
            if (data[i] == 'X')
            {
                child = nullptr;
                i += 2;
            }
            else
            {
                int idx = i;
                int num = 0;
                while (data[idx] != ',')
                    num = num * 10 + (data[idx++] - '0');

                child = new TreeNode(num);
                i = idx + 1;
            }

            if (!st.empty())
            {
                pair<TreeNode *, int> par = st.top();
                st.pop();

                if (par.second == 0)
                {
                    par.first->left = child;
                    par.second++;
                    st.push(par);
                    if (child != nullptr)
                        st.push({child, 0});
                }

                else if (par.second == 1)
                {
                    par.first->right = child;
                    par.second++;
                    // st.push(par);
                    if (child != nullptr)
                        st.push({child, 0});
                }
            }
        }
        return head;
    }
};

//cousins of binary tree.===========================================
class Solution
{
public
    boolean path(TreeNode root, int data, ArrayList<Integer> al)
    {
        if (root == null)
            return false;
        if (root.val == data)
        {
            al.add(data);
            return true;
        }
        boolean l = path(root.left, data, al);
        if (l)
        {
            al.add(root.val);
            return true;
        }
        boolean r = path(root.right, data, al);
        if (r)
        {
            al.add(root.val);
            return true;
        }

        return false;
    }

public
    boolean isCousins(TreeNode root, int x, int y)
    {
        if (root == null)
            return false;
        ArrayList<Integer> xx = new ArrayList<>();
        path(root, x, xx);

        ArrayList<Integer> yy = new ArrayList<>();
        path(root, y, yy);

        if (xx.size() == yy.size())
        {
            if (xx.get(1) == yy.get(1))
            { //same parent
                return false;
            }
            return true;
        }
        else
            return false;
    }
}

//leetcode: 1443.================================================
//3 versions.=====

//key point, think about a single node, then two node with one apple, remember the point of adding 2....
class Solution
{
public:
    int total = 0;
    pair<bool, int> find(int src, vector<vector<int>> &graph, vector<bool> &check, vector<bool> &vis)
    {

        vis[src] = true;

        pair<bool, int> myP = {false, 0};
        int val = 0;
        for (int i = 0; i < graph[src].size(); i++)
        {
            if (!vis[graph[src][i]])
            {
                pair<bool, int> ret = find(graph[src][i], graph, check, vis);
                if (ret.first)
                {
                    val += ret.second + 2;
                }
            }
        }

        if (val == 0)
        { //no true came from child
            return {check[src], 0};
        }

        return {true, val};
    }

    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> vis(n, false);

        total = 0;
        for (bool val : hasApple)
            if (val)
                total++;

        if (total == 0)
            return 0;
        else
            return find(0, graph, hasApple, vis).second;
    }
};

//using pair
class Solution
{
public:
    int total = 0;
    pair<bool, int> find(int src, vector<vector<int>> &graph, vector<bool> &check, vector<bool> &vis)
    {

        vis[src] = true;

        pair<bool, int> myP = {false, 0};
        int val = 0;
        for (int i = 0; i < graph[src].size() && total > 0; i++)
        {
            if (!vis[graph[src][i]])
            {
                pair<bool, int> ret = find(graph[src][i], graph, check, vis);
                if (ret.first)
                {
                    val += ret.second + 2;
                }
            }
        }

        if (val == 0)
        { //no true came from child
            return {check[src], 0};
            total--;
        }

        return {true, val};
    }

    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> vis(n, false);

        total = 0;
        for (bool val : hasApple)
            if (val)
                total++;

        if (total == 0)
            return 0;
        else
            return find(0, graph, hasApple, vis).second;
    }
};

//using single int and total check.======================
class Solution
{
public:
    int total = 0;
    int find(int src, vector<vector<int>> &graph, vector<bool> &check, vector<bool> &vis)
    {

        vis[src] = true;

        int val = 0;
        for (int i = 0; i < graph[src].size() && total > 0; i++)
        {
            if (!vis[graph[src][i]])
            {
                int ret = find(graph[src][i], graph, check, vis);
                if (ret != -1)
                {
                    val += ret + 2;
                }
            }
        }

        if (val == 0)
        { //no true came from child
            if (check[src])
                return 0;
            return -1;
        }

        return val;
    }

    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> vis(n, false);

        total = 0;
        for (bool val : hasApple)
            if (val)
                total++;

        if (total == 0)
            return 0;
        else
            return find(0, graph, hasApple, vis);
    }
};

//leetcode: 1443 ends...================================================

// we can only make a full binary tree, IMPORTANT
//construct tree from pre and post :: key point is to find the left child of root in preorder array , then find the pos of the same
//in post order array, now calculate the nodes of left child from by using the post order array, no of left child nodes = (found_pos-ppsi+1)
class Solution
{
public:
    TreeNode *build(int psi, int pei, int ppsi, int ppei, vector<int> &pre, vector<int> &post)
    {
        if (psi > pei || ppsi > ppei)
        {
            return nullptr;
        }

        if (psi == pei || ppsi == ppei)
        { //important case, stop here, otherwise, it will start considering psi+1 as left child which greater than pei
            return new TreeNode(pre[psi]);
        }

        TreeNode *root = new TreeNode(pre[psi]);

        int found = ppsi; //traversal from start of post array
        while (post[found] != pre[psi + 1])
            found++; //position of left child of root in the post array

        //no of elements in left st
        int noe = found - ppsi + 1;
        root->left = build(psi + 1, psi + 1 + noe - 1, ppsi, found, pre, post);
        root->right = build((psi + 1 + noe - 1) + 1, pei, found + 1, ppei - 1, pre, post);

        return root;
    }
    TreeNode *constructFromPrePost(vector<int> &pre, vector<int> &post)
    {
        if (pre.size() == 0 || post.size() == 0)
            return nullptr;
        return build(0, pre.size() - 1, 0, post.size() - 1, pre, post);
    }
};

//construct tree from level order and inorder.===================
Node *buildTree(int isi, int iei, vector<int> &inorder, vector<int> &levelOrder)
{

    if (isi > iei)
        return nullptr;
    if (isi == iei)
        return new Node(inorder[isi]);

    Node *root = new Node(levelOrder[0]);
    unordered_set<int> map;

    int idx = isi;
    while (inorder[idx] != root->key)
    {
        map.insert(inorder[idx]);
        idx++;
    }

    vector<int> left_level;
    vector<int> right_level;

    for (int i = 1; i < levelOrder.size(); i++)
    { //start from first pos.========================
        int ele = levelOrder[i];

        if (map.find(ele) != map.end())
            left_level.push_back(ele);
        else
            right_level.push_back(ele);
    }

    root->left = buildTree(isi, idx - 1, inorder, left_level);
    root->right = buildTree(idx + 1, iei, inorder, right_level);

    return root;
}

Node *buildTree(int inorder[], int levelOrder[], int iStart, int iEnd, int n)
{
    if (n == 0)
        return nullptr;
    //add code here.
    vector<int> in;
    vector<int> level;
    for (int i = 0; i < n; i++)
    {
        in.push_back(inorder[i]);
        level.push_back(levelOrder[i]);
    }
    return buildTree(0, n - 1, in, level);
}

// https://practice.geeksforgeeks.org/problems/merge-two-bst-s/1
// Given two BST, Return elements of both BSTs in sorted form.
vector<int> merge(Node *r1, Node *r2)
{
    stack<Node *> st1;
    stack<Node *> st2;

    Node *c1 = r1;
    while (c1 != nullptr)
    {
        st1.push(c1);
        c1 = c1->left;
    }

    Node *c2 = r2;
    while (c2 != nullptr)
    {
        st2.push(c2);
        c2 = c2->left;
    }

    vector<int> ans;

    while (st1.size() != 0 && st2.size() != 0)
    {
        if ((st1.top()->data) > (st2.top()->data))
        {
            Node *rvtx = st2.top();
            st2.pop();

            ans.push_back(rvtx->data);
            Node *temp = rvtx->right;
            while (temp != nullptr)
            {
                st2.push(temp);
                temp = temp->left;
            }
        }
        else
        {
            Node *rvtx = st1.top();
            st1.pop();

            ans.push_back(rvtx->data);

            Node *temp = rvtx->right;
            while (temp != nullptr)
            {
                st1.push(temp);
                temp = temp->left;
            }
        }
    }

    while (st1.size() != 0)
    {
        Node *rvtx = st1.top();
        st1.pop();

        ans.push_back(rvtx->data);

        Node *temp = rvtx->right;
        while (temp != nullptr)
        {
            st1.push(temp);
            temp = temp->left;
        }
    }

    while (st2.size() != 0)
    {
        Node *rvtx = st2.top();
        st2.pop();

        ans.push_back(rvtx->data);

        Node *temp = rvtx->right;
        while (temp != nullptr)
        {
            st2.push(temp);
            temp = temp->left;
        }
    }

    return ans;
}

//subtree with given sum
int cc = 0;

int find(Node *root, int X)
{
    if (root == nullptr)
        return 0;

    int l = find(root->left, X);

    int r = find(root->right, X);

    if ((l + r + root->data) == X)
        cc++;

    return (l + r + root->data);
}

int countSubtreesWithSumX(Node *root, int X)
{
    // Code here
    if (root == nullptr)
        return 0;

    cc = 0;
    find(root, X);
    return cc;
}

// we are returning this object
//(isBst,SumofBst,MINIMUM value of bst, MAXIMUM value of bst)
class Solution
{
public:
    pair<pair<bool, int>, pair<int, int>> find(TreeNode *root, int &ln)
    {
        if (root == nullptr)
            return {{true, 0}, {INT_MAX, INT_MIN}};

        //(isBst,SumofBst,MINIMUM value of bst, MAXIMUM value of bst)
        pair<pair<bool, int>, pair<int, int>> ll = find(root->left, ln);
        pair<pair<bool, int>, pair<int, int>> rr = find(root->right, ln);

        if (ll.first.first && rr.first.first)
        {
            bool res = true;

            //ll.second.second is the maximum value of the left BST
            if (root->left != nullptr && ll.second.second >= root->val)
            {
                res = false;
            }

            //rr.second.first is the minimum value of the right BST
            if (root->right != nullptr && rr.second.first <= root->val)
            {
                res = false;
            }

            //current true becomes bst,then find the attributes
            if (res)
            {

                //ll.first.second and rr.first.second represents the sum of left BST and right BST
                int csum = ll.first.second + rr.first.second + root->val;

                //maintainng the maximum bst
                ln = max(ln, csum);

                // ll.second.first represents the minimum of left BST
                int cmin = min(root->val, ll.second.first);

                // rr.second.second represents the maximum of right BST
                int cmax = max(root->val, rr.second.second);

                return {{true, csum}, {cmin, cmax}};
            }
        }

        //as we dont check non-bst nodes, so other arguments doesnt matter much..
        return {{false, 0}, {0, 0}};
    }

    int maxSumBST(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int ln = 0;
        find(root, ln);
        return ln;
    }
};

// 1038. Binary Search Tree to Greater Sum Tree
class Solution
{
public:
    //traverse in the order : right root left, so as to maintain the sum of greater elements in ln varibale
    void rgtNodelft(TreeNode *root, int &ln)
    {
        if (root == nullptr)
            return;

        rgtNodelft(root->right, ln);

        //now ln contains the sum of elements greater than the root, as we need to consider the root as well, so add it in the ln variable
        //and update root->val, then go for left
        ln += root->val;
        root->val = ln;

        rgtNodelft(root->left, ln);
        return;
    }

    TreeNode *bstToGst(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;
        int ln = 0;
        rgtNodelft(root, ln);
        return root;
    }
};
