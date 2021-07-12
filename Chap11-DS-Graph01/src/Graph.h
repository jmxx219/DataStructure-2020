/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접행렬: 무방향, 비가중치
 * std::vector<std::vector<bool>>를 이용하여 표현
 * 삭제를 쉽게 처리하기 위해 freeIndexes 큐 사용
 * 노드 이름은 std::string으로 처리
 * 노드 이름과 노드가 저장되는 색인을 연결시키기 위해 map 사용
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

class Graph {
private:
	unsigned int capacity{5};
	unsigned int size{0};
	std::vector<std::vector<bool>> graph{capacity, std::vector<bool>(capacity,false)};
	std::queue<int> freeIndexes;
	std::unordered_map<std::string, int> nodes;
	std::unordered_map<int, std::string> inverseNodes;
// =================
	void increaseCapacity(){
		for(int i=capacity; i<capacity*2; i++)
			freeIndexes.push(i);
		capacity *= 2;
		graph.resize(capacity);
		for(int i=0; i<capacity; i++) graph[i].resize(capacity,false);
		nodes.reserve(static_cast<int>(capacity*1.3+1));
		inverseNodes.reserve(static_cast<int>(capacity*1.3+1));
	}
public:
	Graph(){
		nodes.reserve(static_cast<int>(capacity*1.3+1));
		inverseNodes.reserve(static_cast<int>(capacity*1.3+1));
		for(int i=0; i<capacity; i++)
			freeIndexes.push(i);
	}
	Graph(std::initializer_list<std::string> list): Graph{}{
		for(auto node: list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept{
		return size==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	int getSize() const noexcept{
		return size;
	}
	// 무방향이면 indegree와 outdegree가 같음
	int indegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("indegree: No such node: "+node);
		int idx = nodes[node];
		int count = 0;
		for(int i=0; i<capacity; i++)
			if(graph[i][idx]) ++count;
		return count;
	}
	int outdegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("outdegree: No such node: "+node);
		int idx = nodes[node];
		int count = 0;
		for(int i=0; i<capacity; i++)
			if(graph[idx][i]) ++count;
		return count;
		// return indegree(node);
	}
	void addNode(const std::string& node){
		if(size==capacity) increaseCapacity();
		if(nodes.find(node)!=nodes.end())
			throw std::invalid_argument("node already exists");
		int idx = freeIndexes.front();
		freeIndexes.pop();
		nodes[node] = idx;
		inverseNodes[idx] = node;
		++size;
	}
	void addEdge(const std::string& from, const std::string& to){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::invalid_argument("addEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		// 무방향 그래프인 경우
		graph[fromIdx][toIdx] = graph[toIdx][fromIdx] = true;
	}
	void removeNode(const std::string& node){
		if(nodes.find(node)==nodes.end())
			throw std::invalid_argument("removeNode: node does not exists");
		if(isEmpty()) return;
		int delIdx = nodes[node];
		nodes.erase(node);
		inverseNodes.erase(delIdx);
		freeIndexes.push(delIdx);
		for(int i=0; i<capacity; i++){
			graph[delIdx][i] = graph[i][delIdx] = false;
		}
		--size;
	}
	void removeEdge(const std::string& from, const std::string& to){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::invalid_argument("removeEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		if(!graph[fromIdx][toIdx])
			throw std::invalid_argument("removeEdge: edge does not exists");
		// 무방향 그래프인 경우
		graph[fromIdx][toIdx] = graph[toIdx][fromIdx] = false;
	}
	std::unordered_map<std::string, int>::iterator begin() {return nodes.begin();}
	std::unordered_map<std::string, int>::iterator end() {return nodes.end();}
};

#endif /* GRAPH_H_ */
