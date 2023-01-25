// Time Complexity: O(V + E)
// To find all the critical connection edges, we perform a modified DFS.
// We keep track of the level and the min level of each node.
// If the min level of a node is greater than the level of the parent node, then the edge between the parent and the node is a critical connection edge.

class Solution {
public:
    void df(int node, vector < bool >& visited, vector < int >& min_level, vector < int >& level, list < int >* adjList, vector < vector < int > >& crit_connections) {
        visited[node] = true;
        min_level[node] = level[node];
        for (auto const& adjNode: adjList[node]) {
            if (!visited[adjNode]) {
                level[adjNode] = level[node] + 1;
                df(adjNode, visited, min_level, level, adjList, crit_connections);

                min_level[node] = min(min_level[node], min_level[adjNode]);

                if (min_level[adjNode] > level[node]) {
                    crit_connections.push_back({node, adjNode});
                }
            } else {
                if (level[adjNode] < level[node] - 1) {
                    min_level[node] = min(min_level[node], level[adjNode]);
                }
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        list < int >* adjList;
        adjList = new list < int > [n];

        vector < bool > visited(n, 0);
        vector < int > min_level(n, 0);
        vector < int > level(n, 0);
        vector < vector < int > > crit_connections;


        for (auto const& connection: connections) {
            adjList[connection[0]].push_back(connection[1]);
            adjList[connection[1]].push_back(connection[0]);
        }

        df(0, visited, min_level, level, adjList, crit_connections);

        return crit_connections;
    }
};