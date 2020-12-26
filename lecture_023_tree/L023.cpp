#include <iostream>
#include <vector>

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
TreeNode* constructTree(vector<int> &arr)
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

int height(TreeNode *node)
{
    if (node == nullptr)
        return -1;

    return max(height(node->left), height(node->right)) + 1;
}

int size_(TreeNode *node)
{
    if (node == nullptr)
        return 0;

    return size_(node->left) + size_(node->right) + 1;
}

bool find(TreeNode *node, int ele)
{
    if (node == nullptr)
        return false;

    if (node->val == ele)
        return true;

    bool res = find(node->left, ele) || find(node->right, ele);

    return res;
}

vector<int> rootToNode(TreeNode *node, int ele)
{
    if (node == nullptr)
    {
        return {};
    }

    if (node->val == ele)
    {
        vector<int> ret;
        ret.push_back(node->val);
        return ret;
    }

    vector<int> left = rootToNode(node->left, ele);
    if (left.size() != 0)
    {
        left.push_back(node->val);
        return left;
    }

    vector<int> right = rootToNode(node->right, ele);
    if (right.size() != 0)
    {
        right.push_back(node->val);
        return right;
    }

    return {};
}

void solve()
{
    vector<int> arr = {10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    TreeNode *head = constructTree(arr);
    display(head);
    cout << height(head) << endl;
    cout << size_(head) << endl;
    const vector<int> &ans = rootToNode(head, 100);
    for (int ele : ans)
        cout << ele << ",";
}

int main()
{
    solve();
}