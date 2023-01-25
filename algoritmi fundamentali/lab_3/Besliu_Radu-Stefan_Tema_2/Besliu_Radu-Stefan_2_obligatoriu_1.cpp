// For each building, we calculate the nearest distance to a generator.
// Then, we search for the closest building and add up the distances.
// We mark the buildings as visited, so we don't visit them again.
// Print the total distance.
// Time Complexity: O(m^2) ( m = number of buildings )

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

int n, m;
int x, y;

vector < pair < int, int >> blocuri;
vector < pair < int, int >> centrale;
vector < double > distanta;
vector < bool > visited;
double totalCost;

double euclidianDist(pair < int, int >& a, pair < int, int >& b) {
    double x1, y1, x2, y2;
    x1 = a.first;
    y1 = a.second;
    x2 = b.first;
    y2 = b.second;
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    f >> n >> m;
    centrale.resize(n);
    blocuri.resize(m);
    distanta.resize(m);
    visited.resize(m);

    for (int i = 0; i < n; ++i) {
        f >> x >> y;
        centrale[i] = make_pair(x, y);
    }

    for (int i = 0; i < m; ++i) {
        f >> x >> y;
        blocuri[i] = make_pair(x, y);
        distanta[i] = 2147483647;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            distanta[i] = min(distanta[i], euclidianDist(blocuri[i], centrale[j]));
        }
    }

    for (int i = 0; i < m; ++i) {
        double minDist = 2147483647;
        int minIndex = -1;

        for (int j = 0; j < m; ++j) {
            if (distanta[j] < minDist && !visited[j]) {
                minDist = distanta[j];
                minIndex = j;
            }
        }

        totalCost += minDist;
        visited[minIndex] = true;

        for (int j = 0; j < m; ++j) {
            distanta[j] = min(distanta[j], euclidianDist(blocuri[j], blocuri[minIndex]));
        }
    }

    g << fixed << setprecision(6) << totalCost;
}