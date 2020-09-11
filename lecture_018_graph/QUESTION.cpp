//REDUNDANT CONNECTION 2:::::::::::::::::::::::::::::::::::::::::::::::::::::
class Solution
{
public:
    vector<int> par;
    vector<int> sz;

    int findPar(int idx)
    {
        if (idx == par[idx])
            return idx;
        return par[idx] = findPar(par[idx]); //return mein aati hui value ko apna parent bnana
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {

        //three possiility:
        //first, A node has indegree > 1 and no cycle exists.=============
        //second, only a cycle exits
        //third, there exists a cycle as well as a node has indegree greater than 1, return the overlapping edge that causes both

        int N = edges.size() + 1;
        par = vector<int>(N);
        sz = vector<int>(N);

        for (int i = 0; i < par.size(); i++)
        {
            par[i] = i;
            sz[i] = 1;
        }

        vector<int> mp(N);

        vector<int> first;
        vector<int> second;

        for (vector<int> e : edges)
        {
            //u is parent of v
            int u = e[0];
            int v = e[1];
            if (mp[v] != 0)
            {
                first = {mp[v], v}; //mp[v] is the parent of v
                second = e;
            }
            mp[v] = u;
        }

        for (vector<int> e : edges)
        {
            //in the third case,
            //either first edge creates a cycle or 2nd edge creates a cycle.
            //if we skip second edge, still find a cycle in our graph, its because of the first edge, hence first edge is the answer.
            //if after skipping we dont find a edge, we'll come out of the loop: 2 possibility:cycle didnt exist originally, hence second is the answer
            //AND OTHER CASE IS CYCLE WAS THERE, BUT COULDNT DETECT IT BECAUSE WE SKIPPED SECOND, THAT IMPLY SECOND IS THE CAUSE OF CYCLE AND HENCE SECOND IS THE ANSWER...... IMPORTANT
            if (e == second)
                continue;

            int u = e[0];
            int v = e[1];

            int p1 = findPar(u);
            int p2 = findPar(v);

            if (p1 != p2)
            {
                par[p2] = p1;
            }

            else
            {
                if (first.size() == 0) //case of only cycle
                    return e;          //WHEN INDEGREE OF ALL NODES IS 1 , AND STILL THERE IS A CYCLE, SO THIS IS BECAUSE OF THE CURRENT EDGE

                else //cycle exists and indegree is zero.
                    //we HAD skipped second edge, still found a cycle in our graph, its because of the first edge, hence first edge is the answer
                    return first;
            }
        }

        return second; //cycle is not found but indegree of a node is 2  ===================
    }
};

//ACCOUNT MERGE : 721
class Solution
{
public:
    int findPar(int idx, vector<int> &par)
    {
        if (par[idx] == idx)
            return idx;
        return par[idx] = findPar(par[idx], par);
    }

    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {

        unordered_map<string, string> mtn;
        unordered_map<string, int> nodes;
        unordered_map<int, string> nodeToMail;
        int idx = 0;

        //mapping from string to int and storing relevant info
        for (vector<string> arr : accounts)
        {
            string name = arr[0];

            for (int i = 1; i < arr.size(); i++)
            {
                // cout<<arr[i]<<endl;
                mtn[arr[i]] = name;

                if (nodes.find(arr[i]) == nodes.end()) //first occurence
                {
                    nodes[arr[i]] = idx;
                    nodeToMail[idx] = arr[i];
                    idx++;
                }
            }
        }

        //defining parent array
        vector<int> par(idx);
        for (int i = 0; i < par.size(); i++)
        {
            par[i] = i;
        }

        for (vector<string> &arr : accounts)
        {

            for (int i = 1; i < arr.size() - 1; i++)
            {

                int j = i + 1;
                int u = nodes[arr[i]];
                int v = nodes[arr[j]];

                int p1 = findPar(u, par);
                int p2 = findPar(v, par);
                if (p1 < p2)
                    par[p2] = p1;
                else
                    par[p1] = p2;
            }
        }

        //creating answer in the map
        vector<vector<string>> ans;
        unordered_map<int, priority_queue<string, vector<string>, greater<string>>> mp;

        for (int i = 0; i < par.size(); i++)
        {
            mp[findPar(i, par)].push(nodeToMail[i]);
        }

        //storing answer in the 2D array
        for (auto i : mp)
        {
            vector<string> ar;
            ar.push_back(mtn[nodeToMail[i.first]]);
            while (i.second.size() != 0)
            {
                string s = i.second.top();
                i.second.pop();
                ar.push_back(s);
            }

            ans.push_back(ar);
        }

        return ans;
    }
};

class Solution
{
public:
    //greedy===============================
    int minSwapsCouples(vector<int> &row)
    {
        int N = row.size();
        vector<int> pos(N);
        for (int i = 0; i < N; i++)
        {
            pos[row[i]] = i;
        }

        int count = 0;
        for (int i = 0; i < N; i += 2)
        {
            int man = row[i];
            //(man&1) is true if man is odd and false if man is even.
            int woman = (man & 1) ? man - 1 : man + 1;

            if (row[i + 1] == woman)
                continue; //already there
            int idx = pos[woman];
            swap(row[i + 1], row[idx]); //replace the next ele of man with the woman found
            count++;
        }

        return count;
    }
};