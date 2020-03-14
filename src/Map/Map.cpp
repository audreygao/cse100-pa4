/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains information for the
 * map including methods to realize its functionality
 */
#include "Map.hpp"
#include <climits>
#include <queue>
/* constructor */
Map::Map() {}

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}

// comparator for priority queue
bool cmp(pair<Vertex*, float> a, pair<Vertex*, float> b) {
    return a.second > b.second;  // smaller cost has higher priority
}

/**
 * ind the weighted shortest path from vertex with name “from” to vertex
 * with name “to” in the map graph using Dijkstra’s algorithm
 * if there's no path, shortestPath should remain empty
 */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    // priority_queue<Vertex*, vector<Vertex*>, decltype(&cmp)> que(cmp);

    priority_queue<pair<Vertex*, float>, vector<pair<Vertex*, float>>,
                   decltype(&cmp)>
        que(cmp);

    // set dist, done and parent
    for (Vertex* v : vertices) {
        v->done = false;
        v->dist = INT_MAX;
        v->parent = nullptr;
    }

    // push the source vertex to the pq
    Vertex* start = vertices.at(vertexId[from]);
    start->dist = 0;
    que.push(make_pair(start, 0));

    while (!que.empty()) {
        // get the vertex with lowest cost
        Vertex* parent = que.top().first;
        que.pop();

        if (!parent->done) {
            parent->done = true;  // set to done

            // for each neighbor
            for (Edge* e : parent->outEdges) {
                Vertex* target = e->target;
                float c = parent->dist + e->weight;

                // update dist with the cost that's lower
                if (c < target->dist) {
                    target->parent = parent;
                    target->dist = c;
                    que.push(make_pair(target, c));
                }
            }
        }
    }

    // backtrack to find the path
    Vertex* end = vertices.at(vertexId[to]);
    Vertex* prev = end;
    while (prev != 0) {
        shortestPath.insert(shortestPath.begin(), prev);
        prev = prev->parent;
    }
}

/* comparator, the smaller weight has higher priority */
bool cmpEdge(Edge* a, Edge* b) { return a->weight > b->weight; }

/**
 * union method for the uptree
 * union the two vertices with optimization
 */
void Map::combine(Vertex* a, Vertex* b) {
    // index of both's centinodes
    int indexA = find(a);
    int indexB = find(b);

    // compare the size of the two sets
    int countA = upIndex[indexA];
    int countB = upIndex[indexB];

    // set A is larger in size
    if (countA < countB) {
        // make vertex b's centinode a's centinode
        upIndex[indexB] = indexA;

        // change the size of the a's centinode
        upIndex[indexA] = countA + countB;
    } else {
        // make vertex a's centinode b's centinode
        upIndex[indexA] = indexB;

        // change the size of the a's centinode
        upIndex[indexB] = countA + countB;
    }
}

/**
 * find method for the uptree
 * return the index of the vertex v's centinode in the uptree
 */
int Map::find(Vertex* v) {
    vector<int> indices;
    int index = vertexId[v->name];

    // record the indices of all the vertices on the path
    while (upIndex[index] >= 0) {
        indices.push_back(index);
        index = upIndex[index];
    }

    // the index of the centinode
    int root = index;

    // point all vertices on the path to the root: path compression
    for (int i : indices) {
        upIndex[i] = root;
    }

    return root;
}

/**
 * Find all the undirected edges in the minimum spanning tree of the map
 * graph.
 */
void Map::findMST(vector<Edge*>& MST) {
    // initialize the up trees
    upIndex = vector<int>(vertices.size(), -1);

    priority_queue<Edge*, vector<Edge*>, decltype(&cmpEdge)> que(cmpEdge);

    // push all edges into pq
    for (Edge* e : undirectedEdges) {
        que.push(e);
    }

    // pop smallest edge
    while (!que.empty()) {
        Edge* smallest = que.top();
        que.pop();

        // edge doesn't make a cycle
        if (find(smallest->source) != find(smallest->target)) {
            MST.push_back(smallest);
            combine(smallest->source,
                    smallest->target);  // union the two vertices
        }
    }
}

/**
 * perform a BFS search from from to to ignoring the direct edge between
 * them to determine if this edge is a bridge
 * Return true if can be reached, not a bridge, false otherwise
 */
bool Map::BFS(Vertex* from, Vertex* to) {
    queue<Vertex*> que;

    que.push(from);

    while (!que.empty()) {
        Vertex* v = que.front();
        que.pop();
        v->done = true;

        // for each neighbor of the vertex
        for (Edge* edge : v->outEdges) {
            Vertex* next = edge->target;

            // skip this edge if it's the edge between from and to
            if ((v == from && next == to) || (v == to && next == from)) {
                continue;
            }

            // push neighbor to queue if it's not done(added) yet
            if (!next->done) {
                que.push(next);
                next->done = true;  // mark it as added
            }

            // if the neighbor is to -> can be reached
            if (next == to) {
                return true;  // not a bridge
            }
        }
    }

    // cannot be reached, is a bridge
    return false;
}

/**
 * Find all the edges representing crucial roads in the map graph
 * and put them in roads, no order required
 */
void Map::crucialRoads(vector<Edge*>& roads) {
    for (Edge* edge : undirectedEdges) {
        // reset all the values for searching
        for (Vertex* v : vertices) {
            v->done = false;
            v->dist = INT_MAX;
            v->parent = nullptr;
        }

        // perform  BFS
        if (!BFS(edge->source, edge->target)) {
            roads.push_back(edge);
        }
    }
}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}

void Map::helperBuild(string name1, string name2, vector<string> ver,
                      vector<string> edge) {
    ofstream myfile1;
    myfile1.open(name1);
    for (string i : ver) {
        myfile1 << i;
        myfile1 << "\n";
    }
    myfile1.close();

    ofstream myfile2;
    myfile2.open(name2);
    for (string i : edge) {
        myfile2 << i;
        myfile2 << "\n";
    }
    myfile2.close();
    buildMapFromFile(name1, name2);
}