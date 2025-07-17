class Solution {

// MLE (Memory limit exceed): 792 / 951 testcases passed
// Note : Jitne variable Chnage hote hai utne variables ka demension ka dp vector of vector of vector..... banta hai
// eg. 🛠️ Step 2: Replace temp with Trackable Parameters
// Instead of passing the whole temp vector, track:
// len: current length of selected elements
// lastParity: (arr[i-1] % 2)
 // => vector<vector<vector<vector<int>>>>& dp)



secondLastParity: (arr[i-2] % 2) — or -1 if not enough elements yet

private :
void solve(vector<int> &arr, vector<int> temp, int &maxi, int i, int n) {
    if(i == n) {
        if(temp.size() > maxi) maxi = temp.size();
        return ;
    }

    // push
    if(temp.size() <= 1) temp.push_back(arr[i]);
    else {
        int n = temp.size();
        int val1 = (temp[n-2]+temp[n-1]) % 2;
        int val2 = (temp[n-1]+arr[i]) % 2;
        if(val1 == val2) temp.push_back(arr[i]);
    }
    solve(arr, temp, maxi, i+1, n);

    // pop
    if(!temp.empty()) temp.pop_back();
    solve(arr, temp, maxi, i+1, n);
}


public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp;
        int maxi = 0;
        solve(nums, temp, maxi, 0, n);
        return maxi;
    }
};


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Memoized Version : 
class Solution {

int solve(vector<int> &arr, int i, int len, int last, int secondLast, int n, vector<vector<vector<vector<int>>>> &dp) {
    if(i == n) return len;

    if(dp[i][len][last][secondLast] != -1) return dp[i][len][last][secondLast];

    // can we push ?
    int pick = 0;
    int parity = arr[i] % 2;

    if(len <= 1 || (last+secondLast)%2 == (last+parity)%2) {
        pick = solve(arr, i+1, len+1, parity, last, n, dp);
    }

    // pop - not to push
    int notPick = solve(arr, i+1, len, last, secondLast, n, dp);

    return dp[i][len][last][secondLast] = max(pick, notPick);
}


public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(3, vector<int>(3, -1))));

        return solve(nums, 0, 0, 2, 2, n, dp);
    }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//  Tabulation Version (Try by your own  not done by me ): 
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int K) {
        int n = nums.size();
        // K+1 to account for undefined state (K means undefined)
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(K+1, vector<int>(K+1, 0)));

        // Base case: No element taken yet
        dp[0][K][K] = 0;

        for(int i = 0; i < n; ++i) {
            int currRem = nums[i] % K;

            // Make a copy of current dp to update for next step
            auto new_dp = dp;

            for(int len = 0; len <= n; ++len) {
                for(int last = 0; last <= K; ++last) {
                    for(int secondLast = 0; secondLast <= K; ++secondLast) {

                        int currentLen = dp[len][last][secondLast];

                        // Option 1: Not pick nums[i]
                        new_dp[len][last][secondLast] = max(new_dp[len][last][secondLast], currentLen);

                        // Option 2: Try to pick nums[i]
                        bool valid = false;

                        if(len <= 1) valid = true;
                        else if(last != K && secondLast != K)
                            valid = ((secondLast + last) % K == (last + currRem) % K);

                        if(valid) {
                            // Shift: current becomes 'last', last becomes 'secondLast'
                            new_dp[len + 1][currRem][last] = max(new_dp[len + 1][currRem][last], currentLen + 1);
                        }
                    }
                }
            }

            dp = move(new_dp);
        }

        // Find max length
        int ans = 0;
        for(int len = 0; len <= n; ++len)
            for(int last = 0; last <= K; ++last)
                for(int secondLast = 0; secondLast <= K; ++secondLast)
                    ans = max(ans, dp[len][last][secondLast]);

        return ans;
    }
};








