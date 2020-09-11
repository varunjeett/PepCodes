#include <iostream>
#include <vector>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        this->val = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    TreeNode(int ele)
    {
        this->val = ele;
        this->left = nullptr;
        this->right = nullptr;
    }
};

TreeNode *constructTree(vector<int> &arr, int si, int ei)
{
    if (si > ei)
    {
        return nullptr;
    }

    int mid = (si + ei) / 2;
    TreeNode *root = new TreeNode(arr[mid]);
    root->left = constructTree(arr, si, mid - 1);
    root->right = constructTree(arr, mid + 1, ei);

    return root;
}

void display(TreeNode *root)
{

    if (root == nullptr)
    {
        return;
    }

    string str = "";

    str = str + (root->left == nullptr ? "." : to_string(root->left->val));
    str = str + " <- " + to_string(root->val) + " -> ";
    str = str + (root->right == nullptr ? "." : to_string(root->right->val));

    cout << str << endl;

    display(root->left);
    display(root->right);

    return;
}

int height(TreeNode *root)
{

    if (root == nullptr)
    {
        return -1; //no of edges
    }

    return max(height(root->left), height(root->right)) + 1;
}

int sizeOfTree(TreeNode *root)
{

    if (root == nullptr)
    {
        return 0; //no of nodes
    }

    return sizeOfTree(root->left) + sizeOfTree(root->right) + 1;
}

int minEle(TreeNode *root)
{

    if (root == nullptr)
        return -1;

    TreeNode *curr = root;

    while (curr->left != nullptr)
    {
        curr = curr->left;
    }

    return curr->val;
}

int maxEle(TreeNode *root)
{

    if (root == nullptr)
        return -1;

    TreeNode *curr = root;

    while (curr->right != nullptr)
    {
        curr = curr->right;
    }

    return curr->val;
}

//recursive
bool findEle(TreeNode *root, int data)
{
    if (root == nullptr)
        return false;

    if (root->val == data)
        return true;
    else if (data < root->val)
        return findEle(root->left, data);
    else
        return findEle(root->right, data);
}

//iterative
bool findEle02(TreeNode *root, int data)
{
    TreeNode *cur = root;
    while (cur != nullptr)
    {
        if (cur->val == data)
            return true;
        else if (data < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return false;
}

TreeNode *addEle(TreeNode *root, int data)
{
    if (root == nullptr)
        return new TreeNode(data);

    if (data < root->val)
    {
        root->left = addEle(root->left, data);
    }

    else
    {
        root->right = addEle(root->right, data);
    }

    return root;
}

TreeNode *remEle(TreeNode *root, int data)
{

    if (root == nullptr)
        return nullptr;

    if (root->val > data)
    {
        root->left = remEle(root->left, data);
    }

    else if (root->val < data)
    {
        root->right = remEle(root->right, data);
    }

    else
    {

        if (root->left == nullptr || root->right == nullptr)
        {
            return (root->left == nullptr ? root->right : root->left);
        }

        int maxInLeft = maxEle(root->left);
        root->val = maxInLeft;
        root->left = remEle(root->left, maxInLeft);
    }

    return root;
}

void set1(TreeNode *root)
{

    // cout << height(root) << endl
    //      << endl;

    // cout << sizeOfTree(root) << endl
    //      << endl;

    // cout << maxEle(root) << endl
    //      << endl;

    // cout << minEle(root) << endl
    //      << endl;

    // cout << (boolalpha) << findEle(root, 15) << endl
    //      << endl;

    // cout << (boolalpha) << findEle02(root, 120) << endl
    //      << endl;

    int add = 71;

    addEle(root, add);
    cout << "adding " << add << endl;
    display(root);

    cout << endl;

    remEle(root, 71);
    cout << "removing " << add << endl;
    display(root);
}

//recursive.==============================
TreeNode *lca_recur(TreeNode *root, int a, int b)
{
    if (root == nullptr)
        return nullptr;

    if (a < root->val && b < root->val)
        return lca_recur(root->left, a, b);
    else if (a > root->val && b > root->val)
        return lca_recur(root->right, a, b);
    else
    {
        if (findEle(root, a) && findEle(root, b))
            return root;
        else
            return nullptr;
    }
}

//iterative.==============================
TreeNode *lca(TreeNode *root, int a, int b) // a<b
{
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (b < curr->val && a < curr->val)
            curr = curr->left;
        else if (a > curr->val && b > curr->val)
            curr = curr->right;
        else
        {
            if (findEle(root, a) && findEle(root, b))
                return root;
            else
                return nullptr;
        }
    }

    return nullptr;
}

static  int count = 0;
void inRange(TreeNode *root, int a, int b, vector<int> &ans)
{
    count++;    //no of calls
    if (root == nullptr)
        return;

    inRange(root->left, a, b, ans);

    if (a <= root->val && root->val <= b)
        ans.push_back(root->val);

    inRange(root->right, a, b, ans);

    return;
}

void inRange01(TreeNode *root, int a, int b, vector<int> &ans)
{
    count++;    //no of calls
    if (root == nullptr)
        return;

    if (a <= root->val)     //if(a > root->val), then all left values will be smaller than a,(out of range),hence no need to traverse
        inRange01(root->left, a, b, ans);

    if (a <= root->val && root->val <= b)
        ans.push_back(root->val);

    if (b > root->val)       //if(b < root->val), then all right values will be greater than b,(out of range),hence no need to traverse
        inRange01(root->right, a, b, ans);

    return;
}

int inorder_prev = (int)-1e8;
bool validateBST(TreeNode *root)
{
    if (root == nullptr)
        return false;

    if (validateBST(root->left))
        return true;

    if (inorder_prev > root->val)
    {
        //this cannt happen in a bst
        return true;
    }

    inorder_prev = root->val;

    if (validateBST(root->right))
        return true;

    return false;
}

TreeNode *a = nullptr;
TreeNode *b = nullptr;
TreeNode *c = nullptr;

bool recover(TreeNode *root)
{
    if (root == nullptr)
        return false;

    if (recover(root->left))
        return true;

    if (c != nullptr && c->val > root->val)
    {
        b = root;
        if (a == nullptr)
        {
            a = c;
        }
        else
        {
            return true;
        }
    }

    c = root;
    if (recover(root->right))
        return true;

    return false;
}

void recoverTree(TreeNode *root)
{ //in a bst if we swap two values, the bst is disturbed , swap them again
    recover(root);
    if (a != nullptr)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
    return;
}

void set2(TreeNode *root)
{
    cout << endl;

    // TreeNode *ans = lca_recur(root, 90, 120);
    // if (ans == nullptr)
    //     cout << "-1";
    // else
    //     cout << ans->val;
    // cout<<endl;

    vector<int> arr;
    inRange(root, 20, 60, arr);
    cout<<"count is "<< count <<endl;
    for (int ele : arr)
        cout << ele << ",";

    cout << endl;

    count = 0;
    arr.clear();
    inRange01(root, 20, 60, arr);
    cout<<"count is "<< count <<endl;
    for (int ele : arr)
        cout << ele << ",";

    cout << endl;

    // bool val=validateBST(root);
    // if(val) cout<<"not a bst";
    // else{
    //     cout<<" a bst";
    // }

    // recoverTree(root);
}

//set3==============================================================
class allSol
{
public:
    int hei = 0;
    int size = 0;
    bool find = false;

    TreeNode *pred = nullptr;
    TreeNode *previ = nullptr;
    TreeNode *succ = nullptr;
};

void allSolFun(TreeNode *root, int data, int level, allSol *obj)
{

    if (root == nullptr)
        return;
    obj->size++;
    obj->hei = max(obj->hei, level);
    obj->find = obj->find || (root->val == data);

    allSolFun(root->left, data, level + 1, obj);

    if (obj->pred == nullptr && root->val == data)
        obj->pred = obj->previ;

    if (obj->previ != nullptr && obj->previ->val == data && obj->succ == nullptr)
        obj->succ = root;

    obj->previ = root;

    allSolFun(root->right, data, level + 1, obj);

    return;
}

void set3(TreeNode *root)
{

    allSol *obj = new allSol();

    allSolFun(root, 100, 0, obj);

    cout << obj->find << endl;
    cout << obj->hei << endl;
    cout << obj->size << endl;

    cout << obj->pred->val << endl;
    cout << obj->succ->val << endl;

    return;
}

void solve()
{

    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
    TreeNode *root = constructTree(arr, 0, arr.size() - 1);
    display(root);
    set1(root);
    // set2(root);
    // display(root);
    // set3(root);
}

int main()
{
    solve();
}