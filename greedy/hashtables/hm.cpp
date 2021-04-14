#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>



using namespace std;
   
// unordered_map<string, vector<string>> map;
        
//     void createMap(vector<string>& wordList) {
       
//         for(int i=0;i<wordList.size();i++) {
            
//             string ele1 = wordList[i];
            
//             for(int j=0;j<wordList.size();j++) {
                
//                 string ele2 = wordList[j];
                
//                 int count=0;
                
//                 for(int k=0 ; k<ele1.length() ; k++) {
                   
//                     if( ele1[k] != ele2[k] ) {
                        
//                         count++;
    
//                     }
//                 }
                
//                 if(count==1) {
//                     map[ele1].push_back(ele2);
//                 }

                
                
//             }
            
//         }
     
//     }

int main() {
//     vector<string> arr={"hot","dot","dog","lot","log","cog","hit"};
    
//     // createMap(arr);

//    // vector<string> v=map["hot"];
//     // for(string ss: v) {
//     //     cout<<ss<<" ";
//     // }
//     int count=0;

//     unordered_map <string , int > map;
//     // for(string ss:arr){
//     //     map[ss]=count++;
//     // }

//     //    for(pair<string, int> p:map ) {
       
//     //     string str=p.first;
        
//     //     int ele = p.second;
        
//     //     cout<<str<<" - > " << ele<<endl;
//     // }

//     map["abc"]++;
//     cout<<map["abc"]<<endl;

//     map["def"]=10;
//     cout<<map["def"];

    // map <char,int> mp;
    // mp['a']=10;
    // mp['g']=80;
    // mp['h']=900;
    // for(auto i:mp) {
    //     cout<<i.first<<"@"<<i.second;
    // }
    
    struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
    };

    unordered_map< vector<int>,int, VectorHasher > mp1;
    vector<int> arr1{1,2,3};
    mp1[arr1]=6;
    vector<int> arr2{4,5,6};
    mp1[arr2]=120;

    if(mp1.find(arr1)!=mp1.end())
    {
        cout<<mp1[arr1];
    }
    
}