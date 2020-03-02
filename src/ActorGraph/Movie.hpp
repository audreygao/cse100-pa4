#include <string>
#include <vector>
#include "Actor.hpp"
using namespace std;
class Movie {
  public:
    string name;
    vector<Actor*> actorList;
    Actor* previous;
    Movie(string movieName);
    ~Movie();
};

Movie::Movie(string movieName) {
    name = movieName;
    previous = 0;
}

Movie::~Movie() {}