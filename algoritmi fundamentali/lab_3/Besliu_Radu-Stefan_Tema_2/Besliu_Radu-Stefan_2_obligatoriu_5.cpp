// We perform Dijkstra's algorithm using a priority queue and keep track of the closest fort.
// If the distance to the node is smaller, we push the node in the priority queue, update the distance and the closest fort.
// Otherwise, if the distances are equal, then we take the minimum of the two and assign it to the closest fort.
// Time Complexity: O(m * log(n)) ( m = number of edges, n = number of nodes )

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

const int INF = 2147483647;

vector < int > closestFort, dist;
vector < pair < int, int >>* adjList;
priority_queue < pair < int, int >, vector < pair < int, int >>, greater <>> pq;

int n, m, k;
int x, y, z;

void dijkstra() {
    while(!pq.empty()){
        int firstInQueue = pq.top().second;
        pq.pop();

        for(auto const& adjNode: adjList[firstInQueue]){
            if (dist[firstInQueue] + adjNode.second < dist[adjNode.first]) {
                dist[adjNode.first] = dist[firstInQueue] + adjNode.second;
                pq.push({dist[adjNode.first], adjNode.first});
                closestFort[adjNode.first] = closestFort[firstInQueue];
            }
            else if (dist[firstInQueue] + adjNode.second == dist[adjNode.first]) {
                closestFort[adjNode.first] = min(closestFort[adjNode.first], closestFort[firstInQueue]);
            }
        }
    }
}

int main() {

    f >> n >> m >> k;
    closestFort.resize(n + 1);
    dist.resize(n + 1, INF);
    adjList = new vector < pair < int, int >> [n + 1];

    for(int i = 0; i < k; ++i) {
        f >> x;
        closestFort[x] = x;
        pq.push({0, x});
        dist[x] = 0;
    }
    for(int i = 0; i < m; ++i) {
        f >> x >> y >> z;
        adjList[x].emplace_back(make_pair(y, z));
        adjList[y].emplace_back(make_pair(x, z));
    }

    dijkstra();

    for(int i = 1; i <= n; ++i) {
        if (closestFort[i] == i) {
            g << 0 << " ";
        } else {
            g << closestFort[i] << " ";
        }
    }
}