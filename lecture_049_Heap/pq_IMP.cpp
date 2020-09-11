#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>


//normal queue : push ,pop, front
//priority queue : push , pop , top (top as in its a heap) 

using namespace std;

void pq()
{
    // priority_queue<int, vector<int>> pq;  //by default max
    // priority_queue<int, vector<int>, greater<int>> pq;  //min pq by using greater

    vector<int> arr{12, 45, 12, 456, 78, 34, 12, 46, -11, 456, -123};
    priority_queue<int, vector<int>, less<int>> pq(arr.begin(), arr.end());
    cout << pq.top();
    pq.push(1000);
    pq.pop();
}

void solve()
{
}

int main()
{
    solve();
}