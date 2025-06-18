// Question : All Palindromic Partitions
// Link : https://www.geeksforgeeks.org/problems/find-all-possible-palindromic-partitions-of-a-string/1

// COde : 
class Solution {
    
private : 

 // Function to check if a string is palindrome
bool isPalindrome(string &s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

// Backtracking function
void solve(int index, string &s, vector<string> &path, vector<vector<string>> &result) {
    if (index == s.size()) {
        result.push_back(path); // Base case
        return;
    }

    for (int i = index; i < s.size(); i++) {
        if (isPalindrome(s, index, i)) {
            path.push_back(s.substr(index, i - index + 1)); // Take the palindromic substring
            solve(i + 1, s, path, result);                  // Recur for the remaining string
            path.pop_back(); // Backtrack
        }
    }
}
    
    
    
 public:
    vector<vector<string>> palinParts(string &s) {
        // code here
        vector<vector<string>> result;
        vector<string> path;
        solve(0, s, path, result);
        return result;
    }
};

