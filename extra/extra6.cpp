#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>

using namespace std;


double f(double d)
{
    cout<<fixed;
    setprecision(6);
    return 123.12;
}
int main()
{
    // int num=1300451;
    // // string s="1230045671";
    // string s=to_string(num);
    // sort(s.begin(),s.end());
    // int i=0;
    // while(s[i]=='0')
    // i++;
    // swap(s[0],s[i]);
    // cout<<s<<endl;
    // double i=1;
    // double dd=f(i);
    // cout<<dd<<endl;

    int a=17;
    int b=2120;
    cout<<(a&b)<<endl;
    int x=(a&b);
    cout<<(x&b)<<endl;
    cout<<(x&a)<<endl;
}


