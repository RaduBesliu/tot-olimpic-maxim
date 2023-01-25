// Time Complexity: O(V + E) ( V = number of vertices, E = number of edges )
class Solution {
public:
    vector < vector < int >> validArrangement(vector < vector <int >>& pairs) {
        int m = pairs.size();

        // The adjacency list is implemented as a stack, because the Euler tour
        // algorithm requires that the edges be processed in a specific order.
        // Specifically, the algorithm needs to process the last edge added
        // to the adjacency list before it processes the earlier edges.

        unordered_map < int, stack < int >> adjMap; // Map to store adjacency lists as stacks
        unordered_map < int, int > indegree;
        unordered_map < int, int > degree;
        vector < vector < int >> answer;

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
    void euler(unordered_map < int, stack < int >>& adjMap, vector < vector < int >>& answer, int current) {
        auto& currentStack = adjMap[current];
        while (!currentStack.empty()) {
            int topItem = currentStack.top();
            currentStack.pop();

            // Recursively compute the Euler tour for the top element
            euler(adjMap, answer, topItem);
            // Add the edge between the current node and the top element to the answer vector
            answer.push_back({current, topItem});
        }
    }
};

//This code defines an implementation of Euler Tour algorithm which is used for finding an Euler cycle on an undirected graph.
//The Euler tour algorithm starts at any vertex in the graph that has a degree greater than 0, and traverses all edges of the graph in such a way that each edge is traversed exactly once.
//The main function validArrangement takes a 2D vector of integers as input, where each pair of integers represent an edge in the graph. The function uses several unordered_map to keep track of the graph's adjacency list, indegree and degree of each vertex respectively.
//The first for-loop creates the adjacency list by adding each vertex in the input pairs to a stack and storing the stack in an unordered_map, keyed by the vertex.
//Then, the function finds the vertex that has a degree of one more than its indegree, this vertex will be the starting point for the Euler tour algorithm. If no such vertex is found, the function takes the first vertex in the adjacency map as the starting point.
//After that, the function calls the euler function, which is a recursive function, passing in the adjacency map, a 2D vector to store the result and the starting vertex as arguments.
//The euler function takes a current node as an argument, and while the stack of the current node is not empty, it pops the top element, calls itself with the popped element as an argument and then pushes the edge between the current node and the popped element to the answer vector.
//Finally, the validArrangement function reverses the answer vector and return it as the result.
//The Time Complexity of this algorithm is O(V + E) because it visits each vertex and each edge once and the space complexity is O(V + E) to store the adjacency list, indegree and degree maps.