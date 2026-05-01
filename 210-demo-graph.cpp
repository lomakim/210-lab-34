// COMSC210| Lab 34 | Loma Kim
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int SIZE = 8; 

struct Edge {
    int stationNum;     
    int dest;           
    int numPassengers;  
    string stationName; 
};

typedef pair<int, int> Pair;

class Graph {
private:
    string stationNames[SIZE];

    void DFS_recursive(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << stationNames[v] << " "; 

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
            int u = edge.stationNum;
            int v = edge.dest;
            int passengers = edge.numPassengers;

            stationNames[u] = edge.stationName;

            // Maintain undirected graph logic
            adjList[u].push_back(make_pair(v, passengers));
            adjList[v].push_back(make_pair(u, passengers));
        }
    }

    void performDFS(int startNode) {
        vector<bool> visited(SIZE, false);
        cout << "DFS Subway Route Exploration starting from " << stationNames[startNode] << ":" << endl;
        DFS_recursive(startNode, visited);
        cout << endl;
    }

    void performBFS(int startNode) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Subway Route Exploration starting from " << stationNames[startNode] << ":" << endl;

        while (!q.empty()) {
            int v = q.front();
            cout << stationNames[v] << " "; 
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

    // Updated printGraph to match the multi-line indented format
    void printGraph() {
        cout << "NYC Subway Connectivity (Adjacency List):" << endl;
        cout << "------------------------------------------" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            // Print the primary station name on its own line
            cout << stationNames[i] << endl; 
            for (Pair v : adjList[i]) {
                // Print each connection on a new indented line with the specific arrow and text[cite: 1]
                cout << "    → " << stationNames[v.first] 
                     << " (Passengers waiting for a train: " << v.second << ")" << endl;
            }
        }
    }
};

int main() {
    vector<Edge> subwayEdges = {
        {0, 1, 450, "Grand Central"},
        {1, 2, 600, "Times Square"},
        {2, 3, 300, "Penn Station"},
        {3, 4, 150, "34th St - Herald Sq"},
        {4, 5, 200, "14th St - Union Sq"},
        {5, 6, 500, "Fulton St"},
        {6, 7, 120, "Wall St"},
        {7, 0, 80,  "Bowling Green"} 
    };

    Graph nycSubway(subwayEdges);
    nycSubway.printGraph();

    cout << "\n--- Service Analysis ---" << endl;
    nycSubway.performDFS(0); 
    nycSubway.performBFS(0); 

    return 0;
}