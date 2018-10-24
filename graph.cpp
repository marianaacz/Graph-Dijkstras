#include "graph.h"
#include <cassert>
#include <cstdlib> //size_t
#include <iostream>
#include <stack>
#include <string>
#include <set> // set
#include <stdexcept>
#include <climits>
#include <list>

using namespace std;

const int INFINITY = INT_MAX;

//constructor 
//build the graph by initiating all the cost and mile edges to infinity
graph::graph(){
  vertices = 0;
  for(int i = 0; i < MAX; ++i){
    for(int j = 0; j < MAX; ++j){
      cost_edges[i][j] = INFINITY;
      mileage_edges[i][j] = INFINITY;
      edges[i][j] = false;
    }
  }
}

// Function Name:    addEdge
// Purpose:       assert that the source and target are less than the max and build the adjancency matrix 
// Parameters:      int source, int target, int cost, int mileage
// Returns:      void
// Pre-conditions:   none
// Post-conditions:none
void graph::addEdge(int source, int target, int cost, int mileage) {
    assert(source < MAX); //Assert that source and target are smaller than size
    assert(target < MAX);
    edges[source][target] = true;
    cost_edges[source][target] = cost;
    mileage_edges[source][target] = mileage;
}

// Function Name:    addVertex
// Purpose:       add the vertices to a new variable label
// Parameters:     const string &label
// Returns:      void
// Pre-conditions:   none
// Post-conditions:none
void graph::addVertex(const string &label) {
    labels[vertices++] = label;
}

// Function Name:    edge
// Purpose:       assert source and target are smaller than the size and return the adjancency matrix
// Parameters:    int source, int target
// Returns:      edges[source][target]
// Pre-conditions:   none
// Post-conditions:none
bool graph::edge(int source, int target) const {
    assert(source < size());
    assert(target < size());
    return edges[source][target];
}

// Function Name:    neighbors
// Purpose:       make a set of integers, assert that the vertex is smaller than the size and doo a loop that to insert them
// Parameters:    int vertex
// Returns:      answer
// Pre-conditions:   if edges[vertex][i] then insert answer
// Post-conditions:none
set<int> graph::neighbors(int vertex) const {
    set<int> answer;
    int i;
    assert(vertex < size());
    
    for (i = 0; i < size(); ++i) {
        if (edges[vertex][i]) {
            answer.insert(i);
        }
        return answer;
    }
}

// Function Name:    removeEdge
// Purpose:        assert that source and target are smaller than size and remove edges by making them false
// Parameters:    int source, int target
// Returns:      none (void)
// Pre-conditions:   none
// Post-conditions: none
void graph::removeEdge(int source, int target) {
    assert(source < size());
    assert(target < size());
    edges[source][target] = false;
}

// Function Name:    mileage
// Purpose:        assert that source and target are smaller than size and see if there is a source and a target if not return infinity
// Parameters:    int source, int target
// Returns:      mileage_edges[source][target] or INFINITY
// Pre-conditions:   if the edge has a source and target 
// Post-conditions: none
int graph::mileage(int source, int target) {
    assert(source < size());
    assert(target < size());
    if (edge(source, target)) {
        return mileage_edges[source][target];
    } else {
        return INFINITY;
    }
}

// Function Name:    costF
// Purpose:        assert that source and target are smaller than size and see if there is a source and a target if not return infinity
// Parameters:    int source, int target
// Returns:      cost_edges[source][target] or INFINITY
// Pre-conditions:   if the edge has a source and target 
// Post-conditions: none
int graph::costF(int source, int target) {
    assert(source < size());
    assert(target < size());
    if (edge(source, target)) {
        return cost_edges[source][target];
    } else {
        return INFINITY;
    }
}

// Function Name:    vertex
// Purpose:        loop through and see if labels at i is the same as label then rerurn i 
// Parameters:   string label
// Returns:      int i 
// Pre-conditions:   if labels at i is the same as label then rerurn i 
// Post-conditions: none
int graph::vertex(string label) {
    for (int i = 0; i < MAX; ++i) {
        if (labels[i] == label) {
            return i;
        }
    }
    return INFINITY;
}

// Function Name:    print
// Purpose:        i made this function but i don't really use it, but the purpose was to print all the flights again in alphabetical order and it helped me see what I was doing with the code and if it was working 
// Parameters:   none
// Returns:      none void 
// Pre-conditions:   order it alphabetically -> see which letter is less than the next one 
// Post-conditions: none
void graph::print() { // print all edges
    // alphabetic
    string alpha_labels[MAX] = labels;
    int num_labels[MAX];
    for (int i = 0; i < size(); ++i) {
        num_labels[i] = i;
    }
    for (int x = 0; x < size(); ++x) {
        for (int y = 0; y < size(); ++y) {
            if (alpha_labels[x] < alpha_labels[y]) {
                string temp = alpha_labels[x];
                alpha_labels[x] = alpha_labels[y];
                alpha_labels[y] = temp;
                int temp2 = num_labels[x];
                num_labels[x] = num_labels[y];
                num_labels[y] = temp2;
            }
        }
    }
    
    for (int i = 0; i < size(); ++i) {
        for (int j = 0; j < size(); ++j) {
            if (edge(num_labels[i], num_labels[j])) {
                cout << alpha_labels[i] << " " << alpha_labels[j] << " "
                << mileage_edges[num_labels[i]][num_labels[j]] << " "
                << cost_edges[num_labels[i]][num_labels[j]] << endl;
            }
        }
    }
}

// Function Name:    shortestPath
// Purpose:      find the shortest path by cost of all the flights 
// Parameters:   string source
// Returns:      none
// Pre-conditions:   yes but too many to put here 
// Post-conditions: none
void graph::shortestPath(string source) { // fills matrix up
  int start = vertex(source);
  int *d = new int[size()]; //dest
  int *p = new int[size()]; //path
  int n = size();
  set<int> rs; //reached source 
  set<int> L; //list of all vertices 


  //DIJKSTRA'S ALGRORITHM
  
  for(int i = 0; i < n; i++){
    d[i] = cost_edges[start][i];
    if (edges[start][i]){
      p[i] = start;
      L.insert(i);
    }
    else {
      p[i] = -1;
    } 
  }
  rs.insert(start);
  
  while(L.empty() == false){
    int minVal = INFINITY;
    int i;
    
    for(int v : L){
      if (d[v] < minVal){
        minVal = d[v];
        i = v;
      }
    }
  

  L.erase(i);
  rs.insert(i);

  for(int j = 0; j < n; j++){
    if (cost_edges[i][j] != INFINITY && rs.count(j) == 0) { //IF IS NOT INFINITE WE KNOW IS NOT ADJACENT
      if (d[i] + cost_edges[i][j] < d[j]){
        d[j] = d[i] + cost_edges[i][j];
        p[j] = i;
        L.insert(j);
      }
    }
  }


  }

  for(int i = 0; i < n; i++){
    if(i == start){

    }
    else { // do stack so we can know the flight connections and print them out 
      stack <int> s; //stack
      s.push(i);
      while(s.top() != start){
        s.push(p[s.top()]);
      }
      int cost = 0;
      int miles = 0;

      while(s.size() > 1){
        int trg = s.top();
        s.pop();
        int src = s.top();
        cost += cost_edges[trg][src];
        miles += mileage_edges[trg][src];
      }
      s.pop();
      s.push(i);

      bool flag = false;

      while(s.top() != start){
        s.push(p[s.top()]);
      }
      //PRINT  Source Dest Cost  Mileage
      cout << labels[start] << "\t" << labels[i] << "\t$" << cost << "\t" << miles;
      while(s.size() > 1){
        int src = s.top();
        s.pop();
        int trg = s.top();
        if(flag == false){ //align it correctly 
          cout << "\t";
          flag = true;
        }
        else {
          cout << "\t\t\t\t";
        } //print connecting flight info 
        //  Src -> Dest Cost  Mileage
        cout << labels[src] << "->" <<
        labels[trg] << " \t$" << cost_edges[src][trg] << "\t" << mileage_edges[src][trg] << endl;
      }
      cout << "----------------------------------------------------------------" << endl;
    }
  }

//delete d and p arrays 

  delete[] d;
  delete[] p;
}

// Function Name:    is_allowed_vertex
// Purpose:      see if it is an allowed vertex or not 
// Parameters:   set<int> verts, int vertex
// Returns:      true or alse 
// Pre-conditions:   if there is a vertex and is not equal to the end then true if not false
// Post-conditions: none
bool graph::is_allowed_vertex(set<int> verts, int vertex) {
    if (verts.find(vertex) != verts.end()) {
        return true;
    } else {
        return false;
    }
}
