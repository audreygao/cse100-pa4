/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains information for the
 * Movie class
 */
#ifndef MOVIE_HPP
#define MOVIE_HPP
#include <string>
#include <vector>
using namespace std;

class Actor;

/**
 * this class defines the Movie object that
 * serves as edge in the graph
 */
class Movie {
  public:
    string name;
    vector<Actor*> actorList;
    Actor* previous;  // for BFS
    Movie(string movieName) {
        name = movieName;
        previous = 0;
    }
};

#endif