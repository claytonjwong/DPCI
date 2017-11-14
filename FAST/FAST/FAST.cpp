/*
 
 DP using the FAST method ( www.byte-by-byte.com )
 
 1) First solution ( recursive top-down )
 2) Analyze the first solution
 3) Subproblem identification
 4) Turn the solution around ( from top-down to bottom-up )
 
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 
 Fibonacci sequence
 
 */
class Solution1 {
public:
    /* O(2^n) time and space */
    int Fib(int n){
        if (n<2) return n;
        return Fib(n-2)+Fib(n-1);
    }
    
    /* O(n) time and space */
    int FibDP(int n){
        vector<int> dp(n+1);
        dp[0]=0;
        dp[1]=1;
        for (int i=2; i<=n; ++i)
            dp[i]=dp[i-2]+dp[i-1];
        return dp[n];
    }
    
    /* O(n) time and O(1) space */
    int FibDP2(int n){
        if (n<2) return n;
        int f2=0, f1=1, fn=1;
        for (int i=2; i<=n; ++i){
            fn=f2+f1;
            f2=f1;
            f1=fn;
        }
        return fn;
    }
};

int main(int argc, const char * argv[]) {
    
    Solution1 s1;
    while (true){
        int n;
        cout << "n: ";
        cin >> n;
        cout << endl << "Fib(" << n << ")==";
        cout << s1.Fib(n) << "==" << s1.FibDP(n) << "==" << s1.FibDP2(n) << endl << endl;
    }
    
    
    return 0;
}


