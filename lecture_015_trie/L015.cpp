//29 april
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    bool wordend;
    vector<Node *> childs;
    string wordhere;

    Node()
    {
        this->wordend = false;
        this->childs.assign(26, nullptr);
        this->wordhere = "";
    }
};

Node *root = nullptr;
void insert(string word)
{
    Node *r = root;

    for (int i = 0; i < word.length(); i++)
    {
        if (r->childs[word[i] - 'a'] == nullptr)
            r->childs[word[i] - 'a'] = new Node();

        r = r->childs[word[i] - 'a'];
    }

    r->wordend = true;
    r->wordhere = word;
}

// bool search(string word)
//     {
//         Node* r=root;

//         for(int i=0;i<word.length();i++)
//         {
//             if(r->childs[word[i]-'a']== nullptr)   return false;
//             else
//             {
//                 r=r->childs[word[i]-'a'];
//             }
//         }
//         if(r->wordend)
//         {
//            cout<<r->wordhere<<" is found"<<endl;
//            return (r->wordend);
//         }
//         else return (r->wordend);

//     }

// void trie(){

//     root=new Node();
//     insert("apple");
//     insert("app");
//     insert("appli");

//     cout<<search("apple");
// }

void dfs(int r, int c, vector<vector<char>> &board, vector<string> &ans, Node *cur)
{
    if (cur->wordend == true)
    {
        cur->wordend = false;
        ans.push_back(cur->wordhere);
    }

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    char ch = board[r][c];

    board[r][c] = '&';

    for (int d = 0; d < 4; d++)
    {
        int x = r + dir[d][0];
        int y = c + dir[d][1];

        if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] != '&' && (cur->childs[board[x][y] - 'a'] != nullptr))
            dfs(x, y, board, ans, cur->childs[board[x][y] - 'a']);
    }

    board[r][c] = ch;
}

vector<string> findWords(vector<vector<char>> &board, vector<string> &words, vector<string> &ans)
{
    if (board.size() == 0 || board[0].size() == 0 || words.size() == 0)
        return {};

    root = new Node();

    for (string s : words)
    {
        insert(s);
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (root->childs[board[i][j] - 'a'] != nullptr)
            {
                //call dfs for this
                dfs(i, j, board, ans, root->childs[board[i][j] - 'a']);
            }
        }
    }
    return ans;
}

void lc212()
{

    vector<vector<char>> board = {{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};

    vector<string> words = {"oath", "pea", "eat", "rain"};

    vector<string> ans = {};

    vector<string> ret = findWords(board, words, ans);

    for (string s : ret)
    {
        cout << s << endl;
    }
}

void solve()
{
    //trie();
    lc212();
}

int main()
{
    solve();
}