#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int n, m, start, finish;
list < int >* adjList;
vector < int > dist;
vector < int >* parents;
vector < vector < int > > allPaths;
vector < int > path;
vector < int > intersect;
vector < int > intersect2;

// recursive get path function
void get_path(int end) {
    int current = end;

    if (current == -1) {
        allPaths.push_back(path);
        return;
    }

    for (auto const& parent: parents[current]) {
        path.push_back(current);
        get_path(parent);
        path.pop_back();
    }
}

void bfs(int& s) {
    queue < int > q;
    q.push(s);
    dist[s] = 0;
    parents[s] = {-1};

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        for (auto const& adjVertex: adjList[firstInQueue]) {
            if (dist[adjVertex] > dist[firstInQueue] + 1) {
                dist[adjVertex] = dist[firstInQueue] + 1;
                parents[adjVertex].clear();
                parents[adjVertex].push_back(firstInQueue);
                q.push(adjVertex);
            } else if (dist[adjVertex] == dist[firstInQueue] + 1) {
                parents[adjVertex].push_back(firstInQueue);
            }
        }
    }
}

int main() {
    f >> n >> m >> start >> finish;
    adjList = new list<int>[n + 1];

    for (int i = 0; i < m; ++i) {
        int x, y;
        f >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    dist.resize(n + 1, 2147483647);
    parents = new vector<int>[n + 1];

    bfs(start);

    get_path(finish);

    int allPathsSize = allPaths.size();
    intersect = allPaths[0];
    sort(intersect.begin(), intersect.end());
    for (int i = 1; i < allPathsSize; ++i) {
        intersect2.clear();
        sort(allPaths[i].begin(), allPaths[i].end());
        set_intersection(intersect.begin(), intersect.end(), allPaths[i].begin(), allPaths[i].end(),
                         back_inserter(intersect2));
        intersect = intersect2;

    }

    g << intersect.size() << '\n';
    for (auto const &vertex: intersect) {
        g << vertex << ' ';
    }
}