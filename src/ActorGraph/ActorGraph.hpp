/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains information for the
 * ActorGraph including methods headers
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"

using namespace std;

/**
 * This class defines functionalities such
 * as building the graph and finding the shortest path
 * between two actors
 */
class ActorGraph {
  protected:
  public:
    // store the Actor and Movie
    std::unordered_map<string, Actor*> actorMap;
    std::unordered_map<string, Movie*> movieMap;
    /* constructor */
    ActorGraph();

    /** Build the actor graph from dataset file.
     * Each line of the dataset file must be formatted as:
     * ActorName <tab> MovieName <tab> Year
     * Two actors are connected by an undirected edge if they have worked in a
     * movie before.
     */
    bool buildGraphFromFile(const char* filename);

    /**
     * method to build the graph not from a file
     * for unit testing
     */
    void helperFill(string name, string mov, int year);

    /**
     * unit testing purpose: build the graph
     * creating a graph with the input information
     * and call buildGraphFromFile to build the graph
     */
    void helper(const char* name, vector<string> str);

    /**
     * find the unweighted shortest path from fromActor
     * to toActor and record it in shortestPath
     * can be any shortest path if there're multiple of them
     */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /**
     * Extra credit only
     */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* destructor */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
