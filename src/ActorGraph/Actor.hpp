/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains information for the
 * Actor class
 */
#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <string>
#include <vector>
#include "Movie.hpp"
using namespace std;

class Movie;

/**
 * this class define the Actor object
 * that serves as a vertex in the
 * graph
 */
class Actor {
  public:
    string name;
    vector<Movie*> movieList;

    Movie* previous;
    bool visited = 0;
    bool inQueue = 0;

    Actor(string actorName) {
        name = actorName;
        previous = 0;
    }
};

#endif
