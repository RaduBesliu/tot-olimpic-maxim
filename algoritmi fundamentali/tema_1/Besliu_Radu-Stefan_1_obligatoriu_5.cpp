// Time Complexity: O(K * (V + E)) (K = number of control points)
// Solution: Perform a BFS for every control point and update distances accordingly.
// BFS works here because the graph is unweighted.

// Modifications: On the first input line read the number of control points

#include <bits/stdc++.h>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int x, y;
int verticesNumber, edgesNumber, controlPointsNumber;

list < int > *adjList;
vector < int > controlPoints;

void updateMinDistance(int& n, const int& controlPoint, vector < int >& minDistance, list < int >* adjList) {
    queue < int > q;
    vector < int > localDistance(n + 1, -1);

    q.push(controlPoint);
    localDistance[controlPoint] = 0;

    while(!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        for (auto const& adjVertex: adjList[firstInQueue]) {
            if (localDistance[adjVertex] == -1) {
                localDistance[adjVertex] = localDistance[firstInQueue] + 1;
                q.push(adjVertex);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (minDistance[i] == -1) {
            minDistance[i] = localDistance[i];
        } else {
            minDistance[i] = localDistance[i] == -1 ? minDistance[i] : min(minDistance[i], localDistance[i]);
        }
    }
}

int main() {
    f >> verticesNumber >> edgesNumber >> controlPointsNumber;

    vector < int > minDistance(verticesNumber + 1, -1);

    adjList = new list < int > [verticesNumber + 1];
    for (int i = 0; i < edgesNumber; ++i) {
        f >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    for (int i = 0; i < controlPointsNumber; ++i) {
        f >> x;
        controlPoints.push_back(x);
        minDistance[x] = 0;
    }

    for (auto const& controlPoint: controlPoints) {
        updateMinDistance(verticesNumber, controlPoint, minDistance, adjList);
    }

    for (int i = 1; i <= verticesNumber; ++i) {
        g << minDistance[i] << " ";
    }
}