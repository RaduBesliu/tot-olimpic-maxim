// Time Complexity: O(n * m) ( n = length of word 1, m = length of word 2 )
// Find the shortest common supersequence of strings A and B.
class Solution {
public:
    string shortestCommonSupersequence(string& A, string& B) {
        int i = 0; // index for string A
        int j = 0; // index for string B
        string res = ""; // result string to be returned

        // For each character in the longest common subsequence of A and B
        for (char const& c: lcs(A, B)) {
            // Move the index for string A up until the current character is found
            while (A[i] != c) {
                res += A[i++];
            }
            // Move the index for string B up until the current character is found
            while (B[j] != c) {
                res += B[j++];
            }
            // Add the current character to the result string
            res += c;
            ++i; // move the index for string A up by 1
            ++j; // move the index for string B up by 1
        }

        // Add the remaining characters in string A to the result string
        return res + A.substr(i) + B.substr(j);
    }

    // Find the longest common subsequence of strings A and B
    string lcs (string& A, string& B) {
        int n = A.size(); // length of string A
        int m = B.size(); // length of string B
        vector < vector < string >> dp(n + 1, vector < string > (m + 1, "")); // 2D array to store longest common subsequences

        // For each character in string A and string B
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // If the current characters are the same
                if (A[i] == B[j]) {
                    // Update the longest common subsequence for the current indices to include the current character
                    dp[i + 1][j + 1] = dp[i][j] + A[i];
                } else {
                    // Update the longest common subsequence for the current indices to the longer of the two possible values
                    dp[i + 1][j + 1] = dp[i + 1][j].size() > dp[i][j + 1].size() ?  dp[i + 1][j] : dp[i][j + 1];
                }
            }
        }

        // Return the longest common subsequence
        return dp[n][m];
    }
};