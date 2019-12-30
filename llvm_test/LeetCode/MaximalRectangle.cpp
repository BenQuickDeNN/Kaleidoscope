#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        const int m = matrix.size();
        if (m == 0)
            return 0;
        const int n = matrix[0].size();
        int left[n] = {0};
        int right[n] = {n};
        int height[n] = {0};

        int cur_left, cur_right;

        int maxarea = 0;
        for (int i = 0; i < m; i++)
        {
            cur_left = 0;
            cur_right = n;
            // update height
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == '1')
                    height[j]++;
                else
                    height[j] = 0;
            // update left
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == '1')
                {
                    if (left[j] < cur_left)
                        left[j] = cur_left;
                }
                else
                {
                    left[j] = 0;
                    cur_left = j + 1;
                }
            // update right
            for (int j = n - 1; j >= 0; j--)
                if (matrix[i][j] == '1')
                {
                    if (right[j] > cur_right)
                        right[j] = cur_right;
                }
                else
                {
                    right[j] = n;
                    cur_right = j;
                }
            // update area
            for (int j = 0; j < n; j++)
                maxarea = max(maxarea, abs(right[j] - left[j]) * height[j]);
        }
        return maxarea;
    }
};