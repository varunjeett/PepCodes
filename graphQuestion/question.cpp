//copying all the edges and creating clones of the nodes.
//while creating clones , be aware about keeping them in a hashmap against the values
//from the copied edges, create nodes and neighbors from hashmap

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        vector<vector<int>> edges(101, vector<int>());
        vector<bool> vis(101, false);

        unordered_map<int, Node *> map;

        queue<Node *> q;
        q.push(node);

        while (q.size() != 0)
        {
            int sz = q.size();
            while (sz-- > 0)
            {
                Node *rvtx = q.front();
                q.pop();

                if (vis[rvtx->val])
                    continue;

                vis[rvtx->val] = true;

                Node *clone = new Node(rvtx->val);
                map[rvtx->val] = clone;

                for (Node *child : rvtx->neighbors)
                {
                    // cout<<rvtx->val<<"->"<<child->val<<endl;
                    edges[rvtx->val].push_back(child->val); //storing all the edges
                    if (!vis[child->val])                   //not traversed previously
                        q.push(child);
                }
            }
        }

        int u, v;
        for (int i = 1; i < edges.size(); i++)
        {
            int u = i;
            for (int ele : edges[i])
            {
                v = ele;
                map[u]->neighbors.push_back(map[v]);
            }
        }

        return map[1]; //head is stored here.===============================================
    }
};

//no of islands 2:::::::::::::::::::::::::::::::::::::::::::::::::
class Solution
{
public:
    int findPar(int idx, vector<int> &par)
    {
        if (par[idx] == idx)
            return idx;
        return par[idx] = findPar(par[idx], par);
    }

    vector<int> noislands2(int n, int m, vector<vector<int>> &land)
    {
        if (n == 0 || m == 0 || land.size() == 0)
        {
            return 0;
        }
        vector<int> ans;
        vector<vector<int>> mat(n, vector<int>(m, 0));
        vector<int> dir = {-1, 0, 1, 0, -1};
        int count = 0;

        vector<int> par(n * m);
        for (int i = 0; i < (n * m); i++)
        {
            par[i] = i;
        }

        for (vector<int> &ar : land)
        {
            int r = ar[0];
            int c = ar[1];
            if (mat[r][c] == 1)
            {
                continue;
            }

            count++;
            int p1 =findPar(r*m+c,par);

            for (int d = 0; d < dir.size() - 1; d++)
            {
                int x = r + dir[d];
                int y = c + dir[d + 1];

                if(x>=0 && y>=0 && x<n && y<m && mat[x][y]==1)
                {
                    int p2=findPar(x*m+y,par);
                    if(p1!=p2)
                    {
                        par[p2]=p1;
                        count--;
                    }

                }
            }

            ans.push_back(count);
        }
    }

    return ans;
}
