// Time Complexity: O((V * 2^V) * E) ( V = number of nodes, E = number of edges )
class Solution {
public:
    int shortestPathLength(vector < vector < int >>& graph) {
        int n = graph.size();
        queue < tuple < int, int, int >> q; // Queue to store nodes, distance, and bitmask
        set < pair < int, int >> visited; // Set to store visited nodes and their bitmasks

        // If there is only one node in the graph, return 0
        if (n == 1) {
            return 0;
        }

        int all = (1 << n) - 1; // Bitmask representing all nodes visited
        for(int i = 0; i < n; ++i) {
            int bitMask = 1 << i; // Bitmask representing the current node visited
            q.push({i, 0, bitMask}); // Push the current node, distance (0), and bitmask onto the queue
            visited.insert({i, bitMask}); // Mark the current node and bitmask as visited
        }

        while (!q.empty()) {
            tuple < int, int, int > firstInQueue = q.front();
            q.pop();

            auto [currentNode, distance, bitMask] = firstInQueue;
            // For each adjacent node to the current node
            for (auto const& adjNode: graph[currentNode]) {
                int newMask = bitMask | (1 << adjNode); // Update the bitmask to include the adjacent node

                // If the new bitmask represents all nodes visited
                if (newMask == all) {
                    return distance + 1;
                }

                // If the adjacent node and new bitmask have already been visited, skip it
                if (visited.find({adjNode, newMask}) != visited.end()) {
                    continue;
                }

                // Push the adjacent node, distance + 1, and new bitmask onto the queue
                // and mark the adjacent node and new bitmask as visited
                q.push({adjNode, distance + 1, newMask});
                visited.insert({adjNode, newMask});
            }
        }

        // If the queue is empty and no solution is found, return 0
        return 0;
    }
};

//This algorithm is an implementation of breadth-first search (BFS) for finding the shortest path length in a graph that visits all nodes exactly once.
// The graph is represented by an adjacency list stored in the vector "graph", where each element of the vector is a vector of integers representing
// the adjacent nodes of that element.
//First, the algorithm initialize some data structures: a queue to store the current node, distance, and a bitmask representing which nodes have been visited,
// a set to store the visited nodes and their bitmasks, the variable all which is a bitmask representing all nodes visited, and a for loop that pushes
// the starting node, distance (0) and bitmask onto the queue and mark the current node and bitmask as visited.
//Then, the algorithm enters a while loop, where it dequeues a node from the queue and inspects each of its adjacent nodes. For each adjacent node,
// it updates the bitmask to include that node, and checks if the updated bitmask represents all nodes visited, if it does it returns the distance + 1
// which is the length of the shortest path. If the adjacent node and the new bitmask have been visited before, it skips that node, if not it pushes
// the adjacent node, distance + 1, and new bitmask onto the queue and marks the adjacent node and new bitmask as visited. If the queue becomes empty
// and no solution is found, the algorithm returns 0.
//The time complexity of this algorithm is O((V * 2^V) * E) ( V = number of nodes, E = number of edges ). This is due to the fact that the algorithm uses a
// queue to store the nodes and it has to explore all possible combinations of bitmasks. This results in an exponential complexity on the number of nodes.