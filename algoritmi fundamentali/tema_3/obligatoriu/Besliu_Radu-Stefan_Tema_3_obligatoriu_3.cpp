// Time Complexity: O(V * E^2) ( V = number of vertices, E = number of edges )
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream f("harta.in");
ofstream g("harta.out");

int n, s, t;

vector < int > parent; // Vector to store the BFS tree
vector < vector < int >> capacity; // 2D vector to store the capacity of each edge
vector < vector < int >> adjNodeList; // 2D vector to store the adjacency list

// Function to perform BFS on the residual graph
bool bfs() {
    vector < bool > visited(t + 1);
    queue < int > q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        // For each adjacent node to the current node
        for (auto const& adjNode: adjNodeList[firstInQueue]) {
            // If the adjacent node has not been visited and there is capacity on the edge between the current node and the adjacent node
            if (!visited[adjNode] && capacity[firstInQueue][adjNode]) {
                // Set the parent of the adjacent node to the current node
                parent[adjNode] = firstInQueue;

                // If the adjacent node is the sink node, return true
                if (adjNode == t) {
                    return true;
                }

                visited[adjNode] = true;
                q.push(adjNode);
            }
        }
    }

    // Return false if we reach this point, as the sink node has not been found
    return false;
}

// Function to compute the maximum flow using Edmonds-Karp algorithm
int edmondsKarp() {
    int maxFlow = 0;

    // While there is a path from the source to the sink in the residual graph
    while (bfs()) {
        int currentFlow = INT_MAX;

        // For each node in the path from the sink to the source
        for (int x = t; x!=s; x = parent[x]) {
            int y = parent[x]; // Get the parent of the current node

            // Find the minimum capacity of the edges in the path
            if (capacity[y][x] < currentFlow) {
                currentFlow = capacity[y][x];
            }
        }

        // For each node in the path from the sink to the source
        for (int x = t; x != s; x = parent[x]) {
            int y = parent[x]; // Get the parent of the current node
            capacity[y][x] -= currentFlow; // Decrease the capacity of the edge between the current node and its parent by the current flow
            capacity[x][y] += currentFlow; // Increase the capacity of the edge between the current node and its parent by the current flow
        }

        maxFlow += currentFlow;
    }

    return maxFlow;
}


int main() {
    f >> n;
    t = 2 * n + 1;

    adjNodeList.resize(t + 1);
    parent.resize(t + 1);
    capacity.resize(t + 1, vector < int >(t + 1));

    for (int i = 1; i <= n; ++i) {
        int x, y;
        f >> x >> y;

        adjNodeList[s].push_back(i); // Add an edge from the source to the node with capacity x
        adjNodeList[i].push_back(s); // Add an edge from the node to the source with capacity 0
        capacity[s][i] = x; // Set the capacity of the edge from the source to the node to x

        adjNodeList[n + i].push_back(t); // Add an edge from the node to the sink with capacity y
        adjNodeList[t].push_back(n + i); // Add an edge from the sink to the node with capacity 0
        capacity[n + i][t] = y; // Set the capacity of the edge from the node to the sink to y
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            // If the nodes are not the same
            if (i != j) {
                adjNodeList[i].push_back(n + j); // Add an edge from node i to node j with capacity 1
                adjNodeList[n + j].push_back(i); // Add an edge from node j to node i with capacity 0
                capacity[i][n + j] = 1; // Set the capacity of the edge from node i to node j to 1
            }
        }
    }

    g << edmondsKarp() << '\n';
    for (int i = 1; i <= n; ++i) {
        for (auto const& node: adjNodeList[i]) {
            // If the adjacent node is not the source and there is no capacity
            // on the edge between the current node and the adjacent node, and the adjacent node is not the sink
            if (node != s && !capacity[i][node] && node != t) {
                // Write the pair of nodes to the output file
                g << i << " " << node - n << '\n';
            }
        }
    }
}

//This is an implementation of the Edmonds-Karp algorithm for finding the maximum flow in a network flow problem.
//The algorithm takes an input file, reads the number of nodes, and creates an adjacency list representation of the graph.
// It also creates a 2D vector to store the capacity of each edge and another vector to store the BFS tree. The source node is set to 1 and the sink node is set to 2 * n + 1.
//A BFS function is used to find augmenting paths in the residual graph. The function also sets the parent node of each visited node.
// If a path from the source to the sink is found, the function returns true. Otherwise, it returns false.
//The main function then calls the edmondsKarp() function which repeatedly finds augmenting paths in the residual graph and updates the flow.
// It starts with an initial flow of 0 and continues to find new paths until there are no more paths.
// At the end of each iteration, the maximum flow is increased by the current flow. Once the loop terminates, the maximum flow is returned.
//The time complexity of this algorithm is O(V * E^2) where V is the number of vertices and E is the number of edges.
// The reason is that in each iteration, the BFS run on a residual graph takes O(V+E) and we can run at most V * E iterations to find the max flow.