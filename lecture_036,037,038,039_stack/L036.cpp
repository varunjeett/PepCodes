#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Mystack{

    int N=1000;
    int * arr;
    int len=0;
    int tos=-1;

    public:

    Mystack(){
        arr=new int[N];
    }
    Mystack(int lenn){
        arr=new int[lenn];
    }

    int size(){
        return this->len;
    }
    bool isEmpty(){
        return (this->len==0);
    }

    void push(int val){
        arr[++tos]=val;
        len++;
    }
    void pop(){
        if(tos > -1)
        arr[tos]=0;
        tos--;
        len--;
    }
   
    int top(){
        if(tos > -1){
            return arr[tos];
        }else
        {
            return -1;
        }
        
    }

};

void solve(){
    Mystack s;
    cout<<s.isEmpty()<<endl;

    for(int i=0; i<10; i++){
        s.push(i*10);
    }

    while(s.size()!=0){
        cout<<s.top()<<" ";
        s.pop();
    }
}

vector<int> ngor(vector<int>& arr){ //first greater on right
    
    stack <int> st;
    vector<int> ans(arr.size(), arr.size());
    for(int i=0; i<arr.size(); i++){
        while(st.size()!=0 && arr[st.top()] < arr [i] )
        {
            ans[st.top()]=i;    //answer of st.top() has been found
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

vector<int> nsor(vector<int>& arr){ //first smaller on right
    
    stack <int> st;
    vector<int> ans(arr.size(), arr.size());
    for(int i=0; i<arr.size(); i++){
        while(st.size()!=0 && arr[st.top()] > arr [i] )
        {
            ans[st.top()]=i;    //answer of st.top() has been found
            st.pop();
        }
        st.push(i);
    }
    return ans;
}


void question(){
   
    vector <int> arr={2,-1,8,6,9,4,3,5};
    vector <int> ans=nsor(arr);
    for(int e:ans){
        cout<<e<<",";
    }
}

int main(){
    
   // solve();
    question();
}