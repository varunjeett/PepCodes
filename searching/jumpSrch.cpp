#include<iostream>
#include<cmath>

using namespace std;

int find(int arr[] ,int n, int ele)
{
    if(ele < arr[0])
        return -1;

    int jmp=sqrt(n);
    int i=0;

    //stop when arr[i] is larger than ele
    while(i < n && ele >= arr[i])
    {
        if(ele==arr[i])
            return i;

        i+=jmp;
    }

    int st=i-jmp;
    // cout<<st<<endl;
    while(st < n && st!=i+1)
    {
        if(arr[st]==ele)
            return st;
        else
        {
            st++;
        }
    }

    return -1;

}

int main()
{
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 }; 
    int n=16;
    int ele=0;
    int pos=find(arr,n,ele);
    cout<<pos<<endl;
}