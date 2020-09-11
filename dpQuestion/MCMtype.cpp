class Solution
{
public:
    void display_bool(vector<bool> &arr)
    {
        for (bool ele : arr)
            cout << ele << " ";
        cout << endl;
    }

    void display2D_bool(vector<vector<bool>> &arr)
    {
        for (vector<bool> ar : arr)
            display_bool(ar);
        cout << endl;
    }

    void display(vector<int> &arr)
    {
        for (int ele : arr)
            cout << ele << " ";
        cout << endl;
    }

    void display2D(vector<vector<int>> &arr)
    {
        for (vector<int> ar : arr)
            display(ar);
        cout << endl;
    }
    // cst- cut start index
    // ced- cut end index
    // rodst- rod start index
    // roded- rod end index

    int find(int rodst, int roded, int cst, int ced, vector<int> &cuts, vector<vector<int>> &dp)
    {

        if (dp[cst][ced] != -1)
            return dp[cst][ced];

        int min_ = INT_MAX;

        for (int idx = cst; idx <= ced; idx++)
        {
            int cut = cuts[idx];
            int ll = (cst > idx - 1) ? 0 : find(rodst, cut, cst, idx - 1, cuts, dp);
            int rr = (idx + 1 > ced) ? 0 : find(cut, roded, idx + 1, ced, cuts, dp);

            min_ = min(min_, (roded - rodst + ll + rr));
        }

        return dp[cst][ced] = min_;
    }

    int minCost(int n, vector<int> &cuts)
    {
        vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), -1));
        sort(cuts.begin(), cuts.end());
        int ans = find(0, n, 0, cuts.size() - 1, cuts, dp);
        display2D(dp);
        cout << ans << endl;
    }
};