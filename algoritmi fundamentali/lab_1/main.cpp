#include <bits/stdc++.h>

using namespace std;

ifstream f("bfs.in");
ofstream g("bfs.out");

int n, m, x, y, startNode;

void bfs(int start, int n, vector < int >& dist, list < int >* adjList) {
    queue < int > q;
    vector < bool > visited(n+1, false);

    q.push(start);
    visited[start] = true;
    dist[startNode] = 0;

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        for (auto const& adjNode: adjList[firstInQueue]) {
            if (!visited[adjNode]) {
                dist[adjNode] = dist[firstInQueue] + 1;
                q.push(adjNode);
                visited[adjNode] = true;
            }
        }
    }
}

int main() {
    f >> n >> m >> startNode;

    list < int >* adjList;
    vector < int > dist(n+1, -1);

    adjList = new list < int > [n+1];

    for (int i = 0; i < m; ++i) {
        f >> x >> y;
        adjList[x].push_back(y);
    }

    bfs(startNode, n, dist, adjList);

    for (int i = 1; i <= n; ++i) {
        g << dist[i] << " ";
    }
}