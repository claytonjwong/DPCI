/*
 
 CH4: Overlapping Subproblems
 
 */


#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class Solution{
public:
    
    Solution() {
        
        _cost = {
            /* src       0   1   2   3 dst */
            
            /* 0   */ {  0, 10, 75, 94 },
            
            /* 1   */ { -1,  0, 35, 50 },
            
            /* 2   */ { -1, -1,  0, 80 },
            
            /* 3   */ { -1, -1, -1,  0 }
        };
    }
    
    int Fib(unsigned int n){
        
        if (n==0) { return 0; }
        if (n<=2) { return 1; }
        vector<int> lookup(n+1, 0); lookup[0]=0; lookup[1]=1; lookup[2]=1;
        for (int i=3; i<=n; i++){
            lookup[i]=lookup[i-2]+lookup[i-1];
        }
        return lookup[n];
    }
    
    int minCost(int src, int dst){
        
        int minimum=Cost(src,dst);
        if (minimum == -1){ throw out_of_range("invalid src/dst"); }
        for (int i=src+1; i < dst; i++){
            int curr=Cost(0,i)+Cost(i,dst);
            if (curr < minimum){
                minimum=curr;
            }
        }
        return minimum;
    }
    
    /*----------------------------------------------------------------------
     Given a matrix of order M*N.  What are the total number of ways
     in which we can move from the top-left cell m[0][0] to the bottom-right
     cell m[m-1][n-1], given that we can only move either doward or rightward?
     ----------------------------------------------------------------------*/
//    int pathCount(int m, int n){
//        
//        if (m==0 && n==0){ return 0; }
//        if (m==0 || n==0){ return 1; }
//        return pathCount(m-1, n) + pathCount(m, n-1);
//    }
    
private:
    
    vector<vector<int>> _cost;
    
    int Cost(int src, int dst){
        
        if (src < 0 || src > _cost.size()) { return -1; }
        if (dst < 0 || dst > _cost.size()) { return -1; }
        
        return _cost[src][dst];
    }
};


int main(int argc, const char * argv[]) {

    
    Solution solution;
    int cnt = solution.pathCount(1, 1);
    
    

    
    
    
    
    return 0;
}









