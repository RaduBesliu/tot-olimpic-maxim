// Time Complexity: O(n * m)
// To find the largest island, we iterate through the matrix.
// If the cell is visited, or it is 0, we skip it.
// Otherwise, we add it to the queue and start a BFS.
// The BFS will visit all the cells that are part of the island.
// We keep track of the number of cells visited.
// If the number of cells visited is larger than the current largest island, we update the largest island.

class Solution {
public:
    bool inBounds(int& i, int& j, int& m, int& n) {
        return i >= 0 && i < m && j >= 0 && j < n;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector < int > dx = {0, 1, 0, -1};
        vector < int > dy = {-1, 0, 1, 0};

        int maxIslandSize = 0;
        vector < vector < bool > > visitedGrid(m, vector < bool > (n));


        queue < pair < int, int > > q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!grid[i][j] || visitedGrid[i][j]) {
                    continue;
                }

                q.push({i, j});
                visitedGrid[i][j] = true;
                int currentIslandSize = 1;

                while (!q.empty()) {
                    pair < int, int > firstInQueue = q.front();
                    q.pop();

                    for (int k = 0; k < 4; ++k) {
                        int newI = firstInQueue.first + dx[k];
                        int newJ = firstInQueue.second + dy[k];

                        if (inBounds(newI, newJ, m, n) && grid[newI][newJ] && !visitedGrid[newI][newJ]) {
                            q.push({newI, newJ});
                            visitedGrid[newI][newJ] = true;
                            ++currentIslandSize;
                        }
                    }
                }

                maxIslandSize = max(maxIslandSize, currentIslandSize);
            }
        }

        return maxIslandSize;
    }
};