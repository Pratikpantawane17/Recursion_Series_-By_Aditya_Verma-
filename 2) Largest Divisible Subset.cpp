class Solution {

// Approach 1 :
bool check(vector<int> temp) {
    int m = temp.size();
    for(int i = 0; i < m-1; i++) {
        for(int j = i+1; j<m; j++) {
            if(temp[j] % temp[i] != 0 && temp[i] % temp[j] != 0) return false;
        }
    }
    return true;
}

void solve(vector<int> &arr, vector<vector<int>> &ans, vector<int> temp, int &maxi, int n) {
    if(n == 0) {
        if(temp.size() >= maxi) {
            if(check(temp)) {
                sort(temp.begin(), temp.end());
                if(temp.size() > maxi) {
                    maxi = temp.size();
                    ans.clear();
                }
                ans.push_back(temp); 
            }
        }
        return;
    }
    
    temp.push_back(arr[n-1]);
    solve(arr, ans, temp, maxi, n-1);
    
    temp.pop_back();
    solve(arr, ans, temp, maxi, n-1);
    
}

// Approach 2 :
bool check2(vector<int> temp, int val) {
    for(int i = 0; i<temp.size(); i++) {
        if(val % temp[i] != 0 && temp[i] % val != 0) return false;
    }
    return true;
}


void solve2(vector<int> &arr, vector<vector<int>> &ans, vector<int> temp, int &maxi, int n, int i) {
    if(i == n) {
            if(temp.size() > maxi) {
                maxi = temp.size();
                ans.clear();
                ans.push_back(temp);
            }
            else if (temp.size() == maxi) ans.push_back(temp);
            
       return;
    }
    
    if(check2(temp, arr[i])) {
        temp.push_back(arr[i]);
        solve2(arr, ans, temp, maxi, n, i+1);
        
        temp.pop_back();
    }
    
    solve2(arr, ans, temp, maxi, n, i+1);
}

public:
    vector<int> largestSubset(vector<int>& arr) {
        // Code here
        // Approach : 
        int n = arr.size();
        vector<vector<int>> ans;
        vector<int> temp;
        int maxi = 0;
        
        // Approach 1 :
        // solve(arr, ans, temp, maxi, n);

        // Approach 2 :
        sort(arr.begin(), arr.end());
        solve2(arr, ans, temp, maxi, n, 0);
        
        if(ans.empty()) return {};
        
        sort(ans.begin(), ans.end());
        return ans.back();
    }
};


// Please the "DP Approach" also bcz it is somehow looks not to understand.....
