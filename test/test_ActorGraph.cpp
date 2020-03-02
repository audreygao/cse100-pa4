#include <gtest/gtest.h>
#include "ActorGraph.hpp"
using namespace std;
using namespace testing;

// TODO: add tests for actor graph
TEST(ActorGraphTests, test1) {
    ActorGraph graph;
    graph.buildGraphFromFile("./data/small_actor_graph.tsv");
    string path;
    graph.BFS("Kevin Bacon", "Michael Fassbender", path);
    ASSERT_EQ(path, "Kevin BaconX-Men: First Class2011Michael Fassbender");
}