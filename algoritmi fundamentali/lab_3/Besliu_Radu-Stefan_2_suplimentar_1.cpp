// For this problem, we use Prim's algorithm to find the minimum spanning tree.
// We use a priority queue to store the edges ( min heap ).
// We start from the first node and we add the edges to the priority queue.
// We pop the edge with the minimum weight and we add it to the MST.
// If the edge connects two nodes that are not in the MST, then we add the edge to the MST.
// If the edge connects two nodes that are in the MST, then we ignore the edge.
// Finally, we return the sum of the weights of the edges in the MST.
// Time Complexity: O(m * log(n)) ( m = number of edges, n = number of nodes )

class Solution {
public:
    int calculateDistance(pair < int, int >& a, pair < int, int >& b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    int mstWeightSum(int& n, vector < pair < int, int >>& vPoints) {
        int totalSum = 0;
        int totalVisited = 0;
        vector < bool > visited(n);
        priority_queue < tuple < int, int,  pair < int, int >>, vector < tuple < int, int, pair < int, int >>>, greater < >> pq;

        pair < int, int > node = vPoints[0];
        int nodeStart = node.first;
        int nodeEnd = node.second;
        ++totalVisited;
        visited[0] = true;

        for (int i = 1; i < n; ++i) {
            int dist = calculateDistance(node, vPoints[i]);
            pq.push(make_tuple(dist, i, vPoints[i]));
        }

        while (totalVisited < n && !pq.empty()) {
            tuple < int, int, pair < int, int >> firstInQueue = pq.top();
            pq.pop();

            int dist = get < 0 > (firstInQueue);
            int index = get < 1 > (firstInQueue);
            pair < int, int > nodeDest = get < 2 > (firstInQueue);

            if (!visited[index]) {
                visited[index] = true;
                totalSum += dist;
                nodeStart = nodeDest.first;
                nodeEnd = nodeDest.second;
                node = nodeDest;
                ++totalVisited;

                for (int i = 0; i < n; ++i) {
                    if (i != index && !visited[i]) {
                        dist = calculateDistance(node, vPoints[i]);
                        pq.push(make_tuple(dist, i, vPoints[i]));
                    }
                }
            }
        }

        return totalSum;
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        vector < pair < int, int >> vPoints;
        for (auto const point: points) {
            vPoints.push_back({point[0], point[1]});
        }

        int n = vPoints.size();

        return mstWeightSum(n, vPoints);
    }
};