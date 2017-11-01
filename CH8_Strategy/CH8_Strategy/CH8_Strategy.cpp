/*
 
 General strategy:
 
 1) see if DP is applicable ( i.e. problem has optimal substructure and overlapping subproblems )
 2) create recursive top-down solution
 3) create dp bottom-up solution
 
 */


#include <iostream>
#include <vector>

using namespace std;

/*
 
 8.1 given a two-dimensional square matrix cost[][] of order M*N where cost[i][j] represents
 the ocst of passing though cell (i,j).  Total cost to reach a particular cell is the sum
 of costs of all the cells in the path (including the starting and final cell).  We can only move
 either downard or rightward.  i.e.  If we are at cell (i,j) then we can either go to cell
 (i,j+1) or to (i+1,j).  Write a function that returns the minimum cost of moving from the top-left
 cell to the bottom-right cell of the matrix.
 
 */

/* Recursion + Memo */
class Solution{
public:
    int minCost(vector<vector<int>>& A){
        if (A.empty()) return 0;
        int r=(int)A.size(), c=(int)A[0].size();
        vector<vector<int>> memo(r, vector<int>(c,_INIT));
        return helper(A,r-1,c-1,memo);
    }
private:
    const int _INIT=-1;
    int helper(vector<vector<int>>& A, int r, int c, vector<vector<int>>& memo){
        if (memo[r][c]!=_INIT) return memo[r][c];
        if (r==0 && c==0) return memo[0][0]=A[0][0];
        if (r==0) return memo[r][c]=helper(A,0,c-1,memo) + A[r][c];
        if (c==0) return memo[r][c]=helper(A,r-1,0,memo) + A[r][c];
        int above=helper(A,r-1,c,memo);
        int left=helper(A,r,c-1,memo);
        return memo[r][c]=min(above,left) + A[r][c];
    }
};

/* DP */
class Solution2{
public:
    int minCost(vector<vector<int>>& A){
        if (A.empty()) return 0;
        int rows=(int)A.size(), cols=(int)A[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols,0));
        dp[0][0]=A[0][0];
        for (int r=1; r<rows; ++r)
            dp[r][0]=dp[r-1][0]+A[r][0];
        for (int c=1; c<cols; ++c)
            dp[0][c]=dp[0][c-1]+A[0][c];
        for (int r=1; r<rows; ++r){
            for (int c=1; c<cols; ++c){
                dp[r][c]=min(dp[r-1][c],dp[r][c-1])+A[r][c];
            }
        }
        return dp[rows-1][cols-1];
    }
};


int main(int argc, const char * argv[]) {
    
    vector<vector<int>> v {
        { 1,3,5,8 },
        { 4,2,1,7 },
        { 4,3,2,3 },
    };
    
    Solution solution;
    cout << solution.minCost(v) << endl;
    
    Solution2 solution2;
    cout << solution2.minCost(v) << endl;
    
    return 0;
}




