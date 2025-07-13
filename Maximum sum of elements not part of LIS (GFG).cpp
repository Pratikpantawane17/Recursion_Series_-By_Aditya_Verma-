
// Brute Force
class Solution {

public:
void solve(vector<int> &arr, vector<int> temp, vector<int> &ans, int i, int n) {
    if(i == n) {
        if(temp.size() > ans.size()) ans = temp;
        else if(temp.size() == ans.size()) {
            int ansSum = 0, tempSum = 0;
            for(int i = 0; i<ans.size(); i++) ansSum += ans[i]; 
            for(int i = 0; i<temp.size(); i++) {
                tempSum += temp[i];
                if(tempSum > ansSum) break;
            } 
            if(ansSum > tempSum) ans = temp;
        }
        return;
    }
        
        if(temp.empty()) temp.push_back(arr[i]);
        else if(temp.size() >=1) {
            if(arr[i] > temp[temp.size() - 1]) temp.push_back(arr[i]);
        }
        solve(arr, temp, ans, i+1, n);
        
        temp.pop_back();
        solve(arr, temp, ans, i+1, n);
        
        return ;
}

 
    int nonLisMaxSum(vector<int>& arr) {
        // code here
        int n = arr.size();
        vector<int> temp = {};
        vector<int> ans = {};
        solve(arr, temp, ans, 0, n);
        int arrSum = 0, ansSum = 0;
        for(int i = 0; i<ans.size(); i++) ansSum += ans[i];
        for(int i = 0; i<n; i++) arrSum += arr[i];
        return abs(arrSum - ansSum);
    }
};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    Given an array arr[] of positive integers, find the maximum possible sum of all elements
    that are NOT part of the Longest Increasing Subsequence (LIS).

    Brute-force Recursive Approach:
    --------------------------------
    Time Complexity: O(2^n)  --> For each element, we either include or exclude.
    Not feasible for n > 20 due to exponential growth.

    ✅ Optimized Approach:
    ----------------------
    Use Dynamic Programming to compute LIS length and LIS sum efficiently.

    Time Complexity: O(n^2)
    Space Complexity: O(n)

    Logic:
    - dp[i] stores the length of LIS ending at index i
    - lisSum[i] stores the sum of LIS ending at index i
    - totalSum stores the sum of all elements
    - maxLisSum stores the max sum among all LIS
    - Final Answer = totalSum - maxLisSum
*/

// Tabulaion (Bottom to Top) --> 
class Solution {
public:
    int nonLisMaxSum(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, 1);      // LIS length ending at i
        vector<int> lisSum(n, 0);  // LIS sum ending at i

        // Initialize with arr[i] itself
        for (int i = 0; i < n; ++i) {
            lisSum[i] = arr[i];
        }

        // Build LIS info
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (arr[i] > arr[j] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    lisSum[i] = lisSum[j] + arr[i];
                } else if (arr[i] > arr[j] && dp[j] + 1 == dp[i]) {
                    lisSum[i] = max(lisSum[i], lisSum[j] + arr[i]);
                }
            }
        }

        int totalSum = 0, maxLisSum = 0;
        for (int i = 0; i < n; ++i) {
            totalSum += arr[i];
            maxLisSum = max(maxLisSum, lisSum[i]);
        }

        return totalSum - maxLisSum;
    }
};


// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*
    ✅ Summary:

    | Version              | Time Complexity | Space | Safe for n <= 1000 |
    |----------------------|-----------------|-------|--------------------|
    | Recursive Brute-force| O(2^n)          | O(n)  | ❌ (TLE, Runtime)   |
    | Optimized DP         | O(n^2)          | O(n)  | ✅                  |
    | Binary Search LIS    | O(n log n)      | O(n)  | ✅ (Advanced)       |

    ⚡ Note:
    A binary search based LIS approach can reduce time to O(n log n), but tracking sum of LIS becomes complex.
    The above O(n^2) version is optimal and clean for current constraints.
*/

// Example usage
int main() {
    Solution sol;
    vector<int> arr = {4, 6, 1, 2, 3, 8}; // Expected output: 10 (4+6 are not in LIS)
    cout << "Non-LIS Maximum Sum = " << sol.nonLisMaxSum(arr) << endl;
    return 0;
}
