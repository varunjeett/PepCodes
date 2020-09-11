#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int onToOFF(int num,int k){
     
    int mask=1;
    mask=( ~(mask<<(k-1)) );
    return (num & mask);
}

int offToON(int num,int k){
    
    int mask=1;
    mask= ( mask<<(k-1) );
    return (num | mask);
}

string evenOdd(int n){      
    return (n&1)==1?"odd":"even";
}


int noOfsetBit(unsigned int num){
    if(num==0) return 0;
    
    else
    {   int ans=0;
        int count=0;
        unsigned int mask=1;
       
        while(count<32 && num>0){
            
            if ((num&mask)==1){
                ans++;
            }
          
            count++;
            num=(num>>1);
        }
        return ans;
    }
   
}

int noOfsetBit01(int num){

    if(num==0) return 0;
  
    else
    {   int ans;
        while(num!=0)
        {
            num=(num&num-1);
            ++ans;
        }
        return ans;
    }
    
}

string power_2(int n){

    if(n==1) return "true";
    if(n>0){
     
       return ( n & (n-1) )==0 ? "true":"false";

    }
    return "false";

}

string power_4(int n){
   
    if(n==1) return "true";
   
    string ans;
    if(n>0){
        for(int i=2;i<32;i=i+2){
            int m=1;
            m=(m<<i);
            if(!(n^m)){
                return "true";
                break;
            }

        }
        return "false";
    }

    return "false";
}

int singleInK(vector <int> arr, int k){  
    int ans=0;
    int m;
    int countVertical;
   
    for(int i=0;i<32;i++)
    {   countVertical=0;
        m=(1<<i);
        for(int ele:arr)
        {  
          if ((ele&m)!=0) ++countVertical;
        }
        
        if(countVertical%k != 0)
        {
            ans= (ans|m);
        }
    }

    return ans;
}

//leetcode 287, elements should be between 0 to 31 
int Duplicate(vector <int> arr){
     
        int n1=0;
        int mask=0;
        int one=1;
        for(int i=0;i<arr.size();i++){
       
        one=1;
        mask=( one << (arr[i]-1) );
     
        if ( (n1&mask) != 0)   return arr[i];
        else n1=(n1|mask);
        }
         
        return 0;
}

unsigned int reverseBits(unsigned int num){
    int i=0;
    int mask2=0;
    int ans=0;
    for(i=1;i<=32;i++)
    {
        if((num&1)!= 0)  
        {
           int shift=32-i;
           mask2=(1<<shift);
           ans=(ans|mask2);
        }
    
        num=(num>>1);  

        if(num==0) break;
    }
    return ans;
}

vector <int> countBits(int num){
   
    int i=0;
    vector <int> table(num,0);
    table[0]=0;
    int pow,sub;
   
    for(i=1;i<=num;i++){
        pow=log2(i);
        sub=(1<<pow);
        table[i]=table[i-sub]+1;
    }

    return table;
}


void bit(){

    // cout<<evenOdd(0);
    // cout<<endl;
    // cout<<power_2(-36);
    // cout<<power_4(0);
    // cout<<endl;
    // cout<<offToON(8,3);

    // cout<<noOfsetBit01(10);
    //vector <int> arr{3,1,3,4,2};
    // cout<<singleInK(arr,3);

    //cout<<Duplicate(arr);

    //cout<<reverseBits(43261596);

    vector <int> ans=countBits(19);
    for(int ele:ans){
        cout<<ele<<endl;
    }
}

int main(){
   
    bit();
  
}