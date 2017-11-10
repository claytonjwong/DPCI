/*
 
 CH9: Practice Questions
 
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 
 9.1 Edit Distance: the words COMPUTER and COMMUTER are very similiar, and an update
 of just one letter, P->M will change the first word into the second.  Similiarly,
 the word SPORT can be changed into SORT by deleting one character, P, or equivalently,
 SORT can be changed into SPORT by inserting P.
 
 Edit distance between two strings is defined as the minimum number of character operations
 (update, delete, insert) required to convert one string into another.
 
 Given two strings, and the following 3 operations which can be performed on the first string
 ( insert, remove, replace ), find the minimum number of operations required to convert
 the first string into the second string.  For example, if the two strings are CAT and CAR,
 then the edit distance is 1.  T is replaced with R.  Similiarly, if the two strings are
 SUNDAY and SATURDAY, then the edit distance is 3.
 
 S  UNDAY
 SATURDAY
 12 3
 
 */

/* recursive solution O(3^n) */
class SolutionREC {
public:
    int editDistance(string s1, string s2){
        return helper(s1,s2,0,0);
    }
    
    int helper(const string& s1, const string& s2, int i, int j){
        if (i >= s1.size()) return (int)s2.size()-j;
        if (j >= s2.size()) return (int)s1.size()-i;
        if (s1[i]==s2[j]) return helper(s1,s2,i+1,j+1); // same
        int insert=1+helper(s1,s2,i,j+1);
        int remove=1+helper(s1,s2,i+1,j);
        int replace=1+helper(s1,s2,i+1,j+1);
        return min({insert,remove,replace});
    }
};

/* DP solution O(n^2) */
class SolutionDP {
public:
    int editDistance(string s1, string s2){
        int m=(int)s1.size(), n=(int)s2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1));
        for (int i=0; i<=m; ++i)
            dp[i][0]=i;
        for (int j=0; j<=n; ++j)
            dp[0][j]=j;
        //printDP(dp);
        for (int i=1; i<=m; ++i){
            for (int j=1; j<=n; ++j){
                if (s1[i-1]==s2[j-1]){ // same
                    dp[i][j]=dp[i-1][j-1];
                } else {
                    dp[i][j]=1+min({
                        dp[i-1][j],   // insert
                        dp[i][j-1],   // remove
                        dp[i-1][j-1], // replace
                    });
                }
                //printDP(dp);
            }
        }
        return dp[m][n];
    }
    
    void printDP(vector<vector<int>>& dp){
        if (dp.empty()) return;
        if (dp[0].empty()) return;
        for (int i=0; i<dp.size(); ++i){
            for (int j=0; j<dp[0].size(); ++j)
                cout << dp[i][j];
            cout << endl;
        }
        cout << endl;
    }
};

int main(int argc, const char * argv[]) {
    
    SolutionREC solutionREC;
    SolutionDP solutionDP;
    while(true){
        string s1="",s2="";
        cout << "s1: ";
        cin >> s1;
        cout << "s2: ";
        cin >> s2;
        cout << "rec: " << solutionREC.editDistance(s1, s2) << endl;
        cout << " dp: " << solutionDP.editDistance(s1, s2) << endl << endl;
    }
    
    
    return 0;
}


