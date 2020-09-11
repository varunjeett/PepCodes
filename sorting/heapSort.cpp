#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//recursion on array, level order
void display(int idx,vector<int> &arr)
{
    if(idx >= arr.size())
        return ;

    string str="";
    if( (2*idx)+1 < arr.size())
    {
        str+=to_string(arr[(2*idx)+1]);
    }

    str+=" <- " + to_string(arr[idx]) + " -> ";

    if((2*idx)+2 < arr.size())
    {
        str+=to_string(arr[(2*idx)+2]);
    }

    cout<<str<<endl;
    display((2*idx)+1, arr);
    display((2*idx)+2, arr);

    return ;
}

//max Heap
void downHeapify(int idx,int last,vector<int> &arr)
{
    if(idx >= last)
    return ;

    int newparent=idx;

    if((2*idx)+1 < last && arr[(2*idx)+1] > arr[newparent])
    newparent=(2*idx)+1 ;

    if((2*idx)+2 < last && arr[(2*idx)+2] > arr[newparent])
    newparent=(2*idx)+2 ;

    if(newparent!=idx)
    {
        swap(arr[idx],arr[newparent]);
        downHeapify(newparent,last,arr);
    }
}

void heapSort(vector<int> &arr)
{
    //create a maxHeap
    //it will take 2n time
    for(int i=arr.size()-1;i>=0;i--)
    {
        downHeapify(i,arr.size(),arr);
    }

    //for each element call heapify, (nlogn) time, in-place sorting
    for(int last=arr.size()-1;last>=0;last--)
    {
        //swap first element and last element (first being the heaviest comes at the last of the array)
        swap(arr[0],arr[last]);

        //heapofy before last
        downHeapify(0,last,arr);
    }

    for(int ele:arr)
    {
        cout<<ele<<" ";
    }
}


//used for adding an element to the heap;
void upHeapify(int idx, vector<int> & arr)
{
    if(idx < 0)
    return ;

    int newparent=idx;

    if((idx-1)/2 >= 0 && arr[(idx-1)/2] < arr[idx])
    newparent=(idx-1)/2 ;

    if(newparent!=idx)
    {
        swap(arr[idx],arr[newparent]);
        upHeapify(newparent,arr);
    }
}

void insert(int ele,vector<int> & arr)
{
    arr.push_back(ele);
    upHeapify(arr.size()-1,arr);
}

void solve()
{
    vector<int> arr={10,20,30,40,50,60,70,80,90,100,110,120,130};
    for(int i=arr.size()-1;i>=0;i--)
    {
        downHeapify(i,arr.size(),arr);
    }

    display(0,arr);
    cout<<"***********"<<endl;
    insert(500,arr);
    cout<<"***********"<<endl;
    display(0,arr);

}
int main()
{
    solve();
}