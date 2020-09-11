//TOUGH
//LEETCODE : 76
class Solution
{
public:
    string minWindow(string s, string t)
    {
        int sl = s.length();
        int tl = t.length();
        if (sl == 0 || tl == 0)
            return "";

        unordered_map<char, int> map_t, map_s;
        for (char ch : t)
            map_t[ch]++;

        int count = 0, left = 0, right = 0, f_left = 0, f_right = 0, min_ = +1e8;

        map_s[s[left]]++;
        if (map_t.find(s[left]) != map_t.end())
            count++;

        while (right < sl)
        {
            while (count == tl)
            {

                if (right - left + 1 < min_)
                {
                    min_ = right - left + 1;
                    f_left = left;
                    f_right = right;
                }

                map_s[s[left]]--;
                if (map_t.find(s[left]) != map_t.end())
                {
                    if (map_s[s[left]] < map_t[s[left]])
                        count--;
                }
                left++;
            }

            right++;
            if (right < sl && map_t.find(s[right]) != map_t.end())
            {
                if (map_s[s[right]] < map_t[s[right]])
                    count++;
            }
            map_s[s[right]]++;
        }

        return min_ == +1e8 ? "" : s.substr(f_left, min_);
    }
};

//lc 692 IMPORTANT QUES
struct myComparator
{
    bool operator()(const pair<int, string> &a, const pair<int, string> &b)
    {
        //this - other for decreasing  and so on ; replace '-' by > in priority_queue
        if (a.first == b.first)
            return b.second > a.second; //alphabetcal greater string return.
        return a.first > b.first;       //min for freq.
    }
};

vector<string> topKFrequent(vector<string> &words, int k)
{
    unordered_map<string, int> map;
    for (string &s : words)
        map[s]++;

    priority_queue<pair<int, string>, vector<pair<int, string>>, myComparator> pq;

    for (const pair<string, int> &p : map)
    { //min priority queue.
        pq.push({p.second, p.first});
        if (pq.size() > k)
            pq.pop();
    }

    vector<string> ans;
    while (pq.size() != 0)
    {
        const pair<int, string> &p = pq.top();
        ans.push_back(p.second);
        pq.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

//leetcode :973 .================================================
struct myComparator
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return (pow(b[0], 2) + pow(b[1], 2)) > (pow(a[0], 2) + pow(a[1], 2)); //other - this(descending) : replace '-' by >.
    }
};

vector<vector<int>> kClosest(vector<vector<int>> &points, int K)
{
    priority_queue<vector<int>, vector<vector<int>>, myComparator> pq;
    for (const vector<int> &arr : points)
    {
        pq.push(arr);
        if (pq.size() > K)
            pq.pop();
    }
    vector<vector<int>> finalAns;
    while (pq.size() != 0)
    {
        const vector<int> &arr = pq.top();
        finalAns.push_back(arr);
        pq.pop();
    }
    return finalAns;
}

//leetcode : 1054
vector<int> rearrangeBarcodes(vector<int> &barcodes)
{
    int n = barcodes.size();
    unordered_map<int, int> map;
    for (int ele : barcodes)
        map[ele]++;

    priority_queue<pair<int, int>> pq;
    for (const pair<int, int> &p : map)
    {
        pq.push({p.second, p.first});
    }

    vector<int> ans;
    while (pq.size() != 0)
    {

        pair<int, int> fir = pq.top();
        pq.pop();

        if (pq.size() == 0)
        {
            int i = fir.first;
            while (i-- > 0)
                ans.push_back(fir.second);
        }

        else
        {
            pair<int, int> sec = pq.top();
            pq.pop();
            ans.push_back(fir.second);
            ans.push_back(sec.second);
            if (fir.first > 1)
                pq.push({fir.first - 1, fir.second});
            if (sec.first > 1)
                pq.push({sec.first - 1, sec.second});
        }
    }
    return ans;
}

//EDGY QUESTION  ; LC 380.============================
class RandomizedSet
{
public:
    vector<int> arr;
    unordered_map<int, int> map;

    /** Initialize your data structure here. */
    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (map.find(val) != map.end())
            return false;
        else
        {
            arr.push_back(val);        //put element in the vector
            map[val] = arr.size() - 1; //put element and its position in the map
            return true;
        }
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if (map.find(val) == map.end())
            return false;
        else
        {
            int pos = map[val];    //pos of element in the vector
            arr[pos] = arr.back(); //overwrite last element
            map[arr.back()] = pos; //change the pos of last element in the map
            arr.pop_back();        //remove last
            map.erase(val);        //delete the element in the map
            return true;
        }
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        int pos = rand() % arr.size();
        return arr[pos];
    }
};

//trapping rain water : 2.============================================
class Solution
{
public:
    int trapRainWater(vector<vector<int>> &arr)
    {

        int n = arr.size();
        if (n == 0)
            return 0;
        int m = arr[0].size();
        if (m == 0)
            return 0;

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        typedef pair<int, int> cell; //(Height,i*m+j)
        priority_queue<cell, vector<cell>, greater<cell>> pq;

        for (int i = 0; i < m; i++)
        {
            pq.push({arr[0][i], 0 * m + i});
            vis[0][i] = true;
            pq.push({arr[n - 1][i], (n - 1) * m + i});
            vis[n - 1][i] = true;
        }

        for (int i = 1; i < n - 1; i++)
        {
            pq.push({arr[i][0], i * m + 0});
            vis[i][0] = true;
            pq.push({arr[i][m - 1], i * m + m - 1});
            vis[i][m - 1] = true;
        }

        int bottleNeck = -1;
        int water = 0;
        vector<int> dir{-1, 0, 1, 0, -1};

        while (pq.size() != 0)
        {
            cell rvtx = pq.top();
            pq.pop();
            bottleNeck = max(bottleNeck, rvtx.first);

            int r = rvtx.second / m;
            int c = rvtx.second % m;

            for (int d = 0; d < dir.size() - 1; d++)
            {
                int x = r + dir[d];
                int y = c + dir[d + 1];

                if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y])
                {
                    pq.push({arr[x][y], x * m + y});
                    vis[x][y] = true;
                    water += max(0, bottleNeck - arr[x][y]);
                }
            }
        }

        return water;
    }
};

//leetcode 381.==============================
//hashmap of int vs hashset(to store the multiple of indexes)
class RandomizedCollection
{
public:
    vector<int> arr;
    unordered_map<int, unordered_set<int>> map;
    /** Initialize your data structure here. */
    RandomizedCollection()
    {
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val)
    {
        if (map.count(val) == 0)
        {
            arr.push_back(val);
            int pos = arr.size() - 1;
            map[val].insert(pos);
            return true;
        }
        else
        {
            arr.push_back(val);
            int pos = arr.size() - 1;
            map[val].insert(pos);
            return false;
        }
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val)
    {
        if (map.count(val) == 0)
            return false;
        else
        {
            int pos = *(map[val].begin());
            map[val].erase(pos);
            if (map[val].size() == 0)
                map.erase(val);

            arr[pos] = arr.back();
            map[arr.back()].insert(pos);
            map[arr.back()].erase(arr.size() - 1);

            if (map[arr.back()].size() == 0) //case for single element
                map.erase(arr.back());

            arr.pop_back();

            return true;
        }
    }

    /** Get a random element from the collection. */
    int getRandom()
    {
        int pos = rand() % arr.size();
        return arr[pos];
    }
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

//leetcode 138.==========================================
//copy list with random pointer
class Solution
{
public:
    void createClones(Node *head)
    {
        if (head == nullptr)
            return;

        Node *cur = head;
        while (cur != nullptr)
        {
            Node *forward = cur->next;
            Node *clone = new Node(cur->val);
            cur->next = clone;
            clone->next = forward;

            cur = forward;
        }
    }

    void setRandom(Node *head) //we cant set random and next at the same time, list will break.
    {
        if (head == nullptr)
            return;

        Node *cur = head;
        while (cur != nullptr)
        {
            Node *clone = cur->next;
            Node *forward = clone->next;
            Node *rand = cur->random;

            if (rand != nullptr)
                clone->random = rand->next;

            cur = forward;
        }
    }

    void setNext(Node *head)
    {
        if (head == nullptr)
            return;

        Node *cur = head;
        while (cur != nullptr)
        {
            Node *clone = cur->next;
            Node *forward = clone->next;

            cur->next = forward;
            if (forward != nullptr)
                clone->next = forward->next;

            cur = forward;
        }
    }

    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;
        createClones(head);
        Node *nhead = head->next;
        setRandom(head);
        setNext(head);
        return nhead;
    }
};
