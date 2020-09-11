#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>

using namespace std;

bool dfs(char src, map<char, vector<char>> &graph, vector<bool> &vis, vector<bool> &myPath, vector<char> &ans)
{
    if (vis[src - 'a'])
    {
        if (myPath[src - 'a'])
            return true; // as in true for cycle exits
        return false;
    }

    vis[src - 'a'] = myPath[src - 'a'] = true;

    bool res = false;

    for (char ele : graph[src])
    {
        res = res || dfs(ele, graph, vis, myPath, ans);
    }

    ans.push_back(src); //since we are pushing them in the stack,the order will be reversed....
    myPath[src - 'a'] = false;
    return res;
}

string findOrder(string dict[], int N, int K)
{
    // Your code here
    map<char, vector<char>> graph;
    unordered_set<char> map;
    //key is to check the two adjacent elements and determine which character make the difference
    //make our graph on that basis, from smaller to higher.

    for (int i = 0; i < N - 1; i++)
    {
        string word1 = dict[i];
        string word2 = dict[i + 1];

        for (char ch : word1)
        {
            graph[ch];
            map.insert(ch);
        }

        for (char ch : word2)
        {
            graph[ch];
            map.insert(ch);
        }

        for (int pos = 0; pos < word1.size() && pos < word2.size(); pos++)
        {
            if (word1[pos] != word2[pos])
            {
                // cout << word1[pos] << "->" << word2[pos] << ",";
                graph[word1[pos]].push_back(word2[pos]);
                break;
            }
        }
    }

    vector<int> indegree(26, 0);
    for (auto i : graph)
    {
        for (char c : i.second)
        {
            indegree[c - 'a']++;
        }
    }
    // cout<<endl;

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 0; i < 26; i++)
    {
        if (map.find((char)(i + 'a')) != map.end())
        {
            // cout << (char)(i + 'a') << indegree[i] << endl;
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
    }

    string ans = "";
    while (q.size() != 0)
    {
        int num = q.top();
        q.pop();

        char rvtx = (char)(num + 'a');
        ans += rvtx;
        for (char child : graph[rvtx])
        {
            if (--indegree[child - 'a'] == 0)
            {
                q.push(child - 'a');
            }
        }
    }

    if (ans.length() == map.size())
        return ans;
    else
        return "";
}

void solve()
{
    string dict[] = {"xyz", "abcd"};
    int N = sizeof(dict) / sizeof(dict[0]);
    int k = 4;
    cout << findOrder(dict, N, k) << endl;
}

int main()
{
    solve();
}
