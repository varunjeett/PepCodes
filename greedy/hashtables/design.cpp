//----------------------DESIGN HASHSET----------------------------------
//normal seperate chaining hashing.===================================
class MyHashSet {
public:
    /** Initialize your data structure here. */
    vector<vector<int>> arr;
    int bucket;
    MyHashSet() {
        bucket=1000;
        arr=vector<vector<int>> (bucket,vector<int>());
    }
    
    int giveHash(int ele) {
        return (ele%bucket);
    }
    
    void add(int key) {
        int flag=0;
        int hash=giveHash(key);
        for(int ele: arr[hash]){
            if(ele==key) {
                flag=1;
                break;
            }
        }
        
        if(flag==1) return;
        arr[hash].push_back(key);
        return;
    }
    
    void remove(int key) {
   
        int hash=giveHash(key);
        for(int i=0;i<arr[hash].size();i++){
            if(arr[hash][i]==key) {
                arr[hash][i]=arr[hash][arr[hash].size()-1];
                arr[hash].pop_back();
                return;
            }
        }

        return;
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        
        int hash=giveHash(key);
        for(int i=0;i<arr[hash].size();i++){
            if(arr[hash][i]==key) {
                return true;
            }
        }

        return false;
    }
};

// Maximum possible value to be stored = 1000000
// Considering each bit of a number reprsents a number
// Number of bits in one number(Numbers each number in the array can represent) = 32
// Total numbers required = 1000000/32 = 31250
// For example:
// number 0 can be reprsented by idx = 0, bit = 0 i.e. num[0] = 00000000000000000000000000000001
// number 37 can be represented by idx = 1(37/32), bit = 5(37%32) ie. num[1] = 00000000000000000000000000100000

//no possibility of duplicate
class MyHashSet {
public:
    int bucket;  
    vector<int> arr;   //TO HAVE LAST INDEX AS 31250, WE SHOULD HAVE SIZE=LAST INDEX+1
    
    /** Initialize your data structure here. */
    MyHashSet() {
        bucket=1000000/32;  
        arr=vector<int>(bucket,0);
    }    
    void add(int key) {
        int idx=key/32;
        int bit=key%32;
        arr[idx]=(arr[idx]|(1<<bit));   //turning on
    }
    
    void remove(int key) {
        int idx=key/32;
        int bit=key%32;
        arr[idx]=(arr[idx]&(~(1<<bit))); //turning off  
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int idx=key/32;
        int bit=key%32;
        if((arr[idx]&(1<<bit))!=0)     //checking on or off
            return true;
        else
            return false;
    }
};
