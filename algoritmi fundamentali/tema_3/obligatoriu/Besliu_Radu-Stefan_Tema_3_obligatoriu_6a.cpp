// Time Complexity: O(n * m) ( n = length of word 1, m = length of word 2 )
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        vector < vector < int >> dp(n + 1, vector < int > (m + 1));

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

//This algorithm is solving the problem of finding the longest common subsequence (LCS) between two strings, text1 and text2. The solution is using dynamic programming by building a 2D dp array of size (n+1)x(m+1), where n is the length of text1 and m is the length of text2.
//It iterates through the characters of both strings using nested loops. For each pair of characters text1[i-1] and text2[j-1], if they match, it updates the LCS length at that position as dp[i-1][j-1] + 1, otherwise it takes the maximum of LCS length at the previous position either dp[i-1][j] or dp[i][j-1].
//Finally it returns the value at the last cell of dp array which represents the LCS of the entire two strings. The time complexity of this algorithm is O(n*m), where n and m are the lengths of two input strings.