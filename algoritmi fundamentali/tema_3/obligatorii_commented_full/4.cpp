// Time Complexity: O(V + E) ( V = number of vertices, E = number of edges )
class Solution {
public:
    vector < vector < int >> validArrangement(vector < vector <int >>& pairs) {
        int m = pairs.size();

        // The adjacency list is implemented as a stack, because the Euler tour
        // algorithm requires that the edges be processed in a specific order.
        // Specifically, the algorithm needs to process the last edge added
        // to the adjacency list before it processes the earlier edges.

        unordered_map <int, stack < int >> adjMap; // Map to store adjacency lists as stacks
        unordered_map <int, int > indegree; // Map to store indegrees of nodes
        unordered_map <int, int > degree; // Map to store degrees of nodes
        vector < vector <int >> answer; // Vector to store answer

        // Reserve space in maps to avoid rehashing
        adjMap.reserve(m);
        indegree.reserve(m);
        degree.reserve(m);

        // Populate maps with input data
        for (int i = 0; i < m; i++) {
            int x, y;
            x = pairs[i][0];
            y = pairs[i][1];
            indegree[y]++; // Increment indegree of y
            degree[x]++; // Increment degree of x
            adjMap[x].push(y); // Add y to adjacency list of x
        }

        int start = -1;
        // Find the node with a degree of 1 more than its indegree
        for (auto const& pair: adjMap) {
            int node = pair.first;
            if (degree[node] - indegree[node] == 1) {
                start = node;
            }
        }

        // If no such node was found, set the start node to be the first element in the adjacency map
        if (start == -1) {
            start = adjMap.begin()->first;
        }

        // Recursively compute the Euler tour and store the result in the answer vector
        euler(adjMap, answer, start);
        // Reverse the answer vector
        reverse(answer.begin(), answer.end());

        return answer;
    }

    // Recursive function to compute the Euler tour
    void euler(unordered_map <int, stack < int >>& adjMap, vector < vector < int >>& answer, int current) {
        // Get the current node's adjacency list as a stack
        auto& currentStack = adjMap[current];
        // While the stack is not empty
        while (!currentStack.empty()) {
            // Get the top element in the stack
            int topItem = currentStack.top();
            currentStack.pop(); // Pop the top element from the stack

            // Recursively compute the Euler tour for the top element
            euler(adjMap, answer, topItem);
            // Add the edge between the current node and the top element to the answer vector
            answer.push_back({current, topItem});
        }
    }
};