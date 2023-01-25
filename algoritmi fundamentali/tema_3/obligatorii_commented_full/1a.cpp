// Time Complexity: O(V * E^2) ( V = number of vertices, E = number of edges )
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream f("maxflow.in");
ofstream g("maxflow.out");

int n, m;
int capacity[1001][1001]; // Matrix to hold capacities of edges
list < int > *adjList; // Pointer to an array of linked lists to store adjacency lists
vector < int > parent; // Vector to store the BFS tree

// Function to perform BFS on the residual graph
bool bfs() {
    parent.assign(n + 1, 0);
    queue < int > q;

    q.push(1);

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        // If the first element in the queue is the sink node, return true
        if (firstInQueue == n) {
            return true;
        }

        // For each adjacent node to the current node
        for (auto const& adjNode: adjList[firstInQueue]) {
            // Get the capacity of the edge between the current node and the adjacent node
            int currentCapacity = capacity[firstInQueue][adjNode];

            // If the capacity is greater than 0 and the parent of the adjacent node has not been set
            if (currentCapacity > 0 && parent[adjNode] == 0) {
                // Set the parent of the adjacent node to the current node
                parent[adjNode] = firstInQueue;
                // Push the adjacent node onto the queue
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

    g << edmondsKarp() << '\n';
}