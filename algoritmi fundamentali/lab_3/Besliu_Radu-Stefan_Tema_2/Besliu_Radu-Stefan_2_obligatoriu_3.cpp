// For each set of 2 words, we calculate the Levenshtein distance.
// Then, we sort the array by the distance.
// Afterwards, we search for the first 2 words that have the smallest distance, which are not in the same cluster.
// We join the clusters.
// Then, we calculate the minimum distance between the clusters.
// Time Complexity: O(n^2 * len1 * len2) ( n = number of words, len1 = length of the first word, len2 = length of the second word )

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

ifstream f("cuvinte.in");
ofstream g("cuvinte.out");

int k, n;
string cuvant;
vector < string > cuvinte;
vector < tuple < string, string, int > > cuvintePerechi;
unordered_map < string, int > clusterCuvant;


int levenshteinDistance(const string& cuvant1, const string& cuvant2, int cuvant1Length, int cuvant2Length) {
    if (cuvant1Length == 0) {
        return cuvant2Length;
    }
    if (cuvant2Length == 0) {
        return cuvant1Length;
    }

    if (cuvant1[cuvant1Length - 1] == cuvant2[cuvant2Length - 1]) {
        return levenshteinDistance(cuvant1, cuvant2, cuvant1Length - 1, cuvant2Length - 1);
    }

    return 1 + min(levenshteinDistance(cuvant1, cuvant2, cuvant1Length, cuvant2Length - 1),
                   min(levenshteinDistance(cuvant1, cuvant2, cuvant1Length - 1, cuvant2Length),
                       levenshteinDistance(cuvant1, cuvant2, cuvant1Length - 1, cuvant2Length - 1)));
}

int main() {
    cin >> k;
    while (f >> cuvant) {
        cuvinte.push_back(cuvant);
        ++n;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int levDist = levenshteinDistance(cuvinte[i], cuvinte[j], cuvinte[i].length(), cuvinte[j].length());
            cuvintePerechi.emplace_back(make_tuple(cuvinte[i], cuvinte[j], levDist));
        }
    }

    sort(cuvintePerechi.begin(), cuvintePerechi.end(), [](const tuple < string, string, int >& a, const tuple < string, string, int >& b) {
        return get < 2 > (a) < get < 2 > (b);
    });

    // assign each word to a cluster
    for (int i = 1; i <= cuvinte.size(); ++i) {
        clusterCuvant[cuvinte[i-1]] = i;
    }

    for (int i = 1; i <= n - k; ++i) {
        int j = 0;
        while (clusterCuvant[get < 0 > (cuvintePerechi[j])] == clusterCuvant[get < 1 > (cuvintePerechi[j])]) {
            ++j;
        }

        int cluster1 = clusterCuvant[get < 0 > (cuvintePerechi[j])];
        int cluster2 = clusterCuvant[get < 1 > (cuvintePerechi[j])];
        int minCluster = min(cluster1, cluster2);
        for (auto& cuv: clusterCuvant) {
            if (cuv.second == cluster1 || cuv.second == cluster2) {
                cuv.second = minCluster;
            }
        }
    }

    int minDif = 2147483647;
    for (auto const& cluster1: clusterCuvant) {
        for (auto const& cluster2: clusterCuvant) {
            if (cluster1.second != cluster2.second) {
                int dif = levenshteinDistance(cluster1.first, cluster2.first, cluster1.first.length(), cluster2.first.length());
                if (dif < minDif) {
                    minDif = dif;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        bool hasWord = false;
        for (auto const& cuv: clusterCuvant) {
            if (cuv.second == i) {
                g << cuv.first << " ";
                hasWord = true;
            }
        }
        if (hasWord) {
            g << '\n';
        }
    }
    g << minDif;
}