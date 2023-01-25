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
vector < bool > bfs() {
    parent.assign(n + 1, 0);
    queue < int > q;

    // Declare a vector of booleans to mark visited nodes
    vector < bool > visited(n + 1, false);

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
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
    int maxFlow = 0;

    // While there is a path from the source to the sink in the residual graph
    // Here we used the true condition, because the bfs() function now returns a vector of booleans
    while (true) {
        // Use BFS to find a path from the source to the sink
        vector < bool > visited = bfs();
        // If no path is found, break out of the loop
        if (!visited[n]) {
            break;
        }

        // For each node in the adjacency list of the sink node
        for (auto const& node: adjList[n]) {
            // If the parent of the node has been set
            if (parent[node]) {
                // Set the parent of the sink node to the current node
                parent[n] = node;

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

                maxFlow += currentFlow;
            }
        }
    }

    // Once the maximum flow has been found, use BFS to determine which nodes are reachable from the source
    vector < bool > visited = bfs();

    g << "Min-cut: " << '\n';
    for (int i = 1; i <= n; i++) {
        for (auto const& adjNode: adjList[i]) {
            // If the current node is reachable from the source and the adjacent node is not, print the edge
            if (visited[i] && !visited[adjNode]) {
                g << i << " " << adjNode << '\n';
            }
        }
    }
    g << '\n';

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

//This is an implementation of the Edmonds-Karp algorithm for computing the maximum flow in a network,
// it is similar to the previous version you asked about but with an additional feature of finding the min-cut,
// which are edges on the last bfs call that separates the nodes that can be reached from the source (S) from those that cannot.
//The algorithm is a variant of the Ford-Fulkerson algorithm and is used to find the maximum flow in a graph, where each
// edge has a capacity, and each node is a vertex. The algorithm repeatedly finds augmenting paths in the residual graph, and at each iteration,
// it increases the flow along the path by the minimum capacity of the edges in the path. The flow is increased until no more augmenting paths can be found.
//The implementation uses an adjacency list to represent the graph, BFS to find augmenting paths and to find min-cut,
// and a vector of booleans to mark visited nodes. The function edmondsKarp() repeatedly calls the bfs() function to find augmenting paths
// and increases the flow along the path by the minimum capacity of the edges in the path. The capacity of each edge is stored in the capacity[i][j]
// array, and the maximum flow is returned by the function.
//The time complexity of the Edmonds-Karp algorithm is O(VE^2), where V is the number of vertices and E is the number of edges in the graph.
// The algorithm performs VE iterations, and each iteration takes O(E) time to find an augmenting path using BFS, resulting in the overall time complexity of O(V*E^2).
//After the maximum flow has been found, the code uses BFS to find the edges that separate the reachable nodes from the source
// (S) and the non-reachable ones. the output of the min-cut is stored in the "maxflow.out" file, with the format : Min-cut: source -> Sink : capacity.