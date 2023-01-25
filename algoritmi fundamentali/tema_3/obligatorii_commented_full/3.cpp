// Time Complexity: O(V * E^2) ( V = number of vertices, E = number of edges )
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Declare input and output files
ifstream f("harta.in");
ofstream g("harta.out");

int n, s, t; // Declare variables n, s, and t

vector < int > parent; // Vector to store the BFS tree
vector < vector < int >> capacity; // 2D vector to store the capacity of each edge
vector < vector < int >> adjNodeList; // 2D vector to store the adjacency list

// Function to perform BFS on the residual graph
bool bfs() {
    vector < bool > visited(t + 1); // Vector to store if a node has been visited during BFS
    queue < int > q; // Queue to store nodes during BFS

    q.push(s); // Push the source node onto the queue
    visited[s] = true; // Mark the source node as visited
    parent[s] = -1; // Set the parent of the source node to -1

    // While the queue is not empty
    while (!q.empty()) {
        int firstInQueue = q.front(); // Get the first element in the queue
        q.pop(); // Remove the first element from the queue

        // For each adjacent node to the current node
        for (auto const& adjNode: adjNodeList[firstInQueue]) {
            // If the adjacent node has not been visited and there is capacity on the edge between the current node and the adjacent node

            if (!visited[adjNode] && capacity[firstInQueue][adjNode]) {
                parent[adjNode] = firstInQueue; // Set the parent of the adjacent node to the current node

                // If the adjacent node is the sink node, return true
                if ( adjNode == t) {
                    return true;
                }

                visited[adjNode] = true; // Mark the adjacent node as visited
                q.push(adjNode); // Push the adjacent node onto the queue
            }
        }
    }

    // Return false if we reach this point, as the sink node has not been found
    return false;
}

// Function to compute the maximum flow using Edmonds-Karp algorithm
int edmondsKarp() {
    int maxFlow = 0; // Initialize the maximum flow to 0

    // While there is a path from the source to the sink in the residual graph
    while (bfs()) {
        int currentFlow = INT_MAX; // Initialize the current flow to the maximum possible value

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

        maxFlow += currentFlow; // Add the current flow to the maximum flow
    }

    return maxFlow; // Return the maximum flow
}


int main() {
    f >> n; // Read the value of n from the input file
    t = 2 * n + 1; // Set the value of t

    adjNodeList.resize(t + 1); // Resize the adjacency list to have t+1 elements
    parent.resize(t + 1); // Resize the parent vector to have t+1 elements
    capacity.resize(t + 1, vector < int >(t + 1)); // Resize the capacity matrix to have t+1 rows and t+1 columns

    for (int i = 1; i <= n; ++i) {
        int x, y;
        f >> x >> y; // Read values x and y from the input file

        adjNodeList[s].push_back(i); // Add an edge from the source to the node with capacity x
        adjNodeList[i].push_back(s); // Add an edge from the node to the source with capacity 0
        capacity[s][i] = x; // Set the capacity of the edge from the source to the node to x

        adjNodeList[n + i].push_back(t); // Add an edge from the node to the sink with capacity y
        adjNodeList[t].push_back(n + i); // Add an edge from the sink to the node with capacity 0
        capacity[n + i][t] = y; // Set the capacity of the edge from the node to the sink to y
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) { // If the nodes are not the same
                adjNodeList[i].push_back(n + j); // Add an edge from node i to node j with capacity 1
                adjNodeList[n + j].push_back(i); // Add an edge from node j to node i with capacity 0
                capacity[i][n + j]=1; // Set the capacity of the edge from node i to node j to 1
            }
        }
    }

    g << edmondsKarp() << '\n'; // Write the maximum flow to the output file
    // For each node in the graph
    for (int i = 1; i <= n; ++i) {
        // For each adjacent node to the current node
        for (auto const& node: adjNodeList[i]) {
            // If the adjacent node is not the source and there is no capacity on the edge between the current node and the adjacent node, and the adjacent node is not the sink
            if (node != s && !capacity[i][node] && node != t) {
                // Write the pair of nodes to the output file
                g << i << " " << node - n << '\n';
            }
        }
    }
}