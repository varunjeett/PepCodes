#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//ql = query left
//qr = query right
//current segment left = ll, current segment right = rr
//idx is the index of the element which contain info about the current window

void update(int idx, int ll, int rr, vector<int> &st, int pos, int new_val)
{
    if (ll == rr)
    {
        st[idx] = new_val;
        return;
    }

    int mid = ll + (rr - ll) / 2;
    if (pos <= mid)
    {
        update((idx * 2) + 1, ll, mid, st, pos, new_val);
    }
    else
    {
        update((idx * 2) + 2, mid + 1, rr, st, pos, new_val);
    }

    st[idx] = st[(idx * 2) + 1] + st[(idx * 2) + 2];
    return;
}

void updateQuery(int pos, int new_val, vector<int> &arr, vector<int> &st)
{
    if (pos < 0 || pos >= arr.size())
    {
        return;
    }

    arr[pos] = new_val;
    update(0, 0, arr.size() - 1, st, pos, new_val);
    return;
}

//current segment is always in range, its the query range which gets distorted.
int getSum(int idx, int ql, int qr, int ll, int rr, vector<int> &st)
{
    if (ql > qr) //window gets distorted, superflous call
    {
        return 0;
    }

    if (ql == ll && qr == rr)
    {
        return st[idx];
    }

    int mid = (ll + rr) / 2;
    
    //in recursive calls, both the current segment and required segment gets divided

    int a = min(qr, mid);
    int b = max(mid + 1, ql);

    int left_st = getSum((idx * 2) + 1, ql, a, ll, mid, st);

    int right_st = getSum((idx * 2) + 2, b, qr, mid + 1, rr, st);

    return left_st + right_st;
}

int sumQuery(int left, int right, vector<int> &arr, vector<int> &st)
{
    if (left > right || left < 0 || right >= arr.size())
    {
        return 0;
    }

    return getSum(0, left, right, 0, arr.size() - 1, st);
}

void constructST(vector<int> &arr, vector<int> &st, int idx, int ll, int rr)
{
    if (ll == rr)
    {
        st[idx] = arr[ll]; //or arr[rr];
        return;
    }

    int mid = ll + (rr - ll) / 2;

    //for the left st : go from ll to mid
    constructST(arr, st, (idx * 2) + 1, ll, mid);

    //for the left st : go from mid+1 to rr
    constructST(arr, st, (idx * 2) + 2, mid + 1, rr);

    //post order
    st[idx] = st[(idx * 2) + 1] + st[(idx * 2) + 2];
    return;
}

void solve()
{
    int sum = 0;
    vector<int> arr = {1, 2, 4, -1, 4, 1, 12, 8, 9, 100};

    int height = ceil(log2(arr.size()));   //height of segment tree
    int max_size = 2 * pow(2, height) - 1; //maximum nodes that can be fit in that height
    vector<int> st(max_size, 0);

    int ll = 0;
    int rr = arr.size() - 1;
    constructST(arr, st, 0, ll, rr);

    //range query
    cout << sumQuery(2, 2, arr, st);

    //updateQuery
    // cout<<st[0]<<endl;
    // updateQuery(9,200,arr,st);
    // cout<<st[0]<<endl;
}

int main()
{

    solve();
    return 0;
}