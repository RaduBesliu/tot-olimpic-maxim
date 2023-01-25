// Time Complexity: O(V + E)
// Use Tarjan's algorithm to find the strongly connected components of a directed graph

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

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

int main() {
    f >> verticesNumber >> edgesNumber;

    adjList = new list < int > [verticesNumber + 1];
    for (int i = 0; i < edgesNumber; ++i) {
        f >> x >> y;
        adjList[x].push_back(y);
    }

    stack < int > s;
    vector < int > vertexIndex(verticesNumber + 1, -1);
    vector < bool > vertexOnStack(verticesNumber + 1, false);
    vector < int > lowLink(verticesNumber + 1, -1);

    for (int vertex = 1; vertex <= verticesNumber; ++vertex) {
        if (vertexIndex[vertex] == -1) {
            scc(vertex, vertexIndex, lowLink, s, vertexOnStack);
        }
    }

    g << allScc.size() << '\n';
    for (auto const& scc: allScc) {
        for (auto const& vertex: scc) {
            g << vertex << " ";
        }
        g << '\n';
    }
}