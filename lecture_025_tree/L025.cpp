#include <iostream>
#include <vector>
#include <queue>

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

int idx = 0;
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

int ll = +1e8;
int rr = -1e8;
int range = 0;

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

void verticalView_PQ(TreeNode *root) //normal
{
    if (root == nullptr)
        return;

    priority_queue<pair<TreeNode *, int>, vector<pair<TreeNode *, int>>, myComp> q;
    width(root, 0);
    range = rr - ll + 1;

    vector<vector<int>> arr(range, vector<int>());

    q.push({root, (-ll)});      //adding ll to add the nodes so that from -2 .... 3 becomes 0 to 5.

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

    int i = 0;
    for (vector<int> ar : arr)
    {
        cout << "Level" << i++ << ": ";
        for (int ele : ar)
            cout << ele << ",";
        cout << endl;
    }

    return;
}

void solve()
{
    vector<int> arr = {10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    TreeNode *head = constructTree(arr);
    display(head);
    verticalView_PQ(head);
}

int main()
{
    solve();
}
