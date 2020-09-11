#include <iostream>
#include <vector>

using namespace std;

void display_bool(vector<bool> &arr)
{
    for (bool ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D_bool(vector<vector<bool>> &arr)
{
    for (vector<bool> ar : arr)
        display_bool(ar);
    cout << endl;
}

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

//Substring and Subsequence Series.=========================================================================

vector<vector<bool>> isPalindromeSubstring(string str)
{
    int n = str.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap <= 2 && str[i] == str[j])
            {
                dp[i][j] = true;
                continue;
            }

            dp[i][j] = (str[i] == str[j] && dp[i + 1][j - 1]) ? true : false;
        }
    }
    return dp;
}

vector<vector<int>> PalindromeSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap <= 2 && str[i] == str[j])
            {
                dp[i][j] = gap + 1;
                continue;
            }

            dp[i][j] = (str[i] == str[j] && dp[i + 1][j - 1]) ? gap + 1 : 0;
        }
    }
    return dp;
}

int countPalindromeSubstring(string str)
{
    int n = str.length();
    int count = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap <= 2 && str[i] == str[j])
            {
                dp[i][j] = true;
                count++;
            }

            else
            {
                dp[i][j] = (str[i] == str[j] && dp[i + 1][j - 1]) ? true : false;
                if (dp[i][j])
                    count++;
            }
        }
    }
    return count;
}

string longestPalindromeSubstring(string str)
{
    int n = str.length();
    int maxlen = 0;
    int si = 0;
    int ei = 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap <= 2 && str[i] == str[j])
            {
                dp[i][j] = gap + 1;
            }

            else
            {
                dp[i][j] = (str[i] == str[j] && dp[i + 1][j - 1]) ? gap + 1 : 0;
            }

            if (dp[i][j] > maxlen)
            {
                maxlen = dp[i][j];
                si = i;
                ei = j;
            }
        }
    }

    display2D(dp);
    return str.substr(si, ei - si + 1);
}

int longestpalindromeSubseq_rec(string s, int si, int ei, vector<vector<int>> &isPalindrome, vector<vector<int>> &dp)
{
    if (isPalindrome[si][ei] != 0) //jb si se leke ei tk hi palindrome substring ho
        return dp[si][ei] = isPalindrome[si][ei];

    if (dp[si][ei] != 0)
        return dp[si][ei];

    int ans = 0;

    if (s[si] == s[ei])
    {
        ans = longestpalindromeSubseq_rec(s, si + 1, ei - 1, isPalindrome, dp) + 2;
    }

    else
    {
        ans = max(longestpalindromeSubseq_rec(s, si + 1, ei, isPalindrome, dp), longestpalindromeSubseq_rec(s, si, ei - 1, isPalindrome, dp));
    }

    return dp[si][ei] = ans;
}

int longestPalindromeSubseq_DP(string str, int si, int ei, vector<vector<int>> &dp, vector<vector<bool>> &isPalindrome)
{
    int n = str.length();

    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            if (isPalindrome[si][ei])
            {
                dp[si][ei] = ei - si + 1;
                continue;
            }

            int ans = 0;

            if (str[si] == str[ei])
            {
                ans = dp[si + 1][ei - 1] + 2;
            }

            else
            {
                ans = max(dp[si + 1][ei], dp[si][ei - 1]);
            }

            dp[si][ei] = ans;
        }
    }
    return dp[0][n - 1];
}

int longestPalindromeSubseq_DP_02(string str, int si, int ei, vector<vector<int>> &dp)
{
    int n = str.length();

    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            if (gap == 0)
            {
                dp[si][ei] = 1;
                continue;
            }

            if (gap == 1)
            {
                dp[si][ei] = (str[si] == str[ei]) ? 2 : 1;
                continue;
            }

            int ans = 0;

            if (str[si] == str[ei])
            {
                ans = dp[si + 1][ei - 1] + 2;
            }

            else
            {
                ans = max(dp[si + 1][ei], dp[si][ei - 1]);
            }
            dp[si][ei] = ans;
        }
    }
    display2D(dp);
    return dp[0][n - 1];
}

int longestPalindromeSubseq(string s)
{
    int n = s.length();
    if (n == 1)
        return 1;

    int si = 0;
    int ei = n - 1;

    // vector<vector<int>> isPalindrome = PalindromeSubstring(s);
    // vector<vector<int>> dp(n, vector<int>(n, 0));
    // int ans = longestpalindromeSubseq_rec(s, 0, ei, isPalindrome, dp);
    // display2D(dp);
    // return ans;

    vector<vector<bool>> isPalindrome = isPalindromeSubstring(s);
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int ret = longestPalindromeSubseq_DP(s, 0, ei, dp, isPalindrome);
    display2D(dp);
    return ret;

    // vector<vector<int>> dp(n, vector<int>(n, 0));
    // return longestPalindromeSubseq_DP_02(s,si,ei,dp);
}

int findDistinct_memo(string &s, string &t, int i, int j, int s_len, int t_len, vector<vector<int>> &dp)
{
    if (s_len - i < t_len - j)
        return dp[i][j] = 0;

    if (j == t_len)
        return dp[i][j] = 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    int ans = 0;
    if (s[i] == t[j])
    {
        ans = (findDistinct_memo(s, t, i + 1, j + 1, s_len, t_len, dp) + findDistinct_memo(s, t, i + 1, j, s_len, t_len, dp));
    }
    else
    {
        ans = findDistinct_memo(s, t, i + 1, j, s_len, t_len, dp);
    }
    return dp[i][j] = ans;
}

int findDistinct_tab(string &s, string &t, int i, int j, int s_len, int t_len, vector<vector<int>> &dp)
{

    for (int i = s_len; i >= 0; i--)
    {
        for (int j = t_len; j >= 0; j--)
        { 
            // length of pattern is more than the string to be found in
            // therefore no ways are possible
            if (s_len - i < t_len - j)
            {
                dp[i][j] = 0;
                continue;
            }

            //empty pattern to be found
            if (j == t_len)
            {
                dp[i][j] = 1;
                continue;
            }

            int ans = 0;
            if (s[i] == t[j])
            {
                ans = dp[i + 1][j + 1] + dp[i + 1][j];
            }
            else
            {
                ans = dp[i + 1][j];
            }
            dp[i][j] = ans;
        }
    }

    return dp[0][0];
}

//in how many ways 't' is occuring in 's'
int numDistinct(string s, string t)
{
    int s_len = s.length();

    int t_len = t.length();

    vector<vector<int>> dp(s_len + 1, vector<int>(t_len + 1, -1));
    // int ans = findDistinct_memo(s, t, 0, 0, s_len, t_len, dp);
    int ans = findDistinct_tab(s, t, 0, 0, s_len, t_len, dp);
    display2D(dp);
    return ans;
}

void distinctSubseq()
{
    string t = "gks";
    string s = "geeksforgeeks";
    cout << numDistinct(s, t);
}

int countAll_memo(string str, int i, int j, vector<vector<int>> &dp)
{
    if (i > j)
        return dp[i][j] = 0;

    if (i == j)
        return dp[i][j] = 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    int middle = countAll_memo(str, i + 1, j - 1, dp);
    int first_inc = countAll_memo(str, i, j - 1, dp);
    int last_inc = countAll_memo(str, i + 1, j, dp);
    int ans = 0;

    if (str[i] == str[j])
    {
        ans = 1 + first_inc + last_inc;
    }
    else
    {
        ans = first_inc + last_inc - middle;
    }
    return dp[i][j] = ans;
}

int countAll_tab(string str, int n, vector<vector<int>> &dp)
{
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
            {
                dp[i][j] = 1;
                continue;
            }

            int middle = dp[i + 1][j - 1];
            int first_inc = dp[i][j - 1];
            int last_inc = dp[i + 1][j];

            int ans = 0;
            if (str[i] == str[j])
            {
                //first and last equal
                // case 1: sare middle vale subseq ke aage peeche lagkr bnne wale
                // case 2: i se start hoke, j-1 ke beechme aane wale subseq
                // case 3: i+1 se start hoke j ke beechme aane wale subseq
                // case 4: sirf start character or end character ka subseq
                // add the above four

                // but, we are counting i+1 se start hoke j-1 pe tk hone wale subseq twice 
                // first time in (i+1 to j) and second time (i to j-1), so subtract (i+1,j-1)
                ans = (1 + first_inc + middle + last_inc) - middle;
            }

            else
            {
                //first and last NOT equal, therefore we cannot have them together in one subsequnce

                // case 1: i se start hoke, j-1 ke beechme aane wale subseq
                // case 2: i+1 se start hoke j ke beechme aane wale subseq
                // add up them

                // but, we are counting i+1 se start hoke j-1 pe tk hone wale subseq twice 
                // first time in (i+1 to j) and second time (i to j-1), so subtract (i+1,j-1)

                ans = (first_inc + last_inc) - middle;
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][n - 1];
}

void countPalindromeSubseq()
{
    string t = "abccbaba";
    int n = t.length();
    vector<vector<int>> dp_memo(n, vector<int>(n, -1)); //for memo
    cout << countAll_memo(t,0, n-1, dp_memo) << endl;
    // vector<vector<int>> dp_tab(n, vector<int>(n, 0)); //for tab
    // cout << countAll_tab(t, n, dp_tab) << endl;
    display2D(dp_memo);
}

void stringSubstringSet()
{
    // string str = "abcd";
    // string str = "geeksforgeeks";
    // cout << longestPalindromeSubseq(str) << endl;
    distinctSubseq();
    // countPalindromeSubseq();
}

int main()
{
    stringSubstringSet();
}
