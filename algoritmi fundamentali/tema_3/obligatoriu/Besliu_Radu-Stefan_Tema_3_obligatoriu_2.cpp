// Time Complexity: O(V * E^2) ( V = number of vertices, E = number of edges )
// Hopcroft-Karp
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

ifstream f("cuplaj.in");
ofstream g("cuplaj.out");

// sizeLeft = number of nodes in the left part of the bipartite graph
// sizeRight = number of nodes in the right part of the bipartite graph
// edges = number of edges in the bipartite graph
int sizeLeft, sizeRight, edges;

// s is the source node and t is the sink node
int s, t;

// inRight[i] is true if the node i from the right part of the bipartite graph has at least one incoming edge
vector < bool > inRight;

// parent[i] is a pair (node, edge index) where node is the node from which node i
// was reached and edge index is the index of the edge in the adjacency list of node
vector < pair < int, int >> parent;

// nodesRight[i] is a pair (node, edge index) for each edge connecting a
// node from the right part of the bipartite graph to the sink node t
vector < pair < int, int >> nodesRight;

// adjList[i] is a list of pairs (node, (capacity, edge index)) for each edge connecting node i to another node
// capacity is the current capacity of the edge and edge index is the index of the edge in the adjacency list of the other node
vector < vector < pair < int, pair < int, int >>>> adjList;

// Create an edge between nodes x and y with capacity 1
void createEdge(int x, int y) {
    // Add an edge from x to y with capacity 1 and edge index adjList[y].size()
    adjList[x].push_back({y, {1,adjList[y].size()}});
    // Add an edge from y to x with capacity 0 and edge index adjList[x].size() - 1
    adjList[y].push_back({x, {0,adjList[x].size() - 1}});

    // If y is the sink node t, add the edge to the list of edges connecting nodes from the right part of the bipartite graph to t
    if (y == t) {
        nodesRight.emplace_back(x, adjList[x].size() - 1);
    }
}

// Breadth-first search to find augmenting paths
bool bfs() {
    vector < bool > visited(t + 1);
    queue < int > q;

    q.push(s);
    visited[s] = true;
    parent[s] = {-1, -1}; // the parent of s is not set

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        // skip the sink node t because we don't want to find a path to it
        if (firstInQueue == t) {
            continue;
        }

        // Consider each outgoing edge of the current node
        int i = 0;

        for (auto const& adjNode: adjList[firstInQueue]) {
            int capacity = adjNode.second.first; // capacity of the current edge
            int node = adjNode.first; // adjacent node

            if (!visited[node] && capacity) {
                // Set the parent of the adjacent node to be the current node and the index of the current edge
                parent[node] = {firstInQueue, i};
                // Mark the adjacent node
                parent[node] = {firstInQueue, i};
                visited[node] = true;
                q.push(node);
            }

            ++i;
        }
    }

    return visited[t];
}

// Compute the maximum flow in the bipartite graph
long long int cuplaj() {
    long long int maxFlow = 0;

    // Repeat as long as there are augmenting paths
    while (bfs()) {
        // For each edge connecting a node from the right part of the bipartite graph to the sink t
        for (auto const& adjNode: nodesRight) {
            int currentFlow = 1;  // the flow along the current augmenting path is 1
            parent[t] = adjNode;  // set the parent of t to be the current node
            int y = t;  // start from the sink t

            // Trace back the path from t to s
            while (parent[y].first != -1) {
                // Find the node and the index of the edge in the adjacency list of the node
                int x = parent[y].first;
                int i = parent[y].second;
                // Update the residual capacity of the edge
                adjList[x][i].second.first = 0;
                // Update the current flow by the residual capacity of the edge
                currentFlow = min(currentFlow, adjList[y][adjList[x][i].second.second].second.first);
                y = x;
            }

            // Update the maximum flow
            maxFlow += currentFlow;

            // Trace back the path from t to s again and update the flow along the edges
            y = t;
            while (parent[y].first != -1) {
                int x = parent[y].first;
                int i = parent[y].second;
                // Update the flow of the edge from x to y
                adjList[x][i].second.first -= currentFlow;
                // Update the flow of the edge from y to x
                adjList[y][adjList[x][i].second.second].second.first += currentFlow;
                y = x;
            }
        }
    }

    return maxFlow;
}

int main() {
    f >> sizeLeft >> sizeRight >> edges;

    t = sizeLeft + sizeRight + 1;
    inRight.resize(sizeRight + 1);
    parent.resize(t + 1);
    adjList.resize(t + 1);

    // Create edges from the source s to the nodes in the left part of the bipartite graph
    for (int i = 1; i <= sizeLeft; ++i) {
        createEdge(s, i);
    }

    // Create edges from the nodes in the right part of the bipartite graph to the sink t
    for (int i = 1; i <= edges; ++i) {
        int x, y;
        f >> x >> y;
        createEdge(x, sizeLeft + y);
        inRight[y] = true;
    }

    // Create edges from the nodes in the left part of the bipartite graph to the nodes in the right part of the bipartite graph
    for (int i = 1; i <= sizeRight; ++i) {
        if (inRight[i]) {
            createEdge(sizeLeft + i, t);
        }
    }

    // Compute the maximum flow
    g << cuplaj() << '\n';
    for (int i = 1; i <= sizeLeft; ++i) {
        // For each node in the left part of the bipartite graph, find the node in the right part of the bipartite graph to which it is connected
        for (auto const &node: adjList[i]) {
            int vertex, capacity;

            vertex = node.first;
            capacity = node.second.first;

            // If the node is in the right part of the bipartite graph and the edge from i to vertex is not in the residual graph
            if (vertex && capacity == 0 && vertex != t) {
                g << i << " " << vertex - sizeLeft << '\n';
            }
        }
    }
}

//This is an implementation of the Maximum Bipartite Matching algorithm also known as Hopcroft–Karp algorithm.
// The algorithm is used to find a maximum cardinality matching of a bipartite graph.
// A matching is a set of edges without common vertices. A maximum cardinality matching is a matching with the maximum possible number of edges.
//This implementation uses a vector of vectors, the adjList to represent the graph's edges and a vector of pairs,
// the parent to represent the BFS tree. The function cuplaj() is used to compute the maximum flow in the bipartite graph.
// The function repeatedly calls the bfs() function to find augmenting paths and increases the flow along the path by the minimum capacity of the edges in the path.
//The createEdge(int x, int y) is used to create edges between nodes x and y with capacity 1 and the bfs() is used to
// find the augmenting paths and to initialize the parent vector. The inRight[i] vector is used to indicate if the node i
// from the right part of the bipartite graph has at least one incoming edge. The nodesRight[i] vector is used to store the
// edges connecting nodes from the right part of the bipartite graph to the sink t.