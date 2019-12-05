#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;
        if (grid[0].empty())
            return 0;
        const int m = grid.size() - 1;
        const int n = grid[0].size() - 1;
        int row, col;
        /* 处理下边界 */
        for (col = n - 1; col >= 0; col--)
            grid[m][col] += grid[m][col + 1];
        /* 处理右边界 */
        for (row = m - 1; row >= 0; row--)
            grid[row][n] += grid[row + 1][n];
        /* 处理一般情况 */
        for (row = m - 1; row >= 0; row--)
            for (col = n - 1; col >= 0; col--)
                    grid[row][col] += grid[row + 1][col] < grid[row][col + 1] ? 
                        grid[row + 1][col] : grid[row][col + 1];
        return grid[0][0];
    }
};