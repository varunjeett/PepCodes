import java.util.ArrayList;

public class L008 {
    public static void main(String[] args) {
        solve();
    }

    static int[] row; // kind of global
    static int[] col;
    static int[][] mat;

    public static void solve() {
        sudoku();
    }

    public static void sudoku() {

        int[][] board = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 }, { 5, 2, 0, 0, 0, 0, 0, 0, 0 }, { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                { 0, 0, 3, 0, 1, 0, 0, 8, 0 }, { 9, 0, 0, 8, 6, 3, 0, 0, 5 }, { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                { 1, 3, 0, 0, 0, 0, 2, 5, 0 }, { 0, 0, 0, 0, 0, 0, 0, 7, 4 }, { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

        //one answer
        sudoku01(board, 0);      
     
        //all possible answer
        System.out.println(sudoku02(board, 0)); 

        // row = new int[9];
        // col = new int[9];
        // mat = new int[3][3];

        // ArrayList<Integer> call = new ArrayList<>();

        // for (int i = 0; i < 9; i++) {
        //     for (int j = 0; j < 9; j++) {

        //         if (board[i][j] != 0) {
        //             int mask = (1 << board[i][j]);

        //             row[i] = (row[i] | mask);
        //             col[j] = (col[j] | mask);
        //             mat[i / 3][j / 3] = (mat[i / 3][j / 3] | mask);

        //         }

        //         else {
        //             call.add(i * 9 + j);
        //         }

        //     }
        // }

        // int ans2 = sudoku_SS(board, call, 1, 0);
        // System.out.println(ans2);

    }

    public static void print2D(int[][] board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static boolean isSafe(int[][] board, int x, int y, int num) {

        // for row
        for (int i = 0; i < 9; i++)
            if (board[x][i] == num) // same number already exits
                return false;
        
        //for column
        for (int i = 0; i < 9; i++)
            if (board[i][y] == num) // same number already exits
                return false;

        //for 3*3 matrix
        x = (x / 3) * 3;
        y = (y / 3) * 3;
        for (int i = x; i < x + 3; i++)
            for (int j = y; j < y + 3; j++)
                if (board[i][j] == num)
                    return false;

        return true;
    }

    //gives one answer
    public static boolean sudoku01(int[][] board, int idx) {

        if(idx==81)
        {
            print2D(board);
            return true;
        }


        boolean res = false;
        int r = idx / 9;
        int c = idx % 9;

        if (board[r][c] == 0) {
            for (int val = 1; val <= 9; val++) {
                if (isSafe(board, r, c, val)) {
                    board[r][c]=val;
                    res = res || sudoku01(board,idx+1);
                    board[r][c]=0;
                }
            }
        }

        else{
            res = res || sudoku01(board,idx+1);
        }

        return res;

    }

    //all possible answers
    public static int sudoku02(int[][] board, int idx) {

        if(idx==81)
        {
            print2D(board);
            return 1;
        }


        int count = 0;
        int r = idx / 9;
        int c = idx % 9;

        if (board[r][c] == 0) {
            for (int val = 1; val <= 9; val++) {
                if (isSafe(board, r, c, val)) {
                    board[r][c]=val;
                    count += sudoku02(board,idx+1);
                    board[r][c]=0;
                }
            }
        }

        else
            count += sudoku02(board,idx+1);        

        return count;

    }

    public static int sudoku03(int[][] board, ArrayList<Integer> call, int idx) { // idx is traversing the call
                                                                                  // arraylist

        if (idx == call.size()) {
            print2D(board);
            return 1;
        }

        int count = 0;

        int r = call.get(idx) / 9;
        int c = call.get(idx) % 9;

        int mask;

        for (int num = 1; num <= 9; num++) {
            mask = (1 << num);
            if ((row[r] & mask) == 0 && (col[c] & mask) == 0 && (mat[r / 3][c / 3] & mask) == 0) {
                board[r][c] = num;

                row[r] = (row[r] | mask);
                col[c] = (col[c] | mask);
                mat[r / 3][c / 3] = (mat[r / 3][c / 3] | mask);

                count += sudoku03(board, call, idx + 1);

                board[r][c] = 0;

                row[r] = (row[r] & ~mask);
                col[c] = (col[c] & ~mask);
                mat[r / 3][c / 3] = (mat[r / 3][c / 3] & ~mask);

            }
        }

        return count;
    }

    public static int sudoku_SS(int[][] board, ArrayList<Integer> call, int num, int idx) {

        if (num == 10 || idx == call.size()) {
            if (idx == call.size()) {
                print2D(board);
                return 1;
            } else
                return 0;
        }

        int count = 0;

        int r = call.get(idx) / 9;
        int c = call.get(idx) % 9;

        int mask = (1 << num);
        // num wants to sit at r,c

        if ((row[r] & mask) == 0 && (col[c] & mask) == 0 && (mat[r / 3][c / 3] & mask) == 0) {
            board[r][c] = num;

            row[r] = (row[r] | mask);
            col[c] = (col[c] | mask);
            mat[r / 3][c / 3] = (mat[r / 3][c / 3] | mask);

            count += sudoku_SS(board, call, 1, idx + 1);

            board[r][c] = 0;
            row[r] = (row[r] & ~mask);
            col[c] = (col[c] & ~mask);
            mat[r / 3][c / 3] = (mat[r / 3][c / 3] & ~mask);

        }
        // num doesnt want to sit at r,c
        count += sudoku_SS(board, call, num + 1, idx);

        return count;

    }

}
