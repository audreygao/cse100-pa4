#ifndef MOVIE_HPP
#define MOVIE_HPP
#include <string>
#include <vector>
//#include "Actor.hpp"
using namespace std;

class Actor;

class Movie {
  public:
    string name;
    vector<Actor*> actorList;
    Actor* previous;
    Movie(string movieName) {
        name = movieName;
        previous = 0;
    }
    //~Movie();
};

#endif