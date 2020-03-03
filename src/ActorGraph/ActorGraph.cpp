/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
//#include "Actor.hpp"
//#include "Movie.hpp"

using namespace std;

/* TODO */
ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph

        // concatenate movie title and year
        title = title + "#@" + std::to_string(year);

        Actor* theActor;
        Movie* movie;

        // check if actorMap contains actor
        // if actor not created, create actor and add to map
        if (actorMap.find(actor) == actorMap.end()) {
            theActor = new Actor(actor);
            actorMap[actor] = theActor;
        }
        theActor = actorMap[actor];

        // check if movieMap contains movie
        // if movie not created, create and add to map
        if (movieMap.find(title) == movieMap.end()) {
            movie = new Movie(title);
            movieMap[title] = movie;
        }
        movie = movieMap[title];

        // add movie ptr to actor's movieList
        theActor->movieList.push_back(movie);
        // add actor ptr to movie's actorList
        movie->actorList.push_back(theActor);
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    // if fromActor and toActor are same person
    if (fromActor == toActor) {
    }

    // set the boolean conditions of all actor vertices to false
    for (auto i : actorMap) {
        i.second->visited = 0;
        i.second->inQueue = 0;
    }
    Actor* from = actorMap[fromActor];
    Actor* to;
    std::queue<Actor*> bfsQueue;

    bfsQueue.push(from);

    // add from actor to queue

    // while queue not empty add each actor in each movie to queue
    while (!bfsQueue.empty()) {
        // dequeue the the actor pointer and set as visited
        Actor* curr = bfsQueue.front();
        bfsQueue.pop();
        curr->visited = true;

        // go to each movie of current actor's movieList
        for (Movie* mov : curr->movieList) {
            // set the movie's previous to current actor
            mov->previous = curr;

            // go to each actor of the movie's actorlist
            for (Actor* act : mov->actorList) {
                // OR visited set
                if (!act->visited && !act->inQueue) {
                    // set the actor's previous to the current movie
                    act->previous = mov;

                    // check if actor matches the toActor
                    if (act->name == toActor) {
                        to = act;
                        break;
                    }

                    // add the actor ptr to queue
                    bfsQueue.push(act);
                    act->inQueue = true;
                }
            }
        }
    }

    // no path from fromActor to toActor, path remains empty
    if (to == 0) {
        return;
    }

    // to is the ptr to the toActor
    Actor* vertex = to;
    while (vertex->name != fromActor) {
        shortestPath.insert(0, vertex->name);
        Movie* edge = vertex->previous;
        shortestPath.insert(0, edge->name);
        vertex = edge->previous;
    }
    shortestPath.insert(0, vertex->name);
}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {
    for (auto i : actorMap) {
        delete (i.second);
    }
    for (auto j : movieMap) {
        delete (j.second);
    }
}
