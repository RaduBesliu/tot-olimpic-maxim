#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("johnie.in");
ofstream g("johnie.out");

int n, m;
vector < vector < pair < int, int >>> adjList;
vector < bool > used_side;
int start, finish;

vector < vector < int >> sol;
vector < int > grad;

void euler (int& index, int current) {
    while (!adjList[current].empty()) {
        int node = adjList[current].back().first;
        int i = adjList[current].back().second;

        adjList[current].pop_back();

        if (!used_side[i]) {
            used_side[i] = true;
            euler(index, node);
        }
    }

    if (!current) {
        ++index;
    } else {
        sol[index].push_back(current);
    }
}

int main() {
    int ind;

    f >> n >> m;
    adjList.resize(n + 1);
    sol.resize(n + 1);
    grad.resize(n + 1);
    used_side.resize(m + 1);

    for (int i = 1; i <= m; ++i) {
        f >> start >> finish;
        adjList[start].push_back({finish, i});
        adjList[finish].push_back({start, i});
        ++grad[start];
        ++grad[finish];
    }

    for (int i = 1; i <= n; ++i) {
        if (grad[i] % 2) {
            adjList[i].push_back(make_pair(0, i + m));
            adjList[0].push_back(make_pair(i, i + m));
        }
    }

    euler(ind, 0);

    g << ind - 1 << '\n';
    for (int i = 1; i < ind; ++i) {
        g << sol[i].size() << " ";
        for (auto const& it: sol[i]) {
            g << it << " ";
        }
        g << '\n';
    }
}