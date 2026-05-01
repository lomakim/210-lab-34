// COMSC210| Lab 34 | Loma Kim
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm> // For sorting/reversing neighbors to match specific traversal order

using namespace std;

// Updated SIZE to 9 to accommodate nodes 0 through 8
const int SIZE = 9; 

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
private:
    void DFS_recursive(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        // To match the specific output (0 2 8...), we process neighbors 
        // in the order they appear in your list (starting with node 2)
        for (int i = adjList[v].size() - 1; i >= 0; i--) {
            int adjNode = adjList[v][i].first;
            if (!visited[adjNode]) {
                DFS_recursive(adjNode, visited);
            }
        }
    }

public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // Adding edges to match the adjacency list provided
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void performDFS(int startNode) {
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << startNode << ":" << endl;
        DFS_recursive(startNode, visited);
        cout << endl;
    }

    void performBFS(int startNode) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS starting from vertex " << startNode << ":" << endl;

        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";
            q.pop();

            for (Pair neighbor : adjList[v]) {
                int adjNode = neighbor.first;
                if (!visited[adjNode]) {
                    visited[adjNode] = true;
                    q.push(adjNode);
                }
            }
        }
        cout << endl;
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

int main() {
    // Edges defined to match your specific adjacency list output
    vector<Edge> edges = {
        {0,1,8}, {0,2,21},
        {1,2,6}, {1,3,5}, {1,4,4},
        {2,7,11}, {2,8,8},
        {3,4,9},
        {5,6,10}, {5,7,15}, {5,8,5},
        {6,7,3}, {6,8,7}
    };

    Graph graph(edges);
    graph.printGraph();

    // Call traversals to match requested output[cite: 1]
    graph.performDFS(0);
    graph.performBFS(0);

    return 0;
}