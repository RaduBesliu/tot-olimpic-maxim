#include <fstream>
#include <vector>

using namespace std;

ifstream f("johnie.in");
ofstream g("johnie.out");

const int maxVal = 50001;

vector < pair < int, int >> adjList[maxVal];
bool used[100001];
int degree[maxVal];
int start, finish;

vector < int > sol[maxVal];

void euler(int& index, int current) {
    while (!adjList[current].empty()) {
        int node = adjList[current].back().first;
        int index = adjList[current].back().second;

        adjList[current].pop_back();

        if (!used[index]) {
            used[index] = true;
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
    int n, m;
    f >> n >> m;
    for (int i = 1; i <= m; ++i) {
        f >> start >> finish;
        adjList[start].push_back(make_pair(finish, i));
        adjList[finish].push_back(make_pair(start, i));
        ++degree[start];
        ++degree[finish];
    }

    for (int i = 1; i <= n; ++i) {
        if (degree[i] % 2) {
            adjList[i].push_back(make_pair(0, i + m));
            adjList[0].push_back(make_pair(i, i + m));
        }
    }

    int ind = 0;
    euler(ind, 0);

    g << ind - 1 << '\n';
    for (int i = 1; i < ind; ++i) {
        g << sol[i].size() << ' ';
        for (auto const& it: sol[i]) {
            g << it << " ";
        }
        g << '\n';
    }
    return 0;
}