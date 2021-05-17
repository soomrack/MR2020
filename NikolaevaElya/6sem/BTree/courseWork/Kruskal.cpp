#include <iostream>
#include <cstdlib> // for qsort 
#include <chrono>
using namespace std;
 
// a structure to represent a weighted edge in graph
class Edge {
public:
    int src, end, weight;
};
 
// a structure to represent a connected, undirected and weighted graph
class Graph {
public:
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is an array of edges.
    // Since the graph is undirected, the edge  
    // from src to end is also edge from end to src. 
    // Both are counted as 1 edge here.
    Edge* edge;
};
 
// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
 
    graph->edge = new Edge[E];
 
    return graph;
}
 
// A structure to represent a subset for Union-find
class subset {
public:
    int parent;
    int rank;
};
 
// A function to find set of an element i (uses path compression technique)
int find(subset subsets[], int i) {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}
 
// A function that does Union of two sets of x and y (uses Union by rank)
void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    }  
    // If ranks are same, then make one as root and increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}
 
// The main function to construct Minimum Spanning Tree
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V]; // This will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 
    // Step 1: Sort all the edges in non-decreasing order of their weight. 
    // If we are not allowed to change the given graph, 
    // we can create a copy of array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);
 
    // Allocate memory for creating V subsets
    subset* subsets = new subset[(V * sizeof(subset))];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.end);
 
        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the
    // built MST
    cout << "Following are the edges in the constructed "
            "MST\n";
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        cout << result[i].src << " -- " << result[i].end << " == " << result[i].weight << endl;
        minimumCost = minimumCost + result[i].weight;
    }
    // return;
    cout << "Minimum Cost Spanning Tree: " << minimumCost << endl;
}
 

int main() {

    int V = 3000; // Number of vertices in graph
    int E = 6000; // Number of edges in graph
    Graph* graph = createGraph(V, E);
    for (int i = 0; (i+1) <= E; i++) {
        graph->edge[i].src = rand() % V;
        graph->edge[i].end = rand() % V;
        graph->edge[i].weight = rand() % 100;
    }
    
    auto start = chrono::high_resolution_clock::now();

    KruskalMST(graph);// Function call

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = (end - start)*1000; //ms
    cout << "Duration is " << duration.count() << "ms"<< endl;
    return 0;
}
