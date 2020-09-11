#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<string> mazepath_HV(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    if (sc + 1 <= ec)
    {

        vector<string> smallAns = mazepath_HV(sr, sc + 1, er, ec); //horizontal call
        for (string s : smallAns)
        {
            myAns.push_back("H" + s);
        }
    }

    if (sr + 1 <= er)
    {

        vector<string> smallAns = mazepath_HV(sr + 1, sc, er, ec); //vertical call
        for (string s : smallAns)
        {
            myAns.push_back("V" + s);
        }
    }

    return myAns;
}

//same as above just one diagonal call extra
vector<string> mazepath_HDV(int sr, int sc, int er, int ec)
{

    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    if (sc + 1 <= ec)
    {

        vector<string> smallAns = mazepath_HDV(sr, sc + 1, er, ec); //horizontal call
        for (string s : smallAns)
        {
            myAns.push_back("H" + s);
        }
    }

    if (sr + 1 <= er && sc + 1 <= ec)
    {

        vector<string> smallAns = mazepath_HDV(sr + 1, sc + 1, er, ec); //diagonal call
        for (string s : smallAns)
        {
            myAns.push_back("D" + s);
        }
    }

    if (sr + 1 <= er)
    {

        vector<string> smallAns = mazepath_HDV(sr + 1, sc, er, ec); //vertical call
        for (string s : smallAns)
        {
            myAns.push_back("V" + s);
        }
    }

    return myAns;
}

vector<string> mazepath_HDV_jump(int sr, int sc, int er, int ec)
{

    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    for (int jump = 1; jump + sc <= ec; jump++)
    {

        vector<string> smallAns = mazepath_HDV_jump(sr, sc + jump, er, ec); //horizontal jump
        for (string s : smallAns)
        {
            myAns.push_back("H" + to_string(jump) + s);
        }
    }

    for (int jump = 1; (jump + sr <= er && jump + sc <= ec); jump++)
    {

        vector<string> smallAns = mazepath_HDV_jump(sr + jump, sc + jump, er, ec); //diagonal jump
        for (string s : smallAns)
        {
            myAns.push_back("D" + to_string(jump) + s);
        }
    }

    for (int jump = 1; jump + sr <= er; jump++)
    {

        vector<string> smallAns = mazepath_HDV_jump(sr + jump, sc, er, ec);
        for (string s : smallAns)
        {
            myAns.push_back("V" + to_string(jump) + s);
        }
    }

    return myAns;
}

int mazepath_HDV_void(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;

    if (sr + 1 <= er)
    { //horizontal
        count += mazepath_HDV_void(sr + 1, sc, er, ec, ans + "H");
    }

    if (sr + 1 <= er && sc + 1 <= ec)
    { //diagonal
        count += mazepath_HDV_void(sr + 1, sc + 1, er, ec, ans + "D");
    }

    if (sc + 1 <= ec)
    { //vertical
        count += mazepath_HDV_void(sr, sc + 1, er, ec, ans + "V");
    }
    return count;
}

int mazepath_HDV_jump_void(int sr, int sc, int er, int ec, string ans)
{

    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;

    for (int jump = 1; jump + sc <= ec; jump++)
    { //horizontal
        count += mazepath_HDV_jump_void(sr, sc + jump, er, ec, ans + "H" + to_string(jump));
    }

    for (int jump = 1; jump + sc <= ec && jump + sr <= er; jump++)
    { //diagonal
        count += mazepath_HDV_jump_void(sr + jump, sc + jump, er, ec, ans + "D" + to_string(jump));
    }

    for (int jump = 1; jump + sr <= er; jump++)
    { //vertical
        count += mazepath_HDV_jump_void(sr + jump, sc, er, ec, ans + "V" + to_string(jump));
    }

    return count;
}

vector<vector<int>> board(3, vector<int>(3, 0)); //board of 4*4

vector<string> Dir_Name = {"U", "ur", "R", "dr", "D", "dl", "L", "ul"};

vector<vector<int>> Dir_V = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

bool isValid(int r, int c, vector<vector<int>> &board)
{

    if (r >= 0 && c >= 0 && r < board.size() && c < board[0].size() && board[r][c] == 0)
        return true;

    else
    {
        return false;
    }
}

vector<string> floodfill_8moves(int sr, int sc, int er, int ec)
{

    if (sr == er && sc == er)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    board[sr][sc] = 1;

    for (int i = 0; i < Dir_Name.size(); i++)
    {
        int r = sr + Dir_V[i][0];
        int c = sc + Dir_V[i][1];

        bool check = isValid(r, c, board);

        if (check)
        {
            vector<string> smallAns = floodfill_8moves(r, c, er, ec);

            for (string s : smallAns)
            {
                myAns.push_back(Dir_Name[i] + s);
            }
        }
    }

    board[sr][sc] = 0;
    return myAns;
}

int floodfill_8moves_jump_voidType(int sr, int sc, int er, int ec, string ans)
{

    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;

    board[sr][sc] = 1;

    for (int i = 0; i < Dir_Name.size(); i++)
    {

        for (int jump = 1; jump < board.size(); jump++)
        {

            int r = sr + (jump * Dir_V[i][0]);
            int c = sc + (jump * Dir_V[i][1]);
            if (isValid(r, c, board))
                count += floodfill_8moves_jump_voidType(r, c, er, ec, ans + Dir_Name[i] + to_string(jump));
        }
    }

    board[sr][sc] = 0;
    return count;
}

vector<vector<int>> Dir_V_Oranges = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void rot_start(int r, int c, vector<vector<int>> &board)
{
    board[r][c] = 3; //rotten and visited

    for (int i = 0; i < 4; i++)
    {

        int r_ = r + Dir_V_Oranges[i][0];
        int c_ = c + Dir_V_Oranges[i][1];

        if (r_ >= 0 && c_ >= 0 && r_ < board.size() && c_ < board[0].size() && board[r_][c_] == 1)
        {   //picking only fresh from its neighbourhood
            rot_start(r_, c_, board);
        }
    }
}

int rottenOranges_4DIR(vector<vector<int>> &board)
{
    int i;
    int j;

    for (i = 0; i < board.size(); i++)
    {
        for (j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 2)
            {   //rotten and unvisted
                rot_start(i, j, board);
            }
        }
    }

    int count = 0;

    for (i = 0; i < board.size(); i++)
    {
        for (j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 1)
            {
                count++;
            }
        }
    }

    return count;
}

bool isValidFORISLAND(int r, int c, vector<vector<int>> &board)
{
    if (r >= 0 && c >= 0 && r < board.size() && c < board[0].size() && board[r][c] == 1)
    {
        return true;
    }
    else
        return false;
}

vector<string> Dir_Name_island = {"U", "R", "D", "L"};

vector<vector<int>> Dir_V_island = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs(int r, int c, vector<vector<int>> &board)
{
    board[r][c] = 2;
    for (int i = 0; i < Dir_Name_island.size(); i++)
    {
        int r_ = r + Dir_V_island[i][0];
        int c_ = c + Dir_V_island[i][1];

        if (isValidFORISLAND(r_, c_, board))
        {
            dfs(r_, c_, board);
        }
    }
}

int countIsland(vector<vector<int>> &board)
{
    int count = 0;
    for (int r = 0; r < board.size(); r++)
    {
        for (int c = 0; c < board[0].size(); c++)
        {
            if (board[r][c] == 1)
            {
                dfs(r, c, board);
                count++;
            }
        }
    }
    return count;
}

int combination_infinite(int len, int coins[], int s_index, int target, string ans)
{
    if (target == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = s_index; i < len; i++)
    {
        if (target - coins[i] >= 0)
            count += combination_infinite(len, coins, i, target - coins[i], ans + to_string(coins[i]));
    }

    return count;
}

int combination_finite(int len, int coins[], int s_index, int available[], int target, string ans)
{
    if (target == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = s_index; i < len; i++)
    {

        if (available[i] > 0 && target - coins[i] >= 0)
        {
            available[i]--;
            count += combination_finite(len, coins, i, available, target - coins[i], ans + to_string(coins[i]));
            available[i]++;
        }
    }
    return count;
}

void mazepath()
{

    int sr = 0, sc = 0, er = 2, ec = 2;

    // vector <string> res1=mazepath_HV(sr,sc,er,ec);
    // for(string s:res){
    //     cout<<s<<endl;
    // }

    // vector <string> res2=mazepath_HDV(sr,sc,er,ec);
    // for(string s:res2){
    //     cout<<s<<endl;
    // }

    vector<string> res3 = mazepath_HDV_jump(sr, sc, er, ec);
    for (string s : res3)
    {
        cout << s << endl;
    }

    //cout<<mazepath_HDV_void(sr,sc,er,ec,"");

    cout << mazepath_HDV_jump_void(sr, sc, er, ec, "");
}

void floodfill()
{

    int sr = 0, sc = 0, er = 2, ec = 2;

    vector<string> res = floodfill_8moves(sr, sc, er, ec); //8 steps code
    for (string s : res)
    {
        cout << s << endl;
    }

    //cout<<floodfill_8moves_jump_voidType(sr,sc,er,ec,"");
}

void island()
{
    vector<vector<int>> board_island = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
    int res_1 = countIsland(board_island);
    cout << res_1;
}

void rottenOranges()
{
    vector<vector<int>> board_oranges = {{2, 1, 0, 2}, {1, 1, 0, 1}, {0, 0, 0, 0}, {1, 0, 1, 2}};
    int res = rottenOranges_4DIR(board_oranges);
    cout << res;
}

void coinChange()
{

    int coins[] = {2, 3, 5, 7};
    int available[] = {0, 0, 2, 0};

    int t1 = sizeof(coins);
    int t2 = sizeof(coins[0]);
    int len = t1 / t2;

    // int answer=combination_infinite(len,coins,0,10,"");
    // cout<<answer<<endl;

    int answer2 = combination_finite(len, coins, 0, available, 10, "");
    cout << answer2 << endl;
}

int main()
{

    // mazepath();
    // floodfill();
    // island();
    rottenOranges();
    // coinChange();
}
