/*
 
 DP using the FAST method ( www.byte-by-byte.com )
 
 1) First solution ( recursive top-down )
 2) Analyze the first solution
 3) Subproblem identification
 4) Turn the solution around ( from top-down to bottom-up )
 
 */

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/* Fibonacci sequence */
class Solution1 {
public:
    
    /* recursive solution O(2^n) time and space */
    int Fib(int n){
        if (n<2) return n;
        return Fib(n-2)+Fib(n-1);
    }
    
    /* dp solution O(n) time and space */
    int FibDP(int n){
        vector<int> dp(n+1);
        dp[0]=0;
        dp[1]=1;
        for (int i=2; i<=n; ++i)
            dp[i]=dp[i-2]+dp[i-1];
        return dp[n];
    }
    
    /* dp solution O(n) time and O(1) space */
    int FibDP2(int n){
        if (n<2) return n;
        int f2=0, f1=1, fn=1;
        for (int i=2; i<=n; ++i)
            fn=f2+f1; f2=f1; f1=fn;
        return fn;
    }
};

/*
 
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
     O(mn) time, O(m) space, where m is the amount
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
     dp solution
     O(mn) time, O(m) space, where m is the amount
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
    
    Solution2 s2;
    vector<int> coins { 2,5,10,1 };
    while(true){
        int amount;
        cout << "amount: ";
        cin >> amount;
        cout << s2.minCoins(amount,coins) << endl;
        cout << s2.minCoinsMemo(amount,coins) << endl;
        cout << s2.minCoinsDP(amount,coins) << endl;
        
        cout << "mc1= " << s2.mc1 << endl;
        cout << "mc2= " << s2.mc2 << endl;
    }
    
    
    return 0;
}


