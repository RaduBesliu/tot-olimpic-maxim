// Time Complexity: O(n * m)
// We can use a few algorithms here, like Lee or Fill
// Visit each cell and it's neighbours, if it's a 1, then it's a part of an island
// We also use an auxiliary matrix to keep track of the visited cells


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