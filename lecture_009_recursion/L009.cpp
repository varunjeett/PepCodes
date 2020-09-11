#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//wordbreak=========================================================
//leetcode 139
bool wordBreak01(string s, vector<string>& wordDict) {
        
        if(s=="")
        {
            return true;
            
        }
        
        int flag=false;
        
        for(int i=1;i<=s.length();i++)
        {  
            
           string smallAns=s.substr(0,i);
           
           for(string check:wordDict)
           {
               if(smallAns==check)
               {
                 flag = true;
                 flag = flag &&  wordBreak01(s.substr(i),wordDict) ;
               }
               
               if(flag) return true;
               
           }
            
        }
        
        return flag;
               
}

//for wordbreak 02=========
unordered_set<string> map;

int wordBreak02(string str,string ans){   
    
    if(str.length()==0)
    {
        cout<<ans<<endl;
        return 1;
    }

   string smallAns="";
   
   int count=0;

    for(int i=1;i<=str.length();i++)
    {  
      smallAns=str.substr(0,i);
      if (map.find(smallAns) != map.end())  //means element map mein milgya
      { 
        count+=wordBreak02(str.substr(i),ans+smallAns+" "); 
      }

    }

    return count;

}

void wordbreak(){
    
    int len;
    string str;
   
    cin>>str;
   
    cin>>len;
   
    vector <string> dict(len,"");
    for(int i=0;i<len;i++)
    {
        cin>>dict[i];
    }
    
    for(string ele:dict)
    {
        map.insert(ele);
    }
    

    if(wordBreak01(str,dict))
    {
        cout<<"done";
    }
    cout<<endl;
   
    int count= wordBreak02(str,"");
    cout<<count<<endl;
}

//crypto==============================================================================================================

vector <int> mapping(26,0);

string str1,str2,str3;

int numUsed=0;

int stringToNum(string str){   //according to the mapping formed
     
    int number=0;
    int digit=0; 
    
    for(char ch:str)
    {
        digit=mapping[ ch-'a' ];
        number=number*10 + digit ;
    }
    
    return number;

}

int cryptoPermu(string str,int num,int idx){

    if( idx==str.length() || num>9 )
    {  

       if(  idx==str.length() && mapping[str3[0] - 'a'] != 0)  //taki 5 digit ka number humko mile
       {
        int a=stringToNum(str1);
        int b=stringToNum(str2);
        int c=stringToNum(str3);

        if(a+b==c)
        {
          cout<<a<<"+"<<b<<"="<<c<<endl;
          return 1 ;
        }
        else return 0;

       } 
       else
       {
           return 0;
       }
       
       
      
    }
     
    int count=0;

    int mask=(1<<num);
 
    if( (numUsed&mask) ==0)
    { 
    
    numUsed ^= mask;
    
    mapping[str[idx]-'a']=num; 
  
    count+=cryptoPermu(str,0,idx+1);  //baithane ki call mein idx increment hoga
   
    mapping[str[idx]-'a']=0; 

    numUsed ^= mask;
    

    }

    count+=cryptoPermu(str,num+1,idx);    //yaha pe nhi hoga

    return count;
}


string combine(string str1,string str2,string str3){
    
    string str=str1+str2+str3;

    int letters=0;
    int mask=0;
   
    
    for( char ele: str )
    {
        mask=(1<<(ele-'a'));
        letters = (letters|mask);
    }

    str="";
    
    for(int i=0;i<26;i++){
        
        mask=(1<<i);
        if( (mask&letters)!=0)
        {
            str=str+char('a'+i);
        }
        
    }
    if(str.length()>10) return "";

    
    return str;

}

void crypto(){ 

    cin>>str1>>str2>>str3;
    string str=combine(str1,str2,str3);
   int count=cryptoPermu(str,0,0);
   cout<<count;
   

}

void solve(){
      
    //wordbreak();
    crypto();

}

int main(){
    
    solve();

}