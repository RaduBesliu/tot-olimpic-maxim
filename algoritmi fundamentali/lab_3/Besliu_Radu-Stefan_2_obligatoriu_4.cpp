// We perform Dijkstra's algorithm using a priority queue.
// But, instead of searching for the minimum distance, we search for the maximum distance.
// If the node is not in the priority queue, then we add it.
// If the node is in the priority queue, then we update its distance.
// Time Complexity: O(m * log(n)) ( m = number of edges, n = number of nodes )

class Solution {
public:
    void dijkstra(int n, vector < double >& distance, int& start, int& end, list < pair < double, int > >* adjList) {
        priority_queue < pair < double, int >, vector < pair < double, int >>> pq;
        vector < int > previous(n);
        vector < bool > inPQ(n, false);

        distance[start] = 1;
        pq.push({distance[start], start});
        inPQ[start] = true;

        for (int i = 0; i < n; ++i) {
            if (i != start) {
                previous[i] = -1;
            }
        }

        while (!pq.empty()) {
            pair < int, int > firstInQueue = pq.top();
            pq.pop();
            inPQ[firstInQueue.second] = false;

            for (auto const& adjNode: adjList[firstInQueue.second]) {
                double dist = distance[firstInQueue.second] * adjNode.first;
                if (dist > distance[adjNode.second]) {
                    distance[adjNode.second] = dist;
                    previous[adjNode.second] = firstInQueue.second;
                    if (!inPQ[adjNode.second]) {
                        inPQ[adjNode.second] = true;
                        pq.push({distance[adjNode.second], adjNode.second});
                    }
                }
            }
        }
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        list < pair < double, int >>* adjList = new list < pair < double, int >> [n];

        int m = edges.size();
        for (int i = 0; i < m; ++i) {
            adjList[edges[i][0]].push_back({succProb[i], edges[i][1]});
            adjList[edges[i][1]].push_back({succProb[i], edges[i][0]});
        }

        vector < double > distance(n, -1);

        dijkstra(n, distance, start, end, adjList);

        return distance[end] == -1 ? 0 : 1e-5 * round(1e5 * distance[end]);
    }
};