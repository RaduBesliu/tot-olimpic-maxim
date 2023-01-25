class DisjointSet {
public:
    DisjointSet(int n) {
        for (int node = 0; node <= n; node++) {
            parent.push_back(node);
            rank.push_back(0);
        }
    }

    vector < int > parent;
    vector < int > rank;

    int findParent(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node]);
    }

    void unionSet(int node1, int node2) {
        node1 = findParent(node1);
        node2 = findParent(node2);

        if (node1 == node2)
            return;

        if (rank[node1] < rank[node2])
            swap(node1, node2);

        parent[node2] = node1;
        rank[node1] += rank[node2];
    }

    bool isSameGroup(int node1, int node2) {
        return findParent(node1) == findParent(node2);
    }
};

class Solution {
public:
    vector < bool > distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        for (int i = 0; i < queries.size(); i++)
            queries[i].push_back(i);

        sort(edgeList.begin(), edgeList.end(), [](vector < int >& a, vector < int >& b) { return a[2] < b[2]; });
        sort(queries.begin(), queries.end(), [](vector < int >& a, vector < int >& b) { return a[2] < b[2]; });

        vector < bool > ans(queries.size());
        DisjointSet djs(n);
        int indexEdge = 0;

        for (auto const& query: queries) {
            int node1 = query[0];
            int node2 = query[1];
            int limitLength = query[2];
            int indexQuery = query[3];

            while (indexEdge < edgeList.size() && edgeList[indexEdge][2] < limitLength) {
                int nodeEdge1 = edgeList[indexEdge][0];
                int nodeEdge2 = edgeList[indexEdge][1];
                djs.unionSet(nodeEdge1, nodeEdge2);
                ++indexEdge;
            }

            ans[indexQuery] = djs.isSameGroup(node1, node2);
        }

        return ans;
    }
};