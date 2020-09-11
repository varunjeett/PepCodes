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

class node
{
public:
    TreeNode *pred;
    TreeNode *succ;

    node()
    {
        this->pred = new TreeNode();
        this->succ = new TreeNode();
    }
};

//the whole point is , for any node , its pred will be smaller than the node, now two case, when left St of node exits : finf the
// righmost element, as it will be jst smaller than node, and hence it will be its pred.
// case 2: when left doesnt exist, now the jst smaller element will be that element from where we took a right turn from during our find journey so we'll keep on updating from where we took a right turn.
// ,,, similarly two case for succ, when right St exists or Not, if exist then it will be the leftmost of right st or if not exist then last element from where we took a left turn.
// as it will be jst greater than the node, and that is our succ

void inorder_pred_succ(TreeNode *root, int data, node *obj)
{
    if (root == nullptr)
        return;
    TreeNode *cur = root;
    while (cur != nullptr)
    {
        if (cur->val == data)
        {
            //pred
            if (cur->left == nullptr)
            {
                //we have already set our pred.
            }
            else
            {
                TreeNode *ans = cur->left;
                while (ans->right != nullptr)
                    ans = ans->right;
                obj->pred = ans;
            }

            //succ
            if (cur->right == nullptr)
            {
                //we have already set our pred.
            }
            else
            {
                TreeNode *ans = cur->right;
                while (ans->left != nullptr)
                    ans = ans->left;
                obj->succ = ans;
            }

            break;
        }

        else if (data < cur->val) // we are taking a left turn so , the element could be a possible succ as it is greater than data
        {
            obj->succ = cur;
            cur = cur->left;
        }

        else // we are taking a right turn so , the element could be a possible pred as it is less than data
        {
            obj->pred = cur;
            cur = cur->right;
        }
    }
}

TreeNode* addEle(TreeNode *root, int ele)
{
    if (root==nullptr)
    {
        return new TreeNode(ele);
    }

    if (ele < root->val)
    {
        root->left = addEle(root->left, ele);   //neccche value add krke apna address apne parent ko return krdo.
    }
    else if (ele > root->val)
    {
        root->right = addEle(root->right, ele);  //neccche value add krke apna address apne parent ko return krdo.
    }

    return root;
}

TreeNode* removeEle(TreeNode* root, int ele)
{
    if (root==nullptr)
    {
        return nullptr;
    }

    if (ele < root->val)
    {
        root->left = removeEle(root->left, ele);   //neccche value add krke apna address apne parent ko return krdo.
    }

    else if (ele > root->val)
    {
        root->right = removeEle(root->right, ele);  //neccche value add krke apna address apne parent ko return krdo.
    }

    else    //found
    {
        //first handle the case of one child (two subcases) and no child
        if(root->left==nullptr || root->right==nullptr)
        {
            return (root->left==nullptr ? root->right : root->left);
        }

        TreeNode* temp=root->left;
        while (temp->right!=nullptr)
        {
            temp=temp->right;
        }

        root->val=temp->val;
        root->left=removeEle(root->left,temp->val);
    }

    return root;
}


void set1(TreeNode* root)
{
    root=addEle(root,71);
    display(root);
    cout<<endl;
    root=removeEle(root,120);
    display(root);
}

void solve()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
    TreeNode *root = constructTree(arr, 0, arr.size() - 1);
    display(root);
    // node* obj=new node();
    // inorder_pred_succ(root,130,obj);
    // cout<<obj->pred->val;
    // cout<<endl;
    // cout<<obj->succ->val;
    set1(root);
}

int main()
{
    solve();
}