#include <iostream>
#include <vector>

using namespace std;

vector<string> subseq_byreturn(string str)
{
    if (str.length() == 0)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    char ch = str[0];

    vector<string> smallAns = subseq_byreturn(str.substr(1)); //2 ^ (n-1)
    vector<string> myAns;

    for (string s : smallAns)//2^n-1
    {
        myAns.push_back(ch + s);
        myAns.push_back(s);
    }

    return myAns;// 2^n
}

int subseq_byvoid(string str, string ans)
{
    if (str.length() == 0)
    {
        cout << ans << " ";
        return 1;
    }

    int count = 0;

    char ch = str[0];

    count += subseq_byvoid(str.substr(1), ans + ch);
    count += subseq_byvoid(str.substr(1), ans);

    return count;
}

string buttons[] = {"yz", ":;/", "abc", "def", "ghi", "jkl", "mno", "pqrs", "uv", "wx", "*#", "+-/"};

vector<string> nokiaKeypad_byReturn(string str)
{
    if (str.length() == 0)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    char ch = str[0];

    string button = buttons[ch - '0'];

    vector<string> smallAns = nokiaKeypad_byReturn(str.substr(1));
    vector<string> myAns;

    for (int i = 0; i < button.length(); i++)
    {

        char letterOfButton = button[i];

        for (string s : smallAns)
        {
            myAns.push_back(letterOfButton + s);
        }
    }

    return myAns;
}

// my approach
//create a new list at every position

void nokiaKeypad_byVoid2(int idx,string str, vector<string> ans)
{
    if (str.length() == idx)
    {
        for (string s : ans)
        {
            cout << s << " ";
        }
        return ; 
    }

    char ch = str[idx];
    string button = buttons[ch - '0'];
    vector<string> newans;

    for (string ss : ans)
    {
        for (int i = 0; i < button.length(); i++)
        {
            newans.push_back(ss+button[i]);
        }
    }

    nokiaKeypad_byVoid2(idx+1,str,newans);

    return;
}


//k^n
int nokiaKeypad_byVoid1(string str, string ans)
{
    if (str.length() == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;

    int first_digit = str[0] - '0';
    string button = buttons[first_digit];
    
    string use=str.substr(1);//N time

    for (int i = 0; i < button.length(); i++)
    {
        count += nokiaKeypad_byVoid1(use, ans + button[i]);
    }

    return count;
}

void set1()
{

    // vector <string> arr=subseq_byreturn("abcd");
    // for(string s:arr){
    //     cout<<s<<endl;
    // }

    // int res=subseq_byvoid("abcd","");
    // cout<<res;

    // vector <string> ans=nokiaKeypad_byReturn("23");

    // for(string s:ans){
    //     cout<<s<<" ";
    // }

    int res = nokiaKeypad_byVoid1("589", "");
    cout << res;

    cout<<"----------------------------"<<endl;

    vector <string> ans;
    ans.push_back("");
    nokiaKeypad_byVoid2(0,"589",ans);
}

void solve()
{
    set1();
}

int main()
{
    solve();
}
