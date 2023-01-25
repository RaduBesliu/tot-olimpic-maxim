// We perform a topological sort.
// Then, for each node in the topological sort, we initialize the sum with the value of the node.
// Then for each node we check if it has a parent.
// If it has a parent, we add the biggest sum of the parent to the sum of the current node.
// Time Complexity: O(n^2) ( n = number of nodes )

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <limits.h>

using namespace std;

ifstream f("easygraph.in");
ofstream g("easygraph.out");

int n, t, m;
int x, y;
long long maxSum = 0;

void topologicalSort(vector < int >& indegree, list < int >* adjList, vector < int >& topologicalOrder) {
    queue < int > q;
    topologicalOrder.clear();

    for (int i = 1; i <= n; ++i) {
        if (!indegree[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        topologicalOrder.push_back(firstInQueue);

        for (auto const& adjNode: adjList[firstInQueue]) {
            if (!(--indegree[adjNode])) {
                q.push(adjNode);
            }
        }
    }
}

int main() {
    f >> t;
    for (int k = 0; k < t; ++k) {
        f >> n >> m;

        vector < long long > val(n + 1);
        vector < int > indegree(n + 1);
        vector < int > topologicalOrder;
        vector < long long > sums(n + 1);
        list < int > adjList[n + 1];
        list < int > parents[n + 1];

        for (int i = 1; i <= n; ++i) {
            f >> val[i];
        }

        for (int i = 0; i < m; ++i) {
            f >> x >> y;
            adjList[x].push_back(y);
            parents[y].push_back(x);
            ++indegree[y];
        }

        topologicalSort(indegree, adjList, topologicalOrder);

        for (auto const& node: topologicalOrder) {
            sums[node] = val[node];
            for (auto const& parent: parents[node]) {
                sums[node] = max(sums[node], sums[parent] + val[node]);
            }
        }

        maxSum = LONG_LONG_MIN;
        for (int i = 1; i <= n; ++i) {
            maxSum = max(maxSum, sums[i]);
        }

        g << maxSum << '\n';
    }
}