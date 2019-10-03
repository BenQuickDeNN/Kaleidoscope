
#include <vector>

using namespace std;

class Solution
{
public:
    int maxArea(vector<int>& height) {
        unsigned int sIdx = 0;  // index of start position
        unsigned int eIdx = height.size() - 1; // index of end positon
        unsigned int maxA = 0; // maximum area
        unsigned int tmpA;  // temp var that stores area
        /* Two poiter method */
        while (sIdx < eIdx)
        {
            if (height[sIdx] < height[eIdx])
            {
                tmpA = (eIdx - sIdx) * height[sIdx];
                sIdx++;
            }
            else
            {
                tmpA = (eIdx - sIdx) * height[eIdx];
                eIdx--;
            }
            if (tmpA > maxA)
                maxA = tmpA;
        }
        return maxA;
    }

    int BruteMetod(vector<int>& height)
    {

    }
};

int main()
{
    
}