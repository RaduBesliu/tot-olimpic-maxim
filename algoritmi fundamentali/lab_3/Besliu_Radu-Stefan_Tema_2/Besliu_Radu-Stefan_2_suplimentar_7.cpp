// To find the cheapest flight, we use Prim's algorithm to find the minimum spanning tree.
// We use a priority queue to store the edges ( min heap ).
// But, the difference is that we also check if the number of stops is less than the maximum number of stops.
// If the number of stops is less than the maximum number of stops, then we add the edge to the MST.
// If the number of stops is equal to the maximum number of stops, then we ignore the edge.
// Finally, we return the distance of the cheapest flight with k stops.
// Time Complexity: O(m * log(n)) ( m = number of edges, n = number of nodes )

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector < pair < int, int >> adjList[n];

        for(auto const& flight: flights){
            adjList[flight[0]].push_back({flight[1],flight[2]});
        }

        priority_queue < tuple < int, int, int >> pq;
        pq.push(make_tuple(0, src, 0));

        vector < int > distance (n + 1, 2147483647);

        distance[src] = 0;

        while(!pq.empty()){
            tuple < int, int, int > firstInQueue = pq.top();
            pq.pop();

            int dist = get < 0 > (firstInQueue);
            int node = get < 1 > (firstInQueue);
            int stops = get < 2 > (firstInQueue);

            for(auto const& adjNode: adjList[node] ){
                if ((dist + adjNode.second) < distance[adjNode.first] && (stops + 1) <= k + 1){
                    distance[adjNode.first] = dist + adjNode.second;
                    pq.push(make_tuple(distance[adjNode.first], adjNode.first, stops + 1));
                }
            }
        }

        return  distance[dst] == 2147483647 ? -1 : distance[dst];
    }
};