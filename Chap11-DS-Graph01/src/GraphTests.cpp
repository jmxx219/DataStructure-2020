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

TEST(GraphAdjacentMatrix, addTest)
{
	Graph graph{"A","B","C","D","E"};
	std::vector<std::string> nodeNames{"A","B","C","D","E"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	ASSERT_EQ(2, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	ASSERT_EQ(2, graph.outdegree("E"));
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
	graph.addNode("F");
	ASSERT_EQ(0, graph.indegree("F"));
	ASSERT_EQ(2, graph.indegree("A"));
}

TEST(GraphAdjacentMatrix, removeTest)
{
	Graph graph{"A","B","C","D","E"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("B","D");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	ASSERT_EQ(2, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	ASSERT_EQ(3, graph.indegree("D"));
	graph.removeNode("C");
	ASSERT_EQ(1, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("D"));
	ASSERT_EQ(4, graph.getSize());
	ASSERT_THROW(graph.indegree("C"), std::invalid_argument);
	graph.removeEdge("A","B");
	ASSERT_EQ(1, graph.indegree("B"));
	ASSERT_EQ(0, graph.outdegree("A"));
}
