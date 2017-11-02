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

/*
 
 8.2 given an empty plot of size 2xN, we want to place tiles such that
 the entire plot is covered.  Each tile is of size 2x1 and can be placed
 either horizontally or vertically.  If N is 5, then one way to cover the plot
 is shown below:
 
 Before: ( X is an empty cell )
 XXXXX
 XXXXX
 
 After: ( 5 tiles: A, B, C, D, and E )
 ABBDE
 ACCDE
 
 Write a function which accepts N as input and return the total number of ways
 in which we can place tiles (without breaking any tile).
 
 */
class Solution3 {
public:
    int tilePlacements(int n){
        vector<int> memo(n+1,0);
        return helper(n,memo);
    }
private:
    int helper(int n, vector<int>& memo){
        if (memo[n]) return memo[n];
        if (n<=3) return memo[n]=n;
        return memo[n]=helper(n-1,memo)+helper(n-2,memo);
    }
};

/*
 
 If size of the plot in 8.2 above is changed to 3*n, then what changes
 do we need to make in the solution?  Below diagram shows one of the possible
 arrangements on a plot of size 3*n where n=12.
 
 */

//
// TODO
//


/*
 
 8.3 consider a game where a player can score 3, 5, or 10 points in one move.
 Given a total score N, find the total number of unique ways to reach a score of N.
 
 For example: If N=13, output should be 5 because there are 5 ways to reach
 a score of 13 as shown below:
 
 (3,5,5), (5,3,5), (5,5,3), (3,10), (10,3)
 
 */

/* recursion + memo */
class Solution4 {
public:
    int uniqueScores(int n, const vector<int>& points){
        vector<int> memo(n+1,_INIT);
        return helper(n,points,memo);
    }
    int count;
private:
    const int _INIT=-1;
    int helper(int n, const vector<int>& points, vector<int>& memo){
        if (n<0) return 0;
        if (n==0) return 1;
        if (memo[n]!=_INIT) return memo[n];
        int cnt=0;
        for (int i=0; i<points.size(); ++i){
            cnt+=helper(n-points[i], points, memo);
        }
        return memo[n]=cnt;
    }
};

/* dp */
class Solution5 {
public:
    int uniqueScores(int n, const vector<int>& points){
        vector<int> dp(n+1,0);
        dp[0]=1;
        for (int i=0; i<=n; ++i){
            for (int j=0; j<points.size(); ++j){
                int point=points[j];
                if (n-point>=0) dp[i]+=dp[i-point];
            }
        }
        return dp[n];
    }
};

/*
 
 What is the total number of ways to reach a particular score
 if (10,3) and (3,10) are considered the same.  Modify your function accordingly.
 
 */

//
// TODO
//

int main(int argc, const char * argv[]) {
    
    /*
    vector<vector<int>> v {
        { 1,3,5,8 },
        { 4,2,1,7 },
        { 4,3,2,3 },
    };
    
    Solution solution;
    cout << solution.minCost(v) << endl;
    
    Solution2 solution2;
    cout << solution2.minCost(v) << endl;
     */
    
    /*
    Solution3 solution3;
    cout << solution3.tilePlacements(6) << endl;
    */

    vector<int> points { 3,5,10 };
    Solution4 solution4;
    cout << solution4.uniqueScores(13, points) << endl;
    
    Solution5 solution5;
    cout << solution5.uniqueScores(13, points) << endl;
    
    
    return 0;
}




