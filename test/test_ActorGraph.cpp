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
    // string path;
    // graph.BFS("Robert Downey Jr.", "James McAvoy", path);
    // ASSERT_EQ(path,
    //           "(Robert Downey Jr.)--[Avengers: Endgame#@2019]-->(Samuel L. "
    //           "Jackson)--[Glass#@2019]-->(James McAvoy)");
}