// Time Complexity: O(V + E)
// To find all the common vertices in the shortest paths we perform two BF searches.
// The first one is from the source node to all the other nodes.
// The second one is from the destination node to all the other nodes.
// We keep track of the distance from the source node and the distance from the destination node.
// If the sum of the distances is equal to the shortest path, then the node is a common vertex.'

#include <fstream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int n, m;
int x, y;
int start, finish;
int nrCommonVertices;

list < int > *adjList;
vector < int > distStart;
vector < int > distFinish;
vector < int > distFreq;

void bfs (int& start, vector < int >& dist) {
    vector < bool > visited (n + 1, false);
    queue < int > q;

    q.push(start);
    visited[start] = true;

    while (!q.empty ()) {
        int firstInQueue = q.front();
        q.pop();

        for (auto const& adjVertex: adjList[firstInQueue]) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                dist[adjVertex] = dist[firstInQueue] + 1;
                q.push(adjVertex);
            }
        }
    }
}

int main() {
    f >> n >> m;
    f >> start >> finish;

    adjList = new list < int > [n + 1];
    distStart.resize(n + 1);
    distFinish.resize(n + 1);
    distFreq.resize(n);

    for (int i = 0; i < m; ++i) {
        f >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    bfs(start, distStart);
    bfs(finish, distFinish);

    int distStartFinish = distStart[finish];
    vector < int > indexes;

    for (int i = 1; i <= n; ++i) {
        if (distStart[i] + distFinish[i] == distStartFinish) {
            ++distFreq[distStart[i]];
            indexes.push_back(i);
        }
    }

    for (auto const& index: indexes) {
        if (distFreq[distStart[index]] == 1) {
            ++nrCommonVertices;
        }
    }

    g << nrCommonVertices << '\n';

    for (auto const& index: indexes) {
        if (distFreq[distStart[index]] == 1) {
            g << index << ' ';
        }
    }
}