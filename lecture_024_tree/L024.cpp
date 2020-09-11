#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class TreeNode
{
public:
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode(int ele)
    {
        this->val = ele;
    }
};

static int idx = 0;
TreeNode *constructTree(vector<int> &arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        idx++;
        return nullptr;
    }

    TreeNode *node = new TreeNode(arr[idx++]);
    node->left = constructTree(arr);
    node->right = constructTree(arr);

    return node;
}

void display(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    string str = "";
    str += (root->left == nullptr ? "." : to_string(root->left->val));
    str += " <- " + to_string(root->val) + " -> ";
    str += (root->right == nullptr ? "." : to_string(root->right->val));

    cout << str << endl;

    display(root->left);
    display(root->right);

    return;
}

static TreeNode *lca;
bool LCA(TreeNode *node, int p, int q)
{
    if (node == nullptr)
        return false;

    bool self = false, left = false, right = false;

    if (node->val == p || node->val == q)
        self = true;

    left = LCA(node->left, p, q);
    if (lca != nullptr)
    {
        return true;
    }

    right = LCA(node->right, p, q);
    if (lca != nullptr)
    {
        return true;
    }

    if ((self && left) || (self && right) || (left && right))
        lca = node;

    return self || right || left;
}

void addNodes(TreeNode *root, TreeNode *block, int k, vector<int> &ans)
{
    if (root == nullptr)
    {
        return;
    }

    if (k == 0)
    {
        ans.push_back(root->val);
        return;
    }

    if (root->left != block)
        addNodes(root->left, block, k - 1, ans);

    if (root->right != block)
        addNodes(root->right, block, k - 1, ans);

    return;
}

int printNodesKdown(TreeNode *root, int ele, int k, vector<int> &ans)
{
    if (root == nullptr)
        return -1;

    if (root->val == ele)
    {
        addNodes(root, nullptr, k, ans);
        return k - 1;
    }

    int ll = printNodesKdown(root->left, ele, k, ans);
    if (ll != -1)
    {
        addNodes(root, root->left, ll, ans);
        return ll - 1;
    }

    int rr = printNodesKdown(root->right, ele, k, ans);
    if (rr != -1)
    {
        addNodes(root, root->right, rr, ans);
        return rr - 1;
    }

    return -1;
}

vector<int> distanceK(TreeNode *root, TreeNode *target, int K)
{
    if (root == nullptr || target == nullptr)
        return {};
    vector<int> ans;
    printNodesKdown(root, target->val, K, ans);
    return ans;
}

void kdown(TreeNode *root)
{
    TreeNode *target = new TreeNode(60);
    const vector<int> &ans = distanceK(root, target, 2);
    for (int ele : ans)
        cout << ele << ",";
}

void solve()
{
    vector<int> arr = {10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, 130, -1, -1, 140, -1, -1, 150, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    TreeNode *head = constructTree(arr);
    display(head);
    // lca = nullptr;
    // LCA(head, 120, 140);
    // cout << lca->val;

    kdown(head);
}

int main()
{
    solve();
}
