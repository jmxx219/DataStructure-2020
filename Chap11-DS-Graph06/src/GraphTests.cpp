/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * GraphTests.cpp
 * 테스트 프로그램
 */

#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "Graph.h"

TEST(GraphAdjacentList, addTest)
{
	Graph graph{"A","B","C","D","E"};
	std::vector<std::string> nodeNames{"A","B","C","D","E"};
	graph.addEdge("A","B",2);
	graph.addEdge("A","C",3);
	graph.addEdge("A","E",5);
	graph.addEdge("B","C",7);
	graph.addEdge("B","D",6);
	graph.addEdge("C","E",1);
	graph.addEdge("D","C",3);
	graph.addEdge("E","D",2);
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(3, graph.outdegree("A"));
	ASSERT_EQ(3, graph.indegree("C"));
	ASSERT_EQ(1, graph.outdegree("C"));
	ASSERT_EQ(2, graph.indegree("E"));
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
	graph.addNode("F");
	graph.addEdge("E","F",2);
	graph.addEdge("D","F",2);
	ASSERT_EQ(2, graph.indegree("F"));
	ASSERT_EQ(2, graph.indegree("E"));
	nodeNames.push_back("F");
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
}

TEST(GraphAdjacentList, removeTest)
{
	Graph graph{"A","B","C","D","E"};
	graph.addEdge("A","B",2);
	graph.addEdge("A","C",3);
	graph.addEdge("A","E",5);
	graph.addEdge("B","C",7);
	graph.addEdge("B","D",6);
	graph.addEdge("C","E",1);
	graph.addEdge("D","C",3);
	graph.addEdge("E","D",2);
	ASSERT_EQ(3, graph.outdegree("A"));
	ASSERT_EQ(1, graph.indegree("B"));
	ASSERT_EQ(2, graph.outdegree("B"));
	graph.removeNode("C");
	ASSERT_EQ(1, graph.outdegree("B"));
	ASSERT_EQ(2, graph.outdegree("A"));
	ASSERT_EQ(4, graph.getSize());
	ASSERT_THROW(graph.indegree("C"), std::invalid_argument);
	graph.removeEdge("A","B");
	ASSERT_EQ(0, graph.indegree("B"));
	ASSERT_EQ(1, graph.outdegree("A"));

	std::vector<std::string> nodeNames{"A","B","D","E"};
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
}

TEST(GraphAdjacentList, dijkstraTest)
{
	Graph graph{"A","B","C","D","E"};
	graph.addEdge("A","B",2);
	graph.addEdge("A","C",3);
	graph.addEdge("A","E",5);
	graph.addEdge("B","C",7);
	graph.addEdge("B","D",6);
	graph.addEdge("C","E",1);
	graph.addEdge("D","C",3);
	graph.addEdge("E","D",2);
	ASSERT_EQ(6, graph.dijkstraAlgorithm("A","D"));
}
