/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains information for the
 * Map class including methods and helper method headers
 */
#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Edge.hpp"

using namespace std;

/**
 * this class defines functionalities of the Map
 * including finding the shortest path between two vertices,
 * finding the minimum spanning tree, and finding
 * the crucial road in the graph
 */
class Map {
  private:
    // vector storing vertices in the map: id of each vertex = index in vector
    vector<Vertex*> vertices;

    // the data structure for storing the uptree
    vector<int> upIndex;

    // Map: name of vertex -> id of vertex = index storing vertex ptr
    unordered_map<string, unsigned int> vertexId;

    // Directed edge in vector represents an undirected edge used in MST
    vector<Edge*> undirectedEdges;

  public:
    /*
     * Add a vertex with name and x, y coordinates to the map graph. Returns
     * false if the name already existed in the map graph, and true otherwise
     */
    bool addVertex(const string& name, float x, float y);

    /*
     * Add an undirected edge between vertices with names "name1" and "name2".
     * Returns false if either name is not in the map graph.
     */
    bool addEdge(const string& name1, const string& name2);

    /* constructor */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /**
     * ind the weighted shortest path from vertex with name “from” to vertex
     * with name “to” in the map graph using Dijkstra’s algorithm
     * if there's no path, shortestPath should remain empty
     */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /**
     * union method for the uptree
     * union the two vertices with optimization
     */
    void combine(Vertex* a, Vertex* b);

    /**
     * find method for the uptree
     * return the index of the vertex v's centinode in the uptree
     */
    int find(Vertex* v);

    /**
     * Find all the undirected edges in the minimum spanning tree of the map
     * graph.
     */
    void findMST(vector<Edge*>& MST);

    /**
     * perform a BFS search from from to to ignoring the direct edge between
     * them to determine if this edge is a bridge
     * Return true if can be reached, not a bridge, false otherwise
     */
    bool BFS(Vertex* from, Vertex* to);

    /**
     * Find all the edges representing crucial roads in the map graph
     * and put them in roads, no order required
     */
    void crucialRoads(vector<Edge*>& roads);

    void helperBuild(string name1, string name2, vector<string> ver,
                     vector<string> edge);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP