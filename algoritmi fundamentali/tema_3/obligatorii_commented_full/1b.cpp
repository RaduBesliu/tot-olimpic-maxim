// Time Complexity: O(V * E^2) ( V = number of vertices, E = number of edges )
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Declare input and output files
ifstream f("maxflow.in");
ofstream g("maxflow.out");

// Declare variables
int n, m;
int capacity[1001][1001]; // Matrix to hold capacities of edges
list < int > *adjList; // Pointer to an array of linked lists to store adjacency lists
vector < int > parent; // Vector to store the BFS tree

// Function to perform BFS on the residual graph
vector < bool > bfs() {
    // Assign all values in the parent vector to 0
    parent.assign(n + 1, 0);
    // Declare a queue to store nodes during BFS
    queue < int > q;
    // Declare a vector of booleans to mark visited nodes
    vector<bool> visited(n + 1, false);

    // Push the source node onto the queue and mark it as visited
    q.push(1);
    visited[1] = true;

    // While the queue is not empty
    while (!q.empty()) {
        // Get the first element in the queue
        int firstInQueue = q.front();
        q.pop();

        // If the first element in the queue is the sink node, return the visited vector
        if (firstInQueue == n) {
            return visited;
        }

        // For each adjacent node to the current node
        for (auto const& adjNode: adjList[firstInQueue]) {
            // Get the capacity of the edge between the current node and the adjacent node
            int currentCapacity = capacity[firstInQueue][adjNode];

            // If the capacity is greater than 0 and the parent of the adjacent node has not been set
            if (currentCapacity > 0 && parent[adjNode] == 0 && !visited[adjNode]) {
                // Set the parent of the adjacent node to the current node
                parent[adjNode] = firstInQueue;
                // Push the adjacent node onto the queue
                q.push(adjNode);
                // Mark the adjacent node as visited
                visited[adjNode] = true;
            }
        }
    }

    // Return the visited vector if we reach this point, as the sink node has not been found
    return visited;
}

// Function to compute the maximum flow using Edmonds-Karp algorithm
int edmondsKarp() {
    // Initialize the maximum flow to 0
    int maxFlow = 0;

    // While there is a path from the source to the sink in the residual graph
    while (true) {
        // Use BFS to find a path from the source to the sink
        vector < bool > visited = bfs();
        // If no path is found, break out of the loop
        if (!visited[n]) break;

        // For each node in the adjacency list of the sink node
        for (auto const& node: adjList[n]) {
            // If the parent of the node has been set
            if (parent[node]) {
                // Set the parent of the sink node to the current node
                parent[n] = node;

                // Initialize the current flow to the maximum possible value
                int currentFlow = INT_MAX;

                // For each node in the path from the sink to the source
                for (int i = n; i != 1; i = parent[i]) {
                    // Find the minimum capacity of the edges in the path
                    currentFlow = min(currentFlow, capacity[parent[i]][i]);
                }

                // For each node in the path from the sink to the source
                for (int i = n; i != 1; i = parent[i]) {
                    capacity[parent[i]][i] -= currentFlow;
                    capacity[i][parent[i]] += currentFlow;
                }

                // Add the current flow to the maximum flow
                maxFlow += currentFlow;
            }
        }
    }

    // Once the maximum flow has been found, use BFS to determine which nodes are reachable from the source
    vector<bool> visited = bfs();

    // Print the min-cut
    g << "Min-cut:" << endl;
    for (int i = 1; i <= n; i++) {
        for (auto const& adjNode: adjList[i]) {
            if (visited[i] && !visited[adjNode]) {
                // If the current node is reachable from the source and the adjacent node is not, print the edge
                g << i << " " << adjNode << '\n';
            }
        }
    }

    g << '\n';

    // Return the maximum flow
    return maxFlow;
}

int main() {
    f >> n >> m;
    adjList = new list < int > [n + 1];
    parent.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y, z;
        f >> x >> y >> z;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
        capacity[x][y] = z;
    }

    g << edmondsKarp() << endl;
}