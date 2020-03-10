/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"
//#include "Movie.hpp"

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph

  public:
    std::unordered_map<string, Actor*> actorMap;
    std::unordered_map<string, Movie*> movieMap;
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraphFromFile(const char* filename);

    void helperFill(string name, string mov, int year);
    void helper(const char* name, vector<string> str);
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
