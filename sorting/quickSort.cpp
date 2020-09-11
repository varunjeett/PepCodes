#include <iostream>
#include <vector>

using namespace std;

int partition(int st,int ed,vector<int> &arr,int pivot)
{
    int i=st-1;
    int j=st;
    while (j <= ed)
    {
        if(arr[j] <= pivot)
        {
            ++i;
            swap(arr[i],arr[j]);
        }
        j++;
    }
    return i;
}

void quickSort(int st,int ed,vector<int> &arr)
{
    if(st >= ed)
        return ;

    srand(0);
    // random number in a range
    // st + (rand()%(ed-st+1));
    // st + (0 to ed-st)
    // (st to ed)

    //Randomized Quick Sort
    // int randomidx=st+(rand()%(ed-st+1));
    // int pivot=arr[randomidx];
    
    int pivot=arr[ed]; //normal quick sort

    int pos=partition(st,ed,arr,pivot);

    quickSort(st,pos-1,arr);
    quickSort(pos+1,ed,arr);

    return;
}

int main()
{
    vector<int> arr={2,5,10,12,8,9,13,10,19,20,10,2,5,10,12,8,9,13,2,5,10,12,8,9,13,10,19,20,2,5};
    quickSort(0,arr.size()-1,arr);
    for(int ele:arr)
    {
        cout<<ele<<" ";
    }
}