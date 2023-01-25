// We perform Kruksal's algorithm.
// We sort the edges by their weight.
// If the parent of the first node of the edge is different from the parent of the second node of the edge,
// then for each question, we check if the nodes are in the same component.
// If the nodes are in the same component, then we ignore the edge.
// If we can devide the 4 nodes in 2 groups, then we update the question's cost.
// Afterwards, if the parents are different, then we merge the 2 groups.
// Time Complexity: O(n * log(n)) ( n = number of edges )

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

ifstream f("apm2.in");
ofstream g("apm2.out");

int n, m, q;
int x, y, z;

vector < tuple < int, int, int >> edgeList;
vector < pair < int, int >> intrebari;
vector < int > costIntrebare;
vector < int > parent;
vector < int > height;

int getParent (const int& a) {
    if (parent[a] != a) {
        parent[a] = getParent(parent[a]);
    }

    return parent[a];
}

void unionA(int& a, int& b) {
    int firstParent = getParent(a);
    int secondParent = getParent(b);
    if (firstParent != secondParent) {

        if (height[firstParent] > height[secondParent]) {
            parent[secondParent] = firstParent;
        } else {
            parent[firstParent] = secondParent;
            if (height[firstParent] == height[secondParent]) {
                height[firstParent]++;
            }
        }
    }
}

void prim(){
    sort(edgeList.begin(), edgeList.end(), [](const tuple < int, int, int >& a, const tuple < int, int, int >& b) {
        return get < 2 > (a) < get < 2 > (b);
    });
    for (int i = 0; i < m; ++i) {
        int parent1 = getParent(get < 0 > (edgeList[i]));
        int parent2 = getParent(get < 1 > (edgeList[i]));

        if (parent1 != parent2) {
            for (int j = 0; j < q; ++j) {
                if (costIntrebare[j] == -1) {
                    int parent3 = getParent(intrebari[j].first);
                    int parent4 = getParent(intrebari[j].second);

                    if ((parent3 == parent1 && parent2 == parent4) || (parent2 == parent3 && parent1 == parent4)) {
                        costIntrebare[j] = get < 2 > (edgeList[i]) - 1;
                    }
                }
            }

            unionA(parent1, parent2);
        }
    }
}

int main() {
    f >> n >> m >> q;
    costIntrebare.resize(q, -1);
    height.resize(n, 0);

    for (int i = 0; i < n + 1; ++i) {
        parent.push_back(i);
    }

    for (int i = 0; i < m; ++i) {
        f >> x >> y >> z;
        edgeList.emplace_back(make_tuple(x, y, z));
    }

    for (int i = 0; i < q; ++i) {
        f >> x >> y;
        intrebari.emplace_back(make_pair(x, y));
    }

    prim();

    for (auto const& cost: costIntrebare) {
        g << cost << '\n';
    }
}