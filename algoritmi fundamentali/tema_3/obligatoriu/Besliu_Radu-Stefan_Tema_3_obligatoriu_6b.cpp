// Time Complexity: O(n * m) ( n = length of word 1, m = length of word 2 )
class Solution {
public:
    string shortestCommonSupersequence(string& A, string& B) {
        int i = 0;
        int j = 0;
        string res = "";

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
            ++i;
            ++j;
        }

        // Add the remaining characters in string A to the result string
        return res + A.substr(i) + B.substr(j);
    }

    // Find the longest common subsequence of strings A and B
    string lcs (string& A, string& B) {
        int n = A.size(); // length of string A
        int m = B.size(); // length of string B
        vector < vector < string >> dp(n + 1, vector < string > (m + 1, ""));

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

//This is an implementation of the shortest common supersequence algorithm using dynamic programming.
// The algorithm finds the longest common subsequence (LCS) of the two input strings A and B and then constructs the shortest common
// supersequence by iterating through the LCS and appending the characters from A and B that come before the next character in the LCS.
//The LCS is calculated using a bottom-up approach of dynamic programming. A 2D dp array is created where each cell dp[i][j] stores the
// longest common subsequence of substrings A[0...i-1] and B[0...j-1]. The algorithm iterates through both strings, comparing each character
// and building the LCS by taking the maximum of two possible values at each step.
//The solution starts by iterating through the characters of the LCS, for each character it finds the next occurrence of that character in
// both A and B, adding the characters between this occurrence and the previous one from both strings to the result string.
// It then adds the remaining characters from both strings A and B that have not yet been added to the result string.
//The time complexity of this algorithm is O(n * m) , where n is the length of word 1 and m is the length of word 2.
// This is because it loops over the two strings of length n and m, and for each combination of the two strings runs a calculation on the LCS which is of O(n * m) as well.