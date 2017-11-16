/*
 
 DP using the FAST method ( www.byte-by-byte.com )
 
 1) First solution ( recursive top-down )
 2) Analyze the first solution
 3) Subproblem identification
 4) Turn the solution around ( from recursive top-down to DP bottom-up )
 
 */

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/* Fibonacci Sequence */
class Solution1 {
public:
    
    /* recursive solution O(2^n) time and space */
    int Fib(int n){
        if (n<2) return n;
        return Fib(n-2)+Fib(n-1);
    }
    
    /* DP solution O(n) time and space */
    int FibDP(int n){
        vector<int> dp(n+1);
        dp[0]=0;
        dp[1]=1;
        for (int i=2; i<=n; ++i)
            dp[i]=dp[i-2]+dp[i-1];
        return dp[n];
    }
    
    /* DP solution O(n) time and O(1) space */
    int FibDP2(int n){
        if (n<2) return n;
        int f2=0, f1=1, fn=1;
        for (int i=2; i<=n; ++i)
            fn=f2+f1; f2=f1; f1=fn;
        return fn;
    }
};

/*
 
 Coin Change
 
 Given an integer representing a given amount of change,
 write a function to compute the minumum number of coins
 required to make that amount of change.  You may assume
 there is always a 1 cent coin.
 
 */
class Solution2 {
public:
    /* 
     recursive solution
     O(m^n) time/space, where m is the amount
     and n is the size of the vector coins
     */
    int minCoins(int amount, vector<int>& coins){
        static const int INIT=-1;
        if (amount==0) return 0;
        set<int> cnt{};
        for (auto &&coin: coins)
            if (coin<=amount){
                int res=minCoins(amount-coin,coins);
                if (res!=INIT)
                    cnt.insert(1+res);
            }
        return (cnt.empty() ? INIT : *min_element(cnt.begin(),cnt.end()));
    }
    
    /*
     recursive solution w/ memo
     O(m*n) time, O(m) space, where m is the amount
     and n is the size of the vector coins
     */
    int minCoinsMemo(int amount, vector<int>& coins){
        static const int INIT=-1;
        vector<int> memo(amount+1,INIT);
        return helper(amount,coins,memo);
    }
    int helper(int amount, vector<int>& coins, vector<int>& memo){
        static const int INIT=-1;
        if (memo[amount]!=INIT) return memo[amount];
        if (amount==0) return memo[0]=0;
        set<int> cnt{};
        for (auto &&coin: coins)
            if (coin<=amount){
                int res=helper(amount-coin,coins,memo);
                if (res!=INIT)
                    cnt.insert(1+res);
            }
        return memo[amount]=(cnt.empty() ? INIT : *min_element(cnt.begin(),cnt.end()));
    }
    
    
    /* 
     DP solution
     O(m*n) time, O(m) space, where m is the amount
     and n is the size of the vector coins
     */
    int minCoinsDP(int amount, vector<int>& coins){
        static const int INIT=-1;
        vector<int> dp(amount+1,INIT);
        dp[0]=0;
        for (int i=1; i<=amount; ++i)
            for (auto &&coin: coins)
                if (coin<=i && dp[i-coin]!=INIT)
                    dp[i]=dp[i]==INIT ? 1+dp[i-coin] : min(dp[i],1+dp[i-coin]);
        return dp[amount];
    }
    
    
};

/*
 
 Square Boolean Submatrix
 
 Given a 2D boolean vector, find the largest square subarray of True values.
 The return value should be the side length of the largest square submatrix
 
 */
class Solution3 {
public:
    
    /* recursive solution O(m*n*3^(n+m)) time and O(n*m) space */
    int maxSubmatrix(vector<vector<bool>>& matrix){
        if (matrix.empty() || matrix[0].empty()) return 0;
        int maxi=0,m=(int)matrix.size(),n=(int)matrix[0].size();
        for (int i=0; i<m; ++i)
            for (int j=0; j<n; ++j)
                maxi=max(maxi,helper(matrix,i,j,m,n));
        return maxi;
    }
    int helper(vector<vector<bool>>& matrix, int i, int j, int m, int n){
        if (i==m || j==n || !matrix[i][j]) return 0;
        return 1+min({                  // +1 for current cell i,j==true
            helper(matrix,i,j+1,m,n),   // right
            helper(matrix,i+1,j,m,n),   // below
            helper(matrix,i+1,j+1,m,n)  // below & right ( diagonal )
        });
    }
    
    /* DP solution O(m*n) time and space */
    int maxSubmatrixDP(vector<vector<bool>>& matrix){
        if (matrix.empty() || matrix[0].empty()) return 0;
        int maxi=0,m=(int)matrix.size(),n=(int)matrix[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0));
        for (int i=0; i<m; ++i) dp[i][n-1]=matrix[i][n-1] ? 1 : 0;    // right-most col
        for (int j=0; j<n; ++j) dp[m-1][j]=matrix[m-1][j] ? 1 : 0;    // bottom row
        for (int i=m-2; i>=0; --i){
            for (int j=n-2; j>=0; --j){
                dp[i][j]=matrix[i][j]
                    ? 1+min({
                            dp[i][j+1],     // right
                            dp[i+1][j],     // below
                            dp[i+1][j+1]})  // below & right ( diagonal )
                    : 0;
                maxi=max(maxi,dp[i][j]);
            }
        }
        return maxi;
    }
};

/*
 
 Imagine that you have a knapsack which can carry a certain maximum amount of weight
 and you have a set of items with their own weight and a monetary value.  You are going
 to sell your items in the market but you can only carry what fits in the knapsack.
 How do you maximize the amount of money that you can earn?
 
 More formally: Given a list of items with values and weights, as well as a max weight,
 find the maximum value you can generate from items, where the sum of the weights
 is less than or equal to the max.
 
 Example:
 
 items = {(w:2, v:6), (w:2, v:10), (w:3, v:12)}
 max weight = 5
 knapsack(items, max weight)=22
 
 */
class Item {
public:
    int weight, value;
    Item(int weight, int value) : weight{weight}, value{value} {}
};

class Solution4 {
public:
    
    /* recursive solution O(2^n) time and O(n) space */
    int knapsack(vector<Item>& items, int capacity){
        int maxi=0;
        for (int i=0; i<items.size(); ++i){
            maxi=max(maxi,helper(items,i,capacity));
        }
        return maxi;
    }
    int helper(vector<Item>& items, int i, int capacity){
        if (i==items.size()) return 0;
        return items[i].weight<=capacity
            ? max(items[i].value+helper(items,i+1,capacity-items[i].weight), // with
                  helper(items,i+1,capacity))  // without
            : helper(items,i+1,capacity);      // without
    }
    
    /* DP solution O(n^2) time and space */
    int knapsackDP(vector<Item>& items, int capacity){
        int m=(int)items.size(),n=capacity;
        vector<vector<int>> dp(m+1,vector<int>(n+1,0)); // dp[i] corresponds to item[i-1]
        for (int i=0; i<=m; ++i) dp[i][0]=0; // items ( start with 0 == no item )
        for (int j=0; j<=n; ++j) dp[0][j]=0; // weight capacity ( start with 0 == no weight )
        for (int i=1; i<=m; ++i){
            for (int j=1; j<=n; ++j){
                dp[i][j]=(items[i-1].weight<=j)
                    ? max(items[i-1].value+dp[i-1][j-items[i-1].weight], // with
                          dp[i-1][j])   // without
                    : dp[i-1][j];       // without
            }
        }
        return dp[m][n];
    }
};

int main(int argc, const char * argv[]) {
    
    /* Fibonacci Sequence */
    /*
    Solution1 s1;
    while (true){
        int n;
        cout << "n: ";
        cin >> n;
        cout << endl << "Fib(" << n << ")==";
        cout << s1.Fib(n) << "==" << s1.FibDP(n) << "==" << s1.FibDP2(n) << endl << endl;
    }
     */
    
    /* Coin Change */
    /*
    Solution2 s2;
    vector<int> coins { 2,5,10,1 };
    while(true){
        int amount;
        cout << "amount: ";
        cin >> amount;
        cout << s2.minCoins(amount,coins) << endl;
        cout << s2.minCoinsMemo(amount,coins) << endl;
        cout << s2.minCoinsDP(amount,coins) << endl;
    }
     */
    
    /* Square Boolean Submatrix */
    /*
    Solution3 s3;
    const bool T=true;
    const bool F=false;
    vector<vector<bool>> matrix{
        { T,F,T,F },
        { T,T,F,F },
        { T,T,T,F },
    };
    cout << s3.maxSubmatrix(matrix) << endl;
    cout << s3.maxSubmatrixDP(matrix) << endl;
    */
    
    Solution4 s4;
    vector<Item> items {
        Item(2,6),
        Item(2,10),
        Item(3,12),
        Item(1,7)
    };
    cout << s4.knapsack(items, 2) << endl;
    cout << s4.knapsackDP(items, 2) << endl;
    
    return 0;
}


