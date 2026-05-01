// COMSC210| Lab 34 | Loma Kim
#include <iostream>
#include <vector>
#include <queue> // Required for BFS
#include <stack> // Required for DFS (if done iteratively)

using namespace std;

const int SIZE = 7; // Number of nodes defined in 210-demo-graph.cpp

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
private:
    // Recursive helper for DFS
    void DFS_recursive(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        for (Pair neighbor : adjList[v]) {
            int adjNode = neighbor.first;
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

            // Undirected graph logic from 210-demo-graph.cpp
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // --- Depth First Search ---
    void performDFS(int startNode) {
        vector<bool> visited(SIZE, false);
        cout << "DFS Traversal (starting at " << startNode << "): ";
        DFS_recursive(startNode, visited);
        cout << endl;
    }

    // --- Breadth First Search ---
    void performBFS(int startNode) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal (starting at " << startNode << "): ";

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
    // Data from 210-demo-graph.cpp
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    Graph graph(edges);
    graph.printGraph();

    cout << "\n--- Search Results ---" << endl;
    graph.performDFS(0);
    graph.performBFS(0);

    return 0;
}