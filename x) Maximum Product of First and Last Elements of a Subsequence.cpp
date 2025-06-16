// Question : https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/description/

// Makes Better Understanding....
// Code (Recursive COde only): 
class Solution {

private : 
void solve(vector<int> &arr, long long &maxi, vector<int> temp, int n, int m) {
    if (n == 0) {
        if (m == 0) {
            long long ans = (long long)temp[0] * (long long)temp[temp.size() - 1];
            maxi = max(maxi, ans);
        }
        return ;
    }

    temp.push_back(arr[n-1]);
    solve(arr, maxi, temp, n-1, m-1);

    temp.pop_back();
    solve(arr, maxi, temp, n-1, m);
}
    
    
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();
        vector<int> temp;
        long long maxi = LLONG_MIN;
       
        solve(nums, maxi, temp, n, m);
        
        return maxi == LLONG_MIN ? 0 : maxi;
    }
};
