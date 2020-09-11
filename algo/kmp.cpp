#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void buildTable(string &arr, vector<int> &table)
{
    table[0] = 0;
    int i = 0;
    for (int j = 1; j < arr.length(); j++)
    {
        if (arr[i] == arr[j])
        {
            table[j] = i + 1;
            i++;
        }
        else
        {
            //go to the previous matching location 
            while (i != 0 && arr[i] != arr[j])
            {
                i = table[i - 1];
            }

            //2 possibilities, either i becomes zero or arr[i] equals arr[j]
            if (arr[i] == arr[j])
            {
                table[j] = i + 1;
                i++;
                continue;
            }

            //i=0 and arr[i] is not equal to arr[j], nothing matches
            table[j] = 0; 
        }
    }
    return;
}

void kmp(string &s, string &t, vector<int> &table)
{
    int i = 0; //pointer on s
    int j = 0; //pointer on t
    while (i < s.length())
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
            if (j == t.length())
            {
                cout << "Found at index :" << i - t.length() << endl;
                j = 0;
            }
        }
        else //mismatch prevent the overdoing of work
        {
            if (j == 0)
            {
                i++;
                continue;
            }
            else
            {
                j = table[j - 1]; //going to the point where proper suffix ends.
            }
        }
    }
}

void solve()
{
    string s = "aabaabaaaabaabaaaabaabaa";
    string t = "aabaabaaa";
    vector<int> table(t.length(), 0);
    buildTable(t, table);
    for(int ele:table)
    cout<<ele<<" ";
    kmp(s, t, table);
}

int main()
{
    solve();
    return 0;
}