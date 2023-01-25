// Time Complexity: O(n * m) ( n = length of word 1, m = length of word 2 )
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        vector< vector < int >> dp(n + 1, vector < int > (m + 1));

        // Iterate through the characters in text1
        for (int i = 1; i <= n; ++i) {
            // Iterate through the characters in text2
            for (int j = 1; j <= m; ++j) {
                // If the characters at the current indices match
                if (text1[i-1] == text2[j-1]) {
                    // The length of the LCS at the current indices is equal to the LCS at the previous indices + 1
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    // Otherwise, the length of the LCS at the current indices is 
                    // the maximum of the LCS at the previous indices
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        // Return the length of the LCS of the entire strings
        return dp[n][m];
    }
};