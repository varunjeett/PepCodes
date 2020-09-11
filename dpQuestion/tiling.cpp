#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//simple 2*w plot, and 2*1 tile
long long int find(int w, vector<long long int> &dp)
{
    if (w <= 1)
    {
        return dp[w] = 1;
    }

    if (dp[w] != -1)
    {
        return dp[w];
    }

    long long int ver = find(w - 1, dp);
    long long int hor = find(w - 2, dp);

    return dp[w] = (ver + hor);
}
int main()
{
    //code
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int l;
        cin >> l;
        vector<long long int> dp(l + 1, -1);
        cout << find(l, dp) << endl;
    }
    return 0;
}
