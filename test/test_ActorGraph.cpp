/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains tests for the
 * ActorGraph and its functionalities
 */
#include <gtest/gtest.h>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"
using namespace std;
using namespace testing;

// add tests for actor graph
TEST(ActorGraphTests, test1) {
    ActorGraph graph;

    graph.helperFill("Kevin Bacon", "X-Men: First Class", 2011);
    graph.helperFill("James McAvoy", "X-Men: First Class", 2011);
    graph.helperFill("James McAvoy", "X-Men: Apocalypse", 2016);
    graph.helperFill("James McAvoy", "Glass", 2019);
    graph.helperFill("Michael Fassbender", "X-Men: First Class", 2011);
    graph.helperFill("Michael Fassbender", "X-Men: Apocalypse", 2016);

    string path;
    graph.BFS("Kevin Bacon", "Michael Fassbender", path);
    ASSERT_EQ(
        path,
        "(Kevin Bacon)--[X-Men: First Class#@2011]-->(Michael Fassbender)");
}

TEST(ActorGraphTests, test2) {
    ActorGraph graph;
    vector<string> vec = {"Actor/Actress\tMovie\tYear",
                          "Kevin Bacon\tX-Men: First Class\t2011",
                          "James McAvoy\tX-Men: First Class\t2011"};

    graph.helper("sample.tsv", vec);
    string path;
    graph.BFS("Kevin Bacon", "James McAvoy", path);
    ASSERT_EQ(path,
              "(Kevin Bacon)--[X-Men: First Class#@2011]-->(James McAvoy)");
}