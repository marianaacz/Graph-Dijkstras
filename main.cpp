// Author:       Mariana Acosta
// Assignment:       project 7
// File:       Graph
// Instructor:       Reza Sanati
// Class:       CSIS 2420  Section: 001
// Date Written:   June 20, 2018
// Description: get data from file build a graph of the possible flights, then find the shortest path from place to place based on the cost 

#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <climits>
#include <vector>
#include <list>
using namespace std;

const int INFINITY = INT_MAX;

// Function Name:    read_data
// Purpose:       read the input data and store it in different variables (src, dest, mile, cost)
// Parameters:      ifstream &input, graph &g
// Returns:       none void
// Pre-conditions:  while there's data pass it, if it equals to infinity add vertex 
// Post-conditions:none
void read_data(ifstream &input, graph &g) {
    string src;
    string dest;
    int mile = 0;
    int cost = 0;
    while (input >> src >> dest >> mile >> cost) {
        if (g.vertex(src) == INFINITY) {
            g.addVertex(src);
        }
        if (g.vertex(dest) == INFINITY) {
            g.addVertex(dest);
        }
        g.addEdge(g.vertex(src), g.vertex(dest), cost, mile);
       
    }
}

//----------------------MAIN-------------------------
int main() {
    string filename;
    ifstream file;
    string command;
    // int i;
    int data;
    string sourcePlace;
    
    cout << "Mariana Acosta Zermeño" << endl;
    cout << "CS2420 Section 1" << endl;
    cout << "Program 7: Graph" << endl;
    
    cout << "Enter the file name you would like to use:" << endl;
    cin >> filename; //get file input name
    file.open(filename); //open file 
    
    graph flights; //graph
    read_data(file, flights); //read the file and store it in the graph flights
     // flights.print();
    cout << "Enter source: (three letter abbreviation)" << endl;
    cin >> sourcePlace; //get place input 
    
    cout << "\t \t \t Best Price Report" << endl;
    cout << "\n\t\t\t\t Connecting Flight Information";
    cout << "\nSource Dest\tCost  Mileage   Src  Dest \tCost  \tMileage" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    
    //    flights.print();
    flights.shortestPath(sourcePlace); //call the shortest path function
    
}
