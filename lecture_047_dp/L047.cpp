#include <iostream>
#include <vector>
#include <climits>
#include <unordered_set>

using namespace std;

void display(vector<int> &arr)
{
    for (int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}

int findWays(string str)
{
    int n = str.length();

    if (n <= 2)
        return 0;

    int A_count = 0;
    int B_count = 0;
    int C_count = 0;

    for (int i = 0; i < n; i++)
    {
        if (str[i] == 'a')
        {
            int no = A_count;      // nahi aane ki choice
            int yes = 1 + A_count; //aane ki choice -- peeche vale ke saath + khud ke saath
            A_count = no + yes;    //newly updated
        }
        else if (str[i] == 'b')
        {
            int no = B_count;            // nahi aane ki choice
            int yes = A_count + B_count; //aane ki choice -- peeche vale ke saath + khud ke saath
            B_count = no + yes;          //newly updated
        }
        else
        {
            int no = C_count;            // nahi aane ki choice
            int yes = B_count + C_count; //aane ki choice -- peeche vale ke saath + khud ke saath
            C_count = no + yes;          //newly updated
        }
    }
    return C_count;
}

void aibjck()
{
    string str;
    cin >> str;
    cout << findWays(str) << endl;
}

//wordbreak.====================================================
unordered_set<string> map;

int wordBreak_memo(int idx, string &s, int n, vector<string> &dict, vector<int> &dp)
{
    if (idx == n)
    {
        return dp[idx] = 1;
    }

    if (dp[idx] != -1)
        return dp[idx];

    bool res = false;
    
    for (int i = idx; i < n && !res; i++)
    {
        string findit = s.substr(idx, i - idx + 1);
        if (map.find(findit) != map.end())
            res = res || (wordBreak_memo(i + 1, s, n, dict, dp) == 1 ? true : false);
    }
    return dp[idx] = res ? 1 : 0;
}

bool wordBreak(string s, vector<string> &dict)
{
    int n = s.length();
    if (n == 0)
        return false;

    for (string str : dict)
    {
        map.insert(str);
    }

    vector<int> dp(n + 1, -1);

    bool res = (wordBreak_memo(0, s, n, dict, dp) == 1 ? true : false);
    display(dp);
    return res;
}


int wordBreak_tab(int idx, string &s, int n, vector<string> &dict, vector<int> &dp)
{
    for (idx = n; idx >= 0; idx--)
    {
        if (idx == n)
        {
            dp[idx] = 1;
            continue;
        }

        bool res = false;
        for (int i = idx; i < n && !res; i++)
        {
            string findit = s.substr(idx, i - idx + 1);
            if (map.find(findit) != map.end())
                res = res || (dp[i + 1] == 1 ? true : false);
        }
        dp[idx] = res ? 1 : 0;
    }

    return dp[0];
}

bool wordBreak(string s, vector<string> &dict)
{
    int n = s.length();
    if (n == 0)
        return false;

    for (string str : dict)
    {
        map.insert(str);
    }

    vector<int> dp(n + 1, -1);

    bool res = (wordBreak_tab(n, s, n, dict, dp) == 1 ? true : false);

    return res;
}

void wordbreak()
{
    vector<string> arr = {"leet", "code"};
    cout << (boolalpha) << wordBreak("leetcode", arr);
}

void solve()
{
    // aibjck();
    // wordbreak();
}

int main()
{
    solve();
}
