// Time Complexity : O(V + E) / O(V * logV)
// Sort each adjacency list by the position in the permutation
// Perform DFS from the start node
// If the search order is the same as the permutation, then the graph is a valid topological sort

#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;

vector < int >* adjList;
vector < int > positionInPerm;
vector < bool > visited;
vector < int > searchOrder;
vector < int > perm;

bool myCmp (const int& a, const int& b) {
    return positionInPerm[a] < positionInPerm[b];
}

void dfs (const int& start) {
    searchOrder.push_back(start);
    visited[start] = true;

    for (auto const& adjNode : adjList[start]) {
        if (!visited[adjNode]) {
            dfs(adjNode);
        }
    }
}

int main() {
    cin >> n >> m;

    adjList = new vector < int > [n+1];
    visited.resize(n + 1);
    positionInPerm.resize(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> x;
        perm.push_back(x);
        positionInPerm[x] = i;
    }

    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    for (int i = 1; i <= n; ++i) {
        sort(adjList[i].begin(), adjList[i].end(), myCmp);
    }

    int start = 1;
    dfs(start);
    cout << (searchOrder == perm);
}