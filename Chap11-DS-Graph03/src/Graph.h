/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접행렬: 방향 그래프, 비가중치
 * std::vector<std::vector<bool>>를 이용하여 표현
 * 삭제를 쉽게 처리하기 위해 freeIndexes 큐 사용
 * 노드 이름은 std::string으로 처리
 * 노드 이름과 노드가 저장되는 색인을 연결시키기 위해 map 사용
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <queue>
#include <stack>
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
		for(int i=0; i<capacity; i++) graph[i].resize(capacity,0);
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
	// 방향그래프이므로 indegree와 outdegree가 같지 않음
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
		graph[fromIdx][toIdx] = true;
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
		if(graph[fromIdx][toIdx]!=1)
			throw std::invalid_argument("removeEdge: edge does not exists");
		// 무방향 그래프인 경우
		graph[fromIdx][toIdx] = false;
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (너비 우선 탐색)
	std::vector<std::string> bfs(std::string startNode){
		if(nodes.find(startNode)==nodes.end())
			throw std::invalid_argument("bfs: no such starting node: "+startNode);
		std::queue<std::string> queue;
		std::unordered_map<std::string, bool> visited(capacity*1.3+1);
		std::vector<std::string> result;
		queue.push(startNode);
		visited[startNode] = true;
		while(!queue.empty()){
			std::string currNode(queue.front());
			queue.pop();
			result.push_back(currNode);
			int idx{nodes[currNode]};
			for(int i=0; i<capacity; i++){
				std::string nextNode{inverseNodes[i]};
				if(graph[idx][i] && !visited[nextNode]){
					visited[nextNode] = true;
					queue.push(nextNode);
				}
			}
		}
		return result;
	}

	// 시작노드에서 목적노드까지의 거리
	int bfs(std::string startNode, std::string endNode){
		if(nodes.find(startNode)==nodes.end())
			throw std::invalid_argument("bfs: no such start node: "+startNode);
		if(nodes.find(endNode)==nodes.end())
			throw std::invalid_argument("bfs: no such end node: "+startNode);
		struct Data{
			std::string node;
			int length{0};
			Data(std::string node, int length): node(node), length{length}{}
		};
		std::queue<Data> queue;
		std::unordered_map<std::string, bool> visited(capacity*1.3+1);
		queue.emplace(startNode,0);
		visited[startNode] = true;
		while(!queue.empty()){
			Data data(queue.front());
			queue.pop();
			if(data.node==endNode) return data.length;
			int idx{nodes[data.node]};
			for(int i=0; i<capacity; i++){
				std::string nextNode{inverseNodes[i]};
				if(graph[idx][i] && !visited[nextNode]){
					visited[nextNode] = true;
					queue.emplace(nextNode,data.length+1);
				}
			}
		}
		return -1;
	}

	// 목적노드까지의 경로 구축
	std::vector<std::string> constructRoute(
		std::unordered_map<std::string, int>& visited, const std::string& startNode, const std::string& endNode){
		std::vector<std::string> result;
		int startIndex{nodes[startNode]};
		std::string currNode(endNode);
		result.push_back(currNode);
		int nextIndex{visited[currNode]};
		while(nextIndex!=startIndex){
			currNode = inverseNodes[nextIndex];
			result.push_back(currNode);
			nextIndex = visited[currNode];
		}
		result.push_back(startNode);
		std::reverse(result.begin(), result.end());
		return result;
	}
	// 시작노드에서 목적노드까지의 경로
	std::vector<std::string> bfsWithRoute(std::string startNode, std::string endNode){
		if(nodes.find(startNode)==nodes.end())
			throw std::invalid_argument("bfs: no such start node: "+startNode);
		if(nodes.find(endNode)==nodes.end())
			throw std::invalid_argument("bfs: no such end node: "+startNode);
		struct Data{
			std::string node;
			int length{0};
			Data(std::string node, int length): node(node), length{length}{}
		};
		std::queue<Data> queue;
		std::unordered_map<std::string, int> visited(capacity*1.3+1);
		for(auto node: nodes) visited[node.first] = -1;
		queue.emplace(startNode,0);
		visited[startNode] = nodes[startNode];
		while(!queue.empty()){
			Data data(queue.front());
			queue.pop();
			if(data.node==endNode) return constructRoute(visited, startNode, endNode);
			int idx{nodes[data.node]};
			for(int i=0; i<capacity; i++){
				if(graph[idx][i]&&visited[inverseNodes[i]]==-1){
					queue.emplace(inverseNodes[i],data.length+1);
					visited[inverseNodes[i]] = idx;
				}
			}
		}
		return std::vector<std::string>{};
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (깊이 우선 탐색)
	std::vector<std::string> dfs(std::string startNode){
		if(nodes.find(startNode)==nodes.end())
			throw std::invalid_argument("dfs: no such starting node: "+startNode);
		std::stack<std::string> stack;
		std::unordered_map<std::string, bool> visited(capacity*1.3+1);
		std::vector<std::string> result;
		stack.push(startNode);
		visited[startNode] = true;
		while(!stack.empty()){
			std::string currNode(stack.top());
			stack.pop();
			result.push_back(currNode);
			int idx{nodes[currNode]};
			for(int i=0; i<capacity; i++){
				std::string nextNode{inverseNodes[i]};
				if(graph[idx][i]&&!visited[nextNode]){
					stack.push(nextNode);
					visited[nextNode] = true;
				}
			}
		}
		return result;
	}
	std::unordered_map<std::string, int>::iterator begin() {return nodes.begin();}
	std::unordered_map<std::string, int>::iterator end() {return nodes.end();}
};

#endif /* GRAPH_H_ */
