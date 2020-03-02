#include <string>
#include <vector>
#include "Movie.hpp"
using namespace std;

class Actor {
  private:
    /* data */
  public:
    string name;
    vector<Movie*> movieList;

    Movie* previous;

    Actor(string actorName);
    ~Actor();
};

Actor::Actor(string actorName) {
    name = actorName;
    previous = 0;
}

Actor::~Actor() {}
