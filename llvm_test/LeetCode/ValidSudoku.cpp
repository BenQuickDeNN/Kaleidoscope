#include <cstdio>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool checker[9];
        /* check row */
        for (int row = 0; row < 9; row++)
        {
            for (int i = 0; i < 9; i++)
                checker[i] = false;
            for (int col = 0; col < 9; col++)
                if (board[row][col] != '.')
                    if (!checker[board[row][col] - '1'])
                        checker[board[row][col] - '1'] = true;
                    else
                    {
                        printf("row=%d, col=%d\r\n", row, col);
                        return false;
                    }
        }
        /* check col */
        for (int col = 0; col < 9; col++)
        {
            for (int i = 0; i < 9; i++)
                checker[i] = false;
            for (int row = 0; row < 9; row++)
                if (board[row][col] != '.')
                    if (!checker[board[row][col] - '1'])
                        checker[board[row][col] - '1'] = true;
                    else
                    {
                        printf("row=%d, col=%d\r\n", row, col);
                        return false;
                    }
        }
        /* check block */
        for (int block = 0; block < 9; block++)
        {
            for (int i = 0; i < 9; i++)
                checker[i] = false;
            for (int row = (block / 3) * 3; row < (block / 3) * 3 + 3; row++)
                for (int col = (block % 3) * 3; col < (block % 3) * 3 + 3; col++)
                    if (board[row][col] != '.')
                        if (!checker[board[row][col] - '1'])
                            checker[board[row][col] - '1'] = true;
                        else
                        {
                            printf("block=%d, row=%d, col=%d\r\n", block, row, col);
                            return false;
                        }
        }
        return true;
    }
};