/**
 * Author: Ya Gao, Qingyang Xu
 * Emails: yag003@ucsd.edu, q4xu@ucsd.edu
 * Description: this file contains tests for the
 * map and its methods
 */
#include <gtest/gtest.h>
#include "Map.hpp"

using namespace std;
using namespace testing;

// add tests for map graph
TEST(MAPTESTS, TEST_D) {
    Map map;
    map.addVertex("A", 0, 0);
    map.addVertex("B", 3, 0);
    map.addVertex("C", 3, 4);
    map.addEdge("A", "B");
    map.addEdge("B", "C");
    map.addEdge("A", "C");
    vector<Vertex*> shortestPath;
    map.Dijkstra("A", "C", shortestPath);
    vector<string> vec = {"A", "C"};
    for (int i = 0; i < shortestPath.size(); i++) {
        ASSERT_EQ(shortestPath[i]->name, vec[i]);
    }
}

TEST(MAPTESTS, TEST_MST) {
    Map map;
    map.addVertex("A", 0, 0);
    map.addVertex("B", 3, 0);
    map.addVertex("C", 3, 4);
    map.addEdge("A", "B");
    map.addEdge("B", "C");
    map.addEdge("A", "C");

    vector<Edge*> MST;
    map.findMST(MST);
    ASSERT_EQ(MST[0]->source->name, "A");
    ASSERT_EQ(MST[0]->target->name, "B");
    ASSERT_EQ(MST[1]->source->name, "B");
    ASSERT_EQ(MST[1]->target->name, "C");
}

TEST(MAPTESTS, TEST_CR) {
    Map map;
    map.addVertex("A", 0, 0);
    map.addVertex("B", 3, 0);
    map.addVertex("C", 3, 4);
    map.addVertex("D", 10, 10);
    map.addEdge("A", "B");
    map.addEdge("B", "C");
    map.addEdge("A", "C");
    map.addEdge("C", "D");

    vector<Edge*> roads;

    map.crucialRoads(roads);
    ASSERT_EQ(roads[0]->source->name, "C");
    ASSERT_EQ(roads[0]->target->name, "D");
}