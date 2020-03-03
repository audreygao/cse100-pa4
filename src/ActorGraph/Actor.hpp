#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <string>
#include <vector>
#include "Movie.hpp"
using namespace std;

class Movie;

class Actor {
  private:
    /* data */
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
    //~Actor();
};

// Actor(string actorName) {}

// Actor::~Actor() {}
#endif
