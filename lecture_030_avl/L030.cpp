#include<iostream>
#include<vector>

using namespace std;

class TreeNode{

public:

    int val;
    TreeNode* left=nullptr;
    TreeNode* right=nullptr;
    int bal=0;
    int height=0;

    TreeNode(int data){
      
        this->val=data;
        this->left=nullptr;
        this->right=nullptr;
        this->bal=0;
        this->height=0;

    }

    TreeNode(){
      
        this->val=0;
        this->left=nullptr;
        this->right=nullptr;
        this->bal=0;
        this->height=0;
    }

};

int findMax(TreeNode* root){
 
    if(root==nullptr){
        return -1;
    }
    
    TreeNode* cur=root;

    while(cur->right!=nullptr){

        cur=cur->right;

    }

    return cur->val;
}

void updateHnB(TreeNode* root){
   
    int lh=-1;
    int rh=-1;

    if(root->left!=nullptr) lh=root->left->height;
    if(root->right!=nullptr) rh=root->right->height;

    root->height=max(lh,rh)+1;
    root->bal=lh-rh;
    
    return;

}

TreeNode* ll(TreeNode* a){
    
    TreeNode* b=a->left;
    TreeNode* b_ka_right=b->right;

    b->right=a;
    a->left=b_ka_right;

    updateHnB(a);
    updateHnB(b);
    return b;
}

TreeNode* rr(TreeNode* a){
    
    TreeNode* b=a->right;
    TreeNode* b_ka_left=b->left;

    b->left=a;
    a->right=b_ka_left;

    updateHnB(a);
    updateHnB(b);

    return b;
}

TreeNode* getRotate(TreeNode* root){

    updateHnB(root);

    if(root->bal==2){  //ll, lr

        if(root->left->bal==1){ //ll
            return ll(root);
        }

        else if(root->left->bal==-1){  //lr
            root->left=rr(root->left);
            return ll(root);        
        }

    }
    
    else if(root->bal==-2){  //rr , rl
        
        if(root->right->bal==-1){ //rr
            return rr(root);
        }

        else if(root->right->bal==1){  //rl
            root->right=ll(root->right);
            return rr(root);           
        }

    }
    return root;
}

TreeNode* constructTree(vector <int> arr, int si, int ei){

    if(si > ei){
        return nullptr;
    }

    int mid=(si+ei)/2;
    TreeNode* root=new TreeNode(arr[mid]);
    root->left=constructTree(arr, si, mid-1);
    root->right=constructTree(arr, mid+1, ei);
    
    return getRotate(root);
}


TreeNode* addNode(TreeNode* root, int data){
    
    if(root==nullptr) {
        return new TreeNode(data);  //leaf ke liye hum getRotate nhi chala rhe.
    }
    
    if(data > root->val){
        root->right=addNode(root->right, data);
    }

    else if(data > root->val){
        root->right=addNode(root->right, data);
    }

    return getRotate(root);

}

TreeNode* removeNode(TreeNode* root, int data){
     
    if(root==nullptr){
        return nullptr;
    }
    
    if(data > root->val){
        root->right=removeNode(root->right, data);
    }
   
    else if(data < root->val){
        root->left=removeNode(root->left, data);
    }

    else{
       
        if(root->left==nullptr || root->right==nullptr){
            return (root->left==nullptr) ? root->right : root->right;
        }
        else{

            int maxInLeft=findMax(root->left);
            root->val=maxInLeft;
            root->left=removeNode(root->left, maxInLeft);

        }
      
    }
    
    return getRotate(root);
}

void display(TreeNode* root){
   
    if(root==nullptr){
        return;
    }

    string str="";
    
    str+=(root->left==nullptr) ? "." : to_string(root->left->val);
    str+=" <- " + to_string(root->val) + "(" + to_string(root->bal) + " , " +  to_string(root->height) + ")"  + " -> ";
    str+=(root->right==nullptr) ? "." : to_string(root->right->val);
    
    cout<<str<<endl;

    display(root->left);
    display(root->right);

    return;
    
}

void solve(){
    

    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
    TreeNode* root=constructTree(arr,0,arr.size()-1);
    display(root);
    addNode(root, 140);
    addNode(root, 150);
    display(root);
    cout<<"\n"<<findMax(root);
    
   
}

int main(){
    solve();
}