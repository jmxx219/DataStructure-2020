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
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	ASSERT_EQ(2, graph.indegree("E"));
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
	graph.addNode("F");
	ASSERT_EQ(0, graph.indegree("F"));
	ASSERT_EQ(2, graph.indegree("E"));
	nodeNames.push_back("F");
	for(auto s: graph){
		ASSERT_TRUE(std::find(nodeNames.begin(), nodeNames.end(), s.first)!=nodeNames.end());
	}
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
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	ASSERT_EQ(2, graph.indegree("D"));
	graph.removeNode("C");
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(1, graph.outdegree("A"));
	ASSERT_EQ(1, graph.outdegree("D"));
	ASSERT_EQ(4, graph.getSize());
	ASSERT_THROW(graph.indegree("C"), std::invalid_argument);
	graph.removeEdge("A","B");
	ASSERT_EQ(0, graph.indegree("B"));
	ASSERT_EQ(0, graph.outdegree("A"));
}

TEST(GraphAdjacentMatrix, bfsTest){
	Graph graph{"A","B","C","D","E"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("B","E");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	std::vector<std::string> nodes = graph.bfs("A");
	std::string output = "";
	for(auto s: nodes){
		output += s+",";
	}
	ASSERT_EQ(output,"A,B,C,E,D,");
	graph.addNode("F");
	graph.addNode("G");
	graph.addEdge("B","F");
	graph.addEdge("F","E");
	graph.addEdge("D","G");
	nodes = graph.bfs("A");
	output = "";
	for(auto s: nodes){
		output += s+",";
	}
	ASSERT_EQ(output,"A,B,C,E,F,D,G,");
}

TEST(GraphAdjacentMatrix, dfsTest){
	Graph graph{"A","B","C","D","E"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("B","E");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	std::vector<std::string> nodes = graph.dfs("A");
	std::string output = "";
	for(auto s: nodes){
		output += s+",";
	}
	ASSERT_EQ(output,"A,C,E,D,B,");
	graph.addNode("F");
	graph.addNode("G");
	graph.addEdge("B","F");
	graph.addEdge("F","E");
	graph.addEdge("D","G");
	nodes = graph.dfs("A");
	output = "";
	for(auto s: nodes){
		output += s+",";
	}
	ASSERT_EQ(output,"A,C,E,D,G,B,F,");
}

TEST(GraphAdjacentMatrix, bfsLengthTest){
	Graph graph{"A","B","C","D","E","F","G"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("B","E");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	graph.addEdge("B","F");
	graph.addEdge("F","E");
	graph.addEdge("D","G");
	ASSERT_EQ(2, graph.bfs("A","E"));
	ASSERT_EQ(3, graph.bfs("A","G"));
}

TEST(GraphAdjacentMatrix, MooreTest){
	Graph graph{"A","B","C","D","E","F","G"};
	graph.addEdge("A","B");
	graph.addEdge("A","C");
	graph.addEdge("B","E");
	graph.addEdge("C","D");
	graph.addEdge("C","E");
	graph.addEdge("D","E");
	graph.addEdge("B","F");
	graph.addEdge("F","E");
	graph.addEdge("D","G");
	std::vector<std::string> route = graph.bfsWithRoute("A","G");
	std::string output = "";
	for(auto s: route){
		output += s+",";
	}
	ASSERT_EQ(output,"A,C,D,G,");
	route = graph.bfsWithRoute("A","E");
	output = "";
	for(auto s: route){
		output += s+",";
	}
	ASSERT_EQ(output,"A,B,E,");
}
