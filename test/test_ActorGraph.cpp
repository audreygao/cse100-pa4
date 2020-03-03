#include <gtest/gtest.h>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"
using namespace std;
using namespace testing;

// TODO: add tests for actor graph
TEST(ActorGraphTests, test1) {
    ActorGraph graph;

    // graph.buildGraphFromFile("data/small_actor_graph.tsv");

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