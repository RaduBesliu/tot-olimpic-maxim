// a
// Time Complexity: O(V + E)
// Solution: We can solve this problem using Khan's Algorithm ( BFS variant ). Keep an array of indegrees of every single vertex, then add
// to the queue the ones that have no incoming edges. Perform normal BFS search.
// Condition to add to the queue: indegree[vertex] - 1 == 0 ( has no more requirements )

class Solution {
public:
    vector < int > topologicalSort(int& numCourses, list < int >* adjList, vector < int > indegree) {
        queue < int > q;
        vector < int > topologicalArray;

        for (int i = 0; i < numCourses; ++i) {
            if (!indegree[i]) {
                q.push(i);
                topologicalArray.push_back(i);
            }
        }

        while(!q.empty()) {
            int firstInQueue = q.front();
            q.pop();

            for (auto const& adjVert: adjList[firstInQueue]) {
                if (!(--indegree[adjVert])) {
                    q.push(adjVert);
                    topologicalArray.push_back(adjVert);
                }
            }
        }

        if (topologicalArray.size() == numCourses) {
            return topologicalArray;
        }

        return {};
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        list < int >* adjList;
        adjList = new list < int > [numCourses];
        vector < int > indegree(numCourses, 0);

        for (auto const& edge: prerequisites) {
            adjList[edge[1]].push_back(edge[0]);
            ++indegree[edge[0]];
        }

        return topologicalSort(numCourses, adjList, indegree);
    }
};



// b
// Time Complexity: O(V + E)
// Perform Khan's algorithm on the graph
// If the size of the topological sort is equal to the number of vertices, then there is a topological sort
// Otherwise, there is a cycle in the graph, and we try to find it.

class Solution {
public:
    vector < int > topologicalSort(int& numCourses, list < int >* adjList, vector < int > indegree) {
        queue < int > q;
        vector < int > topologicalArray;

        for (int i = 0; i < numCourses; ++i) {
            if (!indegree[i]) {
                q.push(i);
                topologicalArray.push_back(i);
            }
        }

        while(!q.empty()) {
            int firstInQueue = q.front();
            q.pop();

            for (auto const& adjVert: adjList[firstInQueue]) {
                if (!(--indegree[adjVert])) {
                    q.push(adjVert);
                    topologicalArray.push_back(adjVert);
                }
            }
        }

        if (topologicalArray.size() == numCourses) {
            return topologicalArray;
        }

        return {};
    }

    void DFS_search_circuit(int start, vector < bool >& visited, vector < int >& parent, vector < bool >& fin, vector < int >& circuit, list < int >* adjList) {
        visited[start] = true;
        for (auto const& adjVertex: adjList[start]) {
            if (!visited[adjVertex]) {
                parent[adjVertex] = start;
                DFS_search_circuit(adjVertex, visited, parent, fin, circuit, adjList);
            } else {
                if (!fin[adjVertex]) {
                    int v = start;
                    do {
                        circuit.push_back(v);
                        v = parent[v];
                    } while (v != adjVertex);

                    circuit.push_back(adjVertex);
                    reverse(circuit.begin(), circuit.end());
                    return;
                }
            }
        }
        fin[start] = true;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        list < int >* adjList;
        adjList = new list < int > [numCourses];
        vector < int > indegree(numCourses, 0);
        vector < bool > visited(numCourses, 0);
        vector < int > parent(numCourses, 0);
        vector < bool > fin(numCourses, 0);
        vector < int > circuit;

        for (auto const& edge: prerequisites) {
            adjList[edge[1]].push_back(edge[0]);
            ++indegree[edge[0]];
        }

        if (topologicalSort(numCourses, adjList, indegree).empty()) {
            DFS_search_circuit(1, visited, parent, fin, circuit, adjList);
            return circuit;
        }

        return {};
    }
};