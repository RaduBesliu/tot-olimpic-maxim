// Time Complexity: O((V * 2^V) * E) ( V = number of nodes, E = number of edges )
class Solution {
public:
    int shortestPathLength(vector < vector < int >>& graph) {
        int n = graph.size(); // Number of nodes in the graph
        queue < tuple < int, int, int >> q; // Queue to store nodes, distance, and bitmask
        set < pair < int, int >> visited; // Set to store visited nodes and their bitmasks
        // If there is only one node in the graph, return 0
        if(n == 1) {
            return 0;
        }

        int all = (1 << n) - 1; // Bitmask representing all nodes visited
        // For each node in the graph
        for(int i = 0; i < n; ++i) {
            int bitMask = 1 << i; // Bitmask representing the current node visited
            q.push({i, 0, bitMask}); // Push the current node, distance (0), and bitmask onto the queue
            visited.insert({i, bitMask}); // Mark the current node and bitmask as visited
        }

        // While the queue is not empty
        while (!q.empty()) {
            tuple < int, int, int > firstInQueue = q.front(); // Get the first element in the queue
            q.pop(); // Remove the first element from the queue

            // Destructure the tuple into individual variables
            auto [currentNode, distance, bitMask] = firstInQueue;
            // For each adjacent node to the current node
            for (auto const& adjNode: graph[currentNode]) {
                int newMask = bitMask | (1 << adjNode); // Update the bitmask to include the adjacent node

                // If the new bitmask represents all nodes visited
                if (newMask == all) {
                    return distance + 1; // Return the distance + 1
                }

                // If the adjacent node and new bitmask have already been visited, skip it
                if (visited.find({adjNode, newMask}) != visited.end()) {
                    continue;
                }

                // Push the adjacent node, distance + 1, and new bitmask onto the queue
                q.push({adjNode, distance + 1, newMask});
                // Mark the adjacent node and new bitmask as visited
                visited.insert({adjNode, newMask});
            }
        }

        // If the queue is empty and no solution is found, return 0
        return 0;
    }
};
