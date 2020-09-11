#include <iostream>
using namespace std;

// 2 pointer i, j
// for each i, find the smallest element in the unsorted array and place it on i+1 and increment i.
// it will go (n^2) in the best case as well, best case is when array is already sorted.

//worst and avg case is also (n^2)
void select(int arr[], int n)
{
    int i = -1;
    while (i < n - 2)
    {
        cout<<i<<endl;
        int mn=i+1;
        for (int j=i+1;j<n;j++)
        {
            if(arr[j] < arr[mn])
            {
                mn=j;
            }
        }
        swap(arr[++i],arr[mn]);
    }

    for(int k=0;k<n;k++)
    {
        cout<<arr[k]<<" ";
    }
}

// in one pass of bubble sort, we swap adjacent elements if they are not in order
// keep passing till elements gets swapped,in best case, (already sorted array) , it will go for O(n) only.
// because no swapping will be done, so we won't pass it again

// worst case, reverse sorted array,in one pass the heaviest element is positioned at the right place
void bubble(int arr[], int n)
{
    for(int i=0;i < n-1;i++)
    {
        int ct=0;
        for(int j=0;j<n-1;j++)
        {
            int k=j+1;
            if(arr[j] > arr[k])
            {
                swap(arr[j],arr[k]);
                ct++;
            }
        }

        if(ct==0)
            break;
    }

    for(int k=0;k<n;k++)
    {
        cout<<arr[k]<<" ";
    }
}


// start from the first element , check if the previous is greater if yes then swap, and keep going behind till
// we place it at the right position, we maintain sorted array behind i

//the best case complexity is O(n),, in the worst case it is O(n^2).
void insert(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        int j=i;
        while(j>0 && arr[j-1] > arr[j])
        {
            swap(arr[j-1],arr[j]);
            j--;
        }
    }

    for(int k=0;k<n;k++)
    {
        cout<<arr[k]<<" ";
    }
}

int main()
{
    int arr[] = {13,2,1,5,3,7,9,5,13,67,1,55};
    int n = 12;
    // select(arr, n);
    // bubble(arr, n);
    // insert(arr, n);
}