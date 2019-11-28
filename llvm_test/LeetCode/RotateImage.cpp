#include <vector>

using namespace std;

class Solution {
    template<class T> void swapElement(T& a, T& b)
    {
        a += b;
        b = a - b;
        a -= b;
    }
public:
    void rotate(vector<vector<int>>& matrix) {
        const int N = matrix.size();
        /* 从外到里置换 */
        for (int row = 0; row < N / 2; row++)
            for (int col = row; col < N - row - 1; col++)
            {
                swapElement(matrix[row][col], matrix[N - 1 - col][row]);
                swapElement(matrix[N - 1 - col][row], matrix[N - 1 - row][N - 1 - col]);
                swapElement(matrix[N - 1 - row][N - 1 - col], matrix[col][N - 1 - row]);
            }
    }
};