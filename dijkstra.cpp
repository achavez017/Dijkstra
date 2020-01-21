/*
*   A. Chavez
*   dijkstra.cpp
*   12/30/2019
*   
*   Adjacency matrix used to created weighted graph
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std; 

#define INF 1000000
typedef pair<int, int> PAIR;

class Graph 
{ 
    private:
        int vertList;
        int** adjMatrix;
        
    public: 
        Graph(int vertList);  // Constructor 
    
        int minDistance(int dist[], bool shortestPath[]);
        void addEdge(bool undir, int src, int dest, int wt); 
        void Dijkstra(int src, int dest);
        int printPath(int parent[], int j, int dest);
        void printSolution(int dist[], int n, int parent[], int src, int dest);
        
}; 

Graph::Graph(int vertList)
{
    this->vertList = vertList; 
    adjMatrix = new int* [vertList];
    for (int i = 0; i < vertList; i++)
    {
        adjMatrix[i] = new int[vertList];
        for(int j = 0; j < vertList; j++)
            adjMatrix[i][j] = 0;
    }
}

int Graph::minDistance(int dist[], bool shortestPath[]) 
{ 
    // Initialize min value 
    int min = INF, min_index; 
  
    for (int v = 0; v < vertList; v++) 
        if (shortestPath[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
}

void Graph::addEdge(bool undir, int src, int dest, int wt) 
{ 
    adjMatrix[src][dest] = wt;
    if (undir) 
        adjMatrix[dest][src] = wt;
} 

void Graph::Dijkstra(int src, int dest) 
{ 
    int dist[vertList];
    bool shortestPath[vertList];
    int parent[vertList];

    for (int i = 0; i < vertList; i++)
    {
        dist[i] = INF;
        shortestPath[i] = false;
        parent[src] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < vertList - 1; count++)
    {
        int u = minDistance(dist, shortestPath);
        shortestPath[u] = true;

         for (int v = 0; v < vertList; v++) 
            if(!shortestPath[v] && adjMatrix[u][v] && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
    }
    printSolution(dist, vertList, parent, src, dest);
    cout << " - Distance: " << dist[dest] << endl;
    
}

int Graph::printPath(int parent[], int j, int dest) 
{ 
    // Base Case : If j is source 
    if (parent[j] == -1) 
        return 0; 

    printPath(parent, parent[j], dest); 
    
    if (j == dest)
        cout << "[" << j << "]";
    else
        cout << j << ", ";
    
    return 0;
} 

void Graph::printSolution(int dist[], int n, int parent[], int src, int dest) 
{ 
        cout << "[" << src << "], ";
        
        int count = printPath(parent, dest, dest); 
} 

int main()
{
    int src, dst;
    int vertList = 12;
    Graph G(vertList);
    
    G.addEdge(true, 0, 1, 5);
    G.addEdge(false, 0, 2, 2);
    G.addEdge(true, 0, 3, 4);
    G.addEdge(true, 1, 4, 6);
    G.addEdge(true, 1, 5, 4);
    G.addEdge(false, 2, 4, 1);
    G.addEdge(true, 3, 4, 2);
    G.addEdge(true, 3, 6, 1);
    G.addEdge(true, 3, 7, 3);
    G.addEdge(true, 4, 5, 2);
    G.addEdge(true, 4, 7, 2);
    G.addEdge(true, 4, 8, 3);
    G.addEdge(true, 4, 11, 4);
    G.addEdge(true, 5, 8, 1);
    G.addEdge(true, 6, 9, 2);
    G.addEdge(true, 7, 9, 2);
    G.addEdge(true, 7, 10, 1);
    G.addEdge(true, 7, 11, 2);
    G.addEdge(true, 8, 11, 2);
    G.addEdge(true, 9, 10, 2);
    G.addEdge(true, 10, 11, 2);

    cout << "Enter starting location (0-11): ";
    cin >> src;
    cout << "Enter destination (0-11): ";
    cin >> dst;
    G.Dijkstra(src, dst);
    cout << endl;
    return 0;
}
