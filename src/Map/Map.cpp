
#include "Map.hpp"
#include <climits>
#include <queue>
/* TODO */
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
bool cmp(Vertex* a, Vertex* b) {
    return a->dist > b->dist;

    // // different frequency, return the one with larger frequncy
    // if (a.second != b.second) {
    //     return a.second < b.second;
    // }

    // // same frequency, compare ascii value of string
    // return a.first > b.first;
}

/* TODO */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    priority_queue<Vertex*, vector<Vertex*>, decltype(&cmp)> que(cmp);

    // set dist, done and parent
    for (Vertex* v : vertices) {
        v->done = false;
        v->dist = INT_MAX;
        v->parent = nullptr;
    }

    Vertex* start = vertices.at(vertexId[from]);
    start->dist = 0;
    que.push(start);

    while (!que.empty()) {
        Vertex* parent = que.top();
        que.pop();

        if (!parent->done) {
            parent->done = true;
            for (Edge* e : parent->outEdges) {
                Vertex* target = e->target;
                float c = parent->dist + e->weight;
                if (c < target->dist) {
                    target->parent = parent;
                    target->dist = c;
                    que.push(target);
                }
            }
        }
    }

    Vertex* end = vertices.at(vertexId[to]);
    Vertex* prev = end;
    while (prev != 0) {
        shortestPath.insert(shortestPath.begin(), prev);
        prev = prev->parent;
    }
}

bool cmpEdge(Edge* a, Edge* b) { return a->weight > b->weight; }

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

/* TODO */
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

bool Map::BFS(Vertex* from, Vertex* to) {
    // for (Vertex* v : vertices) {
    //     v->done = false;
    //     // v->dist = INT_MAX;
    //     // v->parent = nullptr;
    // }

    queue<Vertex*> que;

    que.push(from);

    while (!que.empty()) {
        Vertex* v = que.front();
        que.pop();
        v->done = true;
        std::cout << v->name << endl;
        for (Edge* edge : v->outEdges) {
            Vertex* next = edge->target;

            // skip this edge
            if ((v == from && next == to) || (v == to && next == from)) {
                continue;
            }
            if (!next->done) {
                que.push(next);
            }
            if (next == to) {
                std::cout << v->name << endl;
                std::cout << next->name << endl;
                std::cout << "true" << endl;
                return true;
            }
        }
    }
    std::cout << "false" << endl;
    return false;
}

/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {
    // for (Vertex* v : vertices) {
    //     v->done = false;
    //     // v->dist = INT_MAX;
    //     // v->parent = nullptr;
    // }

    for (Edge* edge : undirectedEdges) {
        for (Vertex* v : vertices) {
            v->done = false;
            // v->dist = INT_MAX;
            // v->parent = nullptr;
        }
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
