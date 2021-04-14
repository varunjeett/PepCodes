#include <bits/stdc++.h>
using namespace std;

struct mycomp
{
    bool operator()(const vector<int> &left, const vector<int> &right)
    {
        return left[0] > right[0];
    }
};

int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency, int k)
{
    if (k == 0)
        return 0;

    vector<vector<int>> arr;
    for (int i = 0; i < n; i++)
    {
        arr.push_back({speed[i], efficiency[i]});
    }

    sort(arr.begin(), arr.end(), [](auto &left, auto &right) {
        if (left[1] == right[1])
            return left[0] > right[0];
        return left[1] > right[1];
    });

    for (int i = 0; i < n; i++)
    {
        cout << arr[i][0] << "," << arr[i][1] << endl;
    }

    priority_queue<vector<int>, vector<vector<int>>, mycomp> pq;

    long long int speedsum = 0;
    long long int maxPerform = LONG_MIN;

    for (auto &e : arr)
    {
        int curspeed = e[0];
        int cureff = e[1];

        cout << curspeed << "cur" << cureff << endl;

        if (pq.size() == k)
        {
            vector<int> rvtx = pq.top();
            pq.pop();

            cout << "Removed"
                 << " " << rvtx[0] << " " << rvtx[1] << endl;

            speedsum -= rvtx[0];
        }

        speedsum += curspeed;
        maxPerform = max(maxPerform, speedsum * cureff);
        cout << maxPerform << endl;
        pq.push(e);
    }

    int mod = pow(10, 9) + 7;
    int ans = (int)(maxPerform % mod);
    return ans;
}

int main()
{
    int n = 6;
    vector<int> speed = {2, 10, 3, 1, 5, 8};
    vector<int> eff = {5, 4, 3, 9, 7, 2};
    int k = 3;

    cout << maxPerformance(n, speed, eff, k) << endl;
    return 0;
}