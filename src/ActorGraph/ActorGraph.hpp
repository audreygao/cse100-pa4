/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    std::unordered_map<string, Actor*> actorMap;
    std::unordered_map<string, Movie*> movieMap;
    // TODO: add data structures used in actor graph

  public:
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
