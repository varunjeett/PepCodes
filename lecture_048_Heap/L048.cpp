#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Time complexity for Building a Binary Heap is O(n).
// Each call to upheapify and downHeapify takes O(log n).
// For Adding an element we push_back at last , and then call upHeapify for that element(log n) time
// For Deleting an element, we swap it with the last, decrease array size and call downheapify for top element.
void display(int idx,vector<int> &arr)
{
    if(idx >= arr.size())
        return ;

    string str="";
    if((2*idx)+1 < arr.size())
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
    //create a max heap , O(n) time
    for(int i=arr.size()-1;i>=0;i--)
    {
        downHeapify(i,arr.size(),arr);
    }

    // remove one-by-one from top (n * log n)
    for(int last=arr.size()-1;last>=0;last--)
    {
        //swap first element and last element (first being the heaviest comes at the last of the array)
        swap(arr[0],arr[last]);

        //heapofy before last
        downHeapify(0,last,arr);
    }

    //O(n) 
    for(int ele:arr)
    {
        cout<<ele<<" ";
    }
}


void solve()
{
    vector<int> arr={10,20,30,40,50,60,70,80,90,100,110,120,130};
    display(0,arr);
    cout<<"****************"<<endl;
    heapSort(arr);
}
int main()
{
    solve();
}