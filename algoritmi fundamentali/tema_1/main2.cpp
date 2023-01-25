#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

ifstream f("ctc.in");
ofstream g("ctc.out");

int x, y;
int verticesNumber, edgesNumber, currentIndex = 1;

list < int > *adjList;
vector < vector < int > > allScc;

void scc(int& vertex, vector < int >& vertexIndex, vector < int >& lowLink, stack < int >& s, vector < bool >& vertexOnStack) {
    vertexIndex[vertex] = currentIndex;
    lowLink[vertex] = currentIndex;
    ++currentIndex;

    s.push(vertex);
    vertexOnStack[vertex] = true;

    for (auto& adjVertex: adjList[vertex]) {
        if (vertexIndex[adjVertex] == -1) {
            scc(adjVertex, vertexIndex, lowLink, s, vertexOnStack);
            lowLink[vertex] = min(lowLink[vertex], lowLink[adjVertex]);
        } else if (vertexOnStack[adjVertex]) {
            lowLink[vertex] = min(lowLink[vertex], vertexIndex[adjVertex]);
        }
    }

    vector < int > newScc;
    if (lowLink[vertex] == vertexIndex[vertex]) {
        int vertexToPop;
        do {
            vertexToPop = s.top();
            s.pop();
            newScc.push_back(vertexToPop);
            vertexOnStack[vertexToPop] = false;
        } while(vertexToPop != vertex);

        allScc.push_back(newScc);
    }
}

vector < int > topologicalSort(int& numCourses, list < int >* adjList, vector < int > indegree) {
    queue < int > q;
    vector < int > topologicalArray;

    for (int i = 0; i < numCourses; ++i) {
        if (!indegree[i]) {
            q.push(i);
            topologicalArray.push_back(i);
        }
    }

    while(!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        for (auto const& adjVert: adjList[firstInQueue]) {
            if (!(--indegree[adjVert])) {
                q.push(adjVert);
                topologicalArray.push_back(adjVert);
            }
        }
    }

    if (topologicalArray.size() == numCourses) {
        return topologicalArray;
    }

    return {};
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    list < int >* adjList;
    adjList = new list < int > [numCourses + 1];
    vector < int > indegree(numCourses + 1, 0);
    stack < int > s;
    vector < int > vertexIndex(numCourses + 1, -1);
    vector < bool > vertexOnStack(numCourses + 1, false);
    vector < int > lowLink(numCourses + 1, -1);

    for (auto const& edge: prerequisites) {
        adjList[edge[1]].push_back(edge[0]);
        ++indegree[edge[0]];
    }

    if (topologicalSort(numCourses, adjList, indegree).empty()) {
        for (int vertex = 1; vertex <= verticesNumber; ++vertex) {
            if (vertexIndex[vertex] == -1) {
                scc(vertex, vertexIndex, lowLink, s, vertexOnStack);
            }
        }

        for (auto const& scc: allScc) {
            for (auto const& vertex: scc) {
                g << vertex << " ";
            }
            g << '\n';
        }
    } else {
        return {};
    }
}