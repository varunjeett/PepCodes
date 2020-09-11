#include <bits/stdc++.h>

using namespace std;

long nextGreaterElement(int n)
{
    string str = "";
    str += to_string(n);
    int i, j;
    int len = str.length();
    j = len - 2;

    while (j >= 0 && (str[j] - '0') >= (str[j + 1] - '0'))
        j--;
    cout << j << endl;

    if (j >= 0)
    {
        i = len - 1;
        while (i > j && (str[j] - '0') >= (str[i] - '0'))
            i--;

        cout << i << endl;
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }

    j++;
    i = len - 1;

    while (j < i)
    {

        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;

        i--;
        j++;
    }

    long num = stoi(str);
    if (num > INT_MAX)
        return -1;
    return num;
}

string decodeString(string s)
{
    vector<char> st;
    for (char ch : s)
    {
        if (ch == ']')
        {
            string temp = "";

            while (st.size() != 0 && st.back() != '[')
            {
                temp += st.back();
                st.pop_back();
            }

            st.pop_back();
            reverse(temp.begin(), temp.end());

            string times = "";
            while (isdigit(st.back()))
            {
                times += st.back();
                st.pop_back();
            }
            cout << times;
            reverse(times.begin(), times.end());

            int time = stoi(times);

            while (time-- > 0)
                for (char c : temp)
                    st.push_back(c);
        }
        else
            st.push_back(ch);
    }

    string ans = "";
    for (char c : st)
        ans += c;

    return ans;
}

priority_queue<int, vector<int>> pq;
void dfs(int sr, int sc, int sum, vector<vector<int>> &mat, int k)
{
    if (sr == mat.size() - 1)
    {
        // cout << sum + mat[sr][sc] << endl;
        pq.push(sum + mat[sr][sc] );
        if(pq.size() > k)
          pq.pop();
        return ;
    }

    for (int i = 0; i < mat[0].size(); i++)
        dfs(sr + 1, i, sum + mat[sr][sc], mat, k);

    return;
}

int kthSmallest(vector<vector<int>> &mat, int k)
{
    int n = mat.size();
    int m = mat[0].size();

    for (int i = 0; i < m; i++)
    {
        dfs(0, i, 0, mat, k);
    }
    return pq.top();
}

int main()
{

    //code
    // cout<<nextGreaterElement(138576531);
    // cout << decodeString("100[leetcode]");

    vector<vector<int>> mat = {{1, 3, 11}, {2, 4, 6}};
    cout << kthSmallest(mat,3);
}