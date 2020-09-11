#include <bits/stdc++.h>
using namespace std;

// 10, 7, 8, 12, 6, 8

bool f(int time,vector<int> &arr,int K,int t)
{
    int total=0;
    int k=0;
    int cur=0;
    for(int ele:arr)
    {
        cur+=(ele*t);
        if(cur > time)//assign it to new member
        {
            cur=(ele*t);
            k++;
        }

        if(k == K)//total members exceed than given
        {
            return false;
        }
    }

    return true;
}


int find(int k,int t,vector<int> &arr)
{
    int left=0;
    int sum=0;
    for(int ele:arr)
    {
        sum+=ele;
    }
    int right=sum*t;

    while(left < right)
    {
        int mid=left+(right-left)/2;

        if(f(mid,arr,k,t))
        {
            right=mid;
        }
        else
        {
            left=mid+1;
        }
        
    }

    return left;


}

int main() {
	//code
	int k = 4, T = 5;
    vector<int> job = {10, 7, 8, 12, 6, 8};
    cout << find(4,5,job);
}