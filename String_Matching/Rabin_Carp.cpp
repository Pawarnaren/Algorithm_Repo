#include<bits/stdc++.h>
using namespace std;

vector<int>search(string P, string T){
    int m = P.size(); // length of pattern
    int n = T.size();  // length of text
    int q = 128;
    int x = 11;     // prime no so that it will be hard to collide
    int x_m = 1;     // x^(m-1) used for next hash computation
    int hash_P = 0; // hash of pattern 
    int hash_T = 0; // hash of the current window
    vector<int>ans;
        
    // cumputing the x^(m-1)
    for(int i=0; i<m-1; i++) 
         x_m = (x_m*x) % q;
        
    // hash of pattern and hash of first windown
    for(int i = 0; i<m; i++){
        hash_P = (hash_P*x + P[i]) % q;
        hash_T = (hash_T*x + T[i]) % q;
    }
        
    for(int i = 0; i<n-m+1; i++){
        if(hash_P == hash_T) {
            // there is a possibility of match
            // matching character by character
            bool found = true;
            for(int j=0; j<m; j++){
                if(P[j] != T[i+j]) {
                    found = false;
                    break;
                }
            }
            if(found) ans.push_back(i+1);
        }
            
        // checking the current window should not be last window
        if(i < n-m) {
            // computing the next hash function
            hash_T = x*(hash_T - T[i]*x_m) + T[i+m];
            hash_T = hash_T % q;
            if(hash_T < 0) hash_T += q;
        }
    }
        
    return ans;
}
