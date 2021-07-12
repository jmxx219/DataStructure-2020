/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접 리스트: 무방향, 비가중치
 * std::unordered_map<std::string, std::list<std::string>>를 이용하여 표현
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <queue>
#include <vector>
#include <list>
#include <unordered_map>

class Graph {
private:
	std::unordered_map<std::string, std::list<std::string>> nodes;
public:
	Graph() = default;
	Graph(std::initializer_list<std::string> list): Graph{}{
		for(auto node: list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept{
		return nodes.size()==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	int getSize() const noexcept{
		return nodes.size();
	}
	// 무방향이면 indegree와 outdegree가 같음
	int indegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("indegree: No such node: "+node);
		return nodes[node].size();
	}
	int outdegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("outdegree: No such node: "+node);
		return nodes[node].size();
	}
	void addNode(const std::string& node){
		if(nodes.find(node)!=nodes.end())
			throw std::runtime_error("node already exists");
		std::list<std::string> list;
		nodes[node] = list;
	}
	void addEdge(const std::string& from, const std::string& to){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::runtime_error("addEdge: node does not exists");
		nodes[from].push_front(to);
		nodes[to].push_front(from);
	}
	void removeNode(const std::string& node){
		if(isEmpty()) return;
		if(nodes.find(node)==nodes.end())
			throw std::runtime_error("removeNode: node does not exists");
		for(auto label: nodes[node]){
			nodes[label].remove(node);
		}
		nodes.erase(node);
	}
	void removeEdge(const std::string& from, const std::string& to){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::runtime_error("removeEdge: node does not exists");
		auto it = std::find(nodes[from].begin(), nodes[from].end(), to);
		if(it==nodes[from].end())
			throw std::runtime_error("removeEdge: edge does not exists");
		nodes[from].remove(to);
		nodes[to].remove(from);
	}
	std::unordered_map<std::string, std::list<std::string>>::iterator begin() {return nodes.begin();}
	std::unordered_map<std::string, std::list<std::string>>::iterator end() {return nodes.end();}
};

#endif /* GRAPH_H_ */
