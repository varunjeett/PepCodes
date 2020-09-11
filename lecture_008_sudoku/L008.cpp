#include <iostream>
#include <vector>

using namespace std;

vector<int> row(9, 0);
vector<int> col(9, 0);
vector<vector<int>> mat(3, vector<int>(3, 0));

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

//by bits.=====================
bool isSafe(vector<vector<int>> &board, int x, int y, int val)
{

    int mask = (1 << val);

    if ((row[x] & mask) != 0)
        return false;

    if ((col[y] & mask) != 0)
        return false;

    if ((mat[x / 3][y / 3] & mask) != 0)
        return false;

    return true;
}

long count1 = 0;
int sudoku01(vector<vector<int>> &board, int idx, vector<int> &places)
{
    count1++;
    if (idx == places.size())
    {
        display2D(board);
        return 1;
    }

    int count = 0;

    int i = places[idx] / 9;
    int j = places[idx] % 9;
    int mask;

    for (int val = 1; val <= 9; val++)
    {
        if (isSafe(board, i, j, val))
        {
            mask = (1 << val);

            //turn the bit for that value ON
            row[i] = (row[i] ^ mask);
            col[j] = (col[j] ^ mask);
            mat[i / 3][j / 3] = (mat[i / 3][j / 3] ^ mask);

            board[i][j] = val;
            count += sudoku01(board, idx + 1, places);
            board[i][j] = 0;

            //turn the bit for that value OFF
            row[i] = (row[i] ^ mask);
            col[j] = (col[j] ^ mask);
            mat[i / 3][j / 3] = (mat[i / 3][j / 3] ^ mask);
        }
    }

    return count;
}

long count2 = 0;
int sudoku02(vector<vector<int>> &board, int idx, int num, vector<int> &places)
{
    count2++;
    if (idx == places.size() || num == 10)
    {
        if (idx == places.size())
        {
            display2D(board);
            return 1;
        }
        return 0;
    }

    int count = 0;
    int i = places[idx] / 9;
    int j = places[idx] % 9;

    //aane ki call
    if (isSafe(board, i, j, num)) //kya aane de skte hain
    {
        int mask = (1 << num);

        //turn the bit for that value ON
        row[i] = (row[i] ^ mask);
        col[j] = (col[j] ^ mask);
        mat[i / 3][j / 3] = (mat[i / 3][j / 3] ^ mask);

        board[i][j] = num;
        count += sudoku02(board, idx + 1, 1, places);
        board[i][j] = 0;

        //turn the bit for that value OFF
        row[i] = (row[i] ^ mask);
        col[j] = (col[j] ^ mask);
        mat[i / 3][j / 3] = (mat[i / 3][j / 3] ^ mask);
    }

    //nahi aane ki call
    count += sudoku02(board, idx, num + 1, places);

    return count;
}

void sudoku()
{

    vector<vector<int>> board = {{0, 0, 6, 5, 0, 0, 0, 0, 0},
                                 {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                 {0, 0, 3, 0, 1, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 5},
                                 {0, 5, 0, 0, 0, 0, 6, 0, 0},
                                 {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 4},
                                 {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    vector<int> places;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
                places.push_back(i * 9 + j);
            else
            {
                int mask = (1 << board[i][j]);

                //xor do the reverse of current
                row[i] = (row[i] ^ mask);
                col[j] = (col[j] ^ mask);
                mat[i / 3][j / 3] = (mat[i / 3][j / 3] ^ mask);
            }
        }
    }

    cout << sudoku01(board, 0, places);
    cout << count1;

    
    //most efficient
    // cout << sudoku02(board, 0, 1, places) <<endl; //subsequence method
    // cout << count2;
}

int main()
{
    sudoku();
    return 0;
}
