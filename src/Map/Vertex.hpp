#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <climits>
#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    Vertex* parent = nullptr;
    int dist = INT_MAX;
    bool done = false;
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges

    // TODO: you may add more member variables here

    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y) : name(name), x(x), y(y) {}
};

#endif  // VERTEX_HPP