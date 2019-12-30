class Solution {
    int largestRectangleArea(int[] heights) {
    	int[] stack = new int[heights.length + 1];
    	stack[0] = -1;
    	int top = 0;
    	int maxArea = 0;
    	for(int i = 0;i < heights.length;i++){
    		if(top <= 0 || heights[i] > heights[stack[top]]){
    			stack[++top] = i;
    		}else{
    			while(top > 0 && heights[i] <= heights[stack[top]]){
        			int tmp = heights[stack[top]] * (i - stack[top - 1] - 1);
        			maxArea = tmp > maxArea ? tmp : maxArea;
        			top--;	
    			}
    			stack[++top] = i;
    		}
    	}
    	for(int i = top;i > 0;i--){
    		int tmp = heights[stack[i]] * (stack[top] - stack[i - 1]);
    		maxArea = tmp > maxArea ? tmp : maxArea;
    	}
    	return maxArea;
    }
	
    public int maximalRectangle(char[][] matrix) {
    	int maxArea = 0;
    	if(matrix.length <= 0) return 0;
    	int[] val = new int[matrix[0].length];
        for(int i = 0;i < matrix.length;i++){
        	for(int j = 0;j < val.length;j++){
        		val[j] = (val[j] + 1) * (matrix[i][j] - '0');
        	}
        	int r = largestRectangleArea(val);
        	maxArea = r > maxArea ? r : maxArea;
        }
        return maxArea;
    }
}