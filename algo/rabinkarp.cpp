#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int createHash(string &s,int st,int ed)
{
    int base=26;
    int sum=0;
    int expo=0;
    for(int i=ed;i>=st;i--)
    {
        int val=(s[i]-'a')*pow(base,expo++);
        sum+=val;
    }
    return sum;
}

bool isMatch(string &s,string &t,int i,int j)
{
    for(int idx=i,k=0; idx<=j && k<t.length() ;idx++,k++)
    {
        if(s[idx]!=t[k])
        {
            return false;
        }
    }
    
    return true;
}

void rabinkarp(string &s,string &t)
{
    if(s.length() < t.length())
        return ;
    
    int t_code=createHash(t,0,t.length()-1);
    int s_code=createHash(s,0,t.length()-1);
    
    if(s_code==t_code)
    {
        if(isMatch(s,t,0,t.length()-1))
            cout<<"Found at index: 0"<<endl;
    }
    
    int x=t.length();
    int base=26;
    
    for(int i=1; i<=(s.length()-x); i++)
    {
        int prev=(s[i-1]-'a');
        prev=prev*26*26;
        int val=s_code-prev;
        val*=26;
        
        val+=(s[i+x-1]-'a');
        s_code=val;                  //whole logic: 0 1 2 :initially, subtract 0 and ADD 3  
        
        if(s_code==t_code)
        {   
            if(isMatch(s,t,i,i+t.length()-1))
                cout<<"Found at index: "<<i<<endl;
        }
    }
    
    return;
    
}

void solve()
{
    string s="abcdefcdecde";
    string t="cde";
    rabinkarp(s,t);
}

int main()
{
    solve();
	return 0;
}