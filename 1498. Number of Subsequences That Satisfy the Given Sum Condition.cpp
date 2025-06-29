class Solution {

private :

    void solve(vector<int> &arr, vector<int> temp, int &cnt, int n, int i, int target) {
        if(i == n) {
                if(temp.size() > 0 && temp[0]+temp[temp.size()-1] <= target) cnt++;
            return ;
        }

        temp.push_back(arr[i]);
        solve(arr, temp, cnt, n, i+1, target);
        
        temp.pop_back();
        solve(arr, temp, cnt, n, i+1, target);
    }



public:
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> temp;
        int cnt = 0;
        sort(nums.begin(), nums.end());
        solve(nums, temp, cnt, n, 0, target);
        return cnt;
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// void funct converted to int...
class Solution {

private :

    int solve(vector<int> &arr, vector<int> temp, int &cnt, int n, int i, int target) {
        if(i == n) {
                if(!temp.empty() > 0 && temp[0]+temp[temp.size()-1] <= target)  return 1;
            return 0;
        }

        temp.push_back(arr[i]);
        int left = solve(arr, temp, cnt, n, i+1, target);
        
        temp.pop_back();
        int right = solve(arr, temp, cnt, n, i+1, target);

       return left + right;
    }



public:
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> temp;
        int cnt = 0;
        sort(nums.begin(), nums.end());
        return solve(nums, temp, cnt, n, 0, target);
    }
};


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// 🔹 Approach 1: Optimal Iterative Two-Pointer Method
class Solution {
    const int MOD = 1e9 + 7;

    int power(int x, int y, int mod) {
        long long res = 1;
        while (y > 0) {
            if (y & 1)
                res = (res * x) % mod;
            x = (1LL * x * x) % mod;
            y >>= 1;
        }
        return res;
    }

public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int left = 0, right = n - 1;
        int ans = 0;

        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                ans = (ans + power(2, right - left, MOD)) % MOD;
                left++;
            } else {
                right--;
            }
        }

        return ans;
    }
};


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// 🔹 Approach 2: Recursive + Memoization Method
class Solution {
    const int MOD = 1e9 + 7;

    int power(int x, int y, int mod) {
        long long res = 1;
        while (y > 0) {
            if (y & 1)
                res = (res * x) % mod;
            x = (1LL * x * x) % mod;
            y >>= 1;
        }
        return res;
    }

    int solve(int i, int j, vector<int>& nums, int target, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (nums[i] + nums[j] > target)
            return dp[i][j] = solve(i, j - 1, nums, target, dp);

        int count = (power(2, j - i, MOD) + solve(i + 1, j, nums, target, dp)) % MOD;
        return dp[i][j] = count;
    }

public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, n - 1, nums, target, dp);
    }
};


