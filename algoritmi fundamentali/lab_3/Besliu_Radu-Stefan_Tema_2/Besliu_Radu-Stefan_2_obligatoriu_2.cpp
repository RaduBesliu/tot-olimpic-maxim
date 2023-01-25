// Initially, we set the parent of each node to itself.
// Then, we read the operation and the 2 nodes.
// If the operation is 1, then we perform the union operation.
// If the operation is 2, we check if the 2 nodes are in the same group and print the result.
// Time Complexity: O(m * log(n)) ( m = number of operations, n = number of nodes )

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("disjoint.in");
ofstream g("disjoint.out");

int n, m;
int x, y, op;

vector < int > parent;

int getRoot(int& a) {
    if (parent[a] == a) {
        return a;
    }

    return getRoot(parent[a]);
}

int main() {
    f >> n >> m;
    parent.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        f >> op >> x >> y;
        if (op == 1) {
            parent[getRoot(y)] = getRoot(x);
        } else {
            if (getRoot(x) == getRoot(y)) {
                g << "DA" << '\n';
            } else {
                g << "NU" << '\n';
            }
        }
    }
}