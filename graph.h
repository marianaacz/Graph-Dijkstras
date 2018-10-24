#ifndef GRAPH
#define GRAPH
#include <cstdlib> //size_t
#include <set> // set
#include <string>

using namespace std;

class graph {
public:
    graph();
    static const int MAX = 20;

    void addVertex(const string& label);
    void addEdge(int source, int target, int cost, int milage);
    void removeEdge(int source, int target);
    int size() const {
        return vertices;
    }
    bool edge(int source, int target) const;
    set<int>neighbors(int vertex) const;
    int mileage(int source, int target);
    int costF(int source, int target);
    int vertex(string label);
    
    void print();
    void shortestPath(string source);
    bool is_allowed_vertex(set<int>verts, int vertex);
    
private:
    bool edges[MAX][MAX];
    string labels[MAX];
    int vertices;
    int cost_edges[MAX][MAX];
    int mileage_edges[MAX][MAX];
};

#endif
