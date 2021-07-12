/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접 리스트: 방향 그래프, 비가증치
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
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>

class Graph {
private:
	// Graph02와 달리 두 개의 맵 유지 (방향성이 있기 때문)
	std::unordered_map<std::string, std::list<std::string>> outNodes;
	std::unordered_map<std::string, std::list<std::string>> inNodes;
public:
	Graph(int capacity = 7){
		outNodes.reserve(capacity);
		inNodes.reserve(capacity);
	}
	Graph(std::initializer_list<std::string> list): Graph(list.size()*1.3+1){
		for(auto node: list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept{
		return outNodes.size()==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	int getSize() const noexcept{
		return outNodes.size();
	}
	int indegree(const std::string& node) {
		if(inNodes.find(node) == inNodes.end())
			throw std::invalid_argument("indegree: No such node: "+node);
		return inNodes[node].size();
	}
	int outdegree(const std::string& node) {
		if(outNodes.find(node) == outNodes.end())
			throw std::invalid_argument("outdegree: No such node: "+node);
		return outNodes[node].size();
	}
	void addNode(const std::string& node){
		if(outNodes.find(node)!=outNodes.end())
			throw std::runtime_error("node already exists");
		outNodes[node] = std::list<std::string>{};
		inNodes[node] = std::list<std::string>{};
	}
	void addEdge(const std::string& from, const std::string& to){
		if(outNodes.find(from)==outNodes.end()||outNodes.find(to)==outNodes.end())
			throw std::runtime_error("addEdge: node does not exists");
		outNodes[from].push_front(to);
		inNodes[to].push_front(from);
	}
	void removeNode(const std::string& node){
		if(isEmpty()) return;
		if(outNodes.find(node)==outNodes.end())
			throw std::runtime_error("removeNode: node does not exists");
		outNodes.erase(node);
		for(auto& other: outNodes){
			other.second.remove(node);
		}
		inNodes.erase(node);
		for(auto& other: inNodes){
			other.second.remove(node);
		}
	}
	void removeEdge(const std::string& from, const std::string& to){
		if(outNodes.find(from)==outNodes.end()||outNodes.find(to)==outNodes.end())
			throw std::runtime_error("removeEdge: node does not exists");
		auto it = std::find(outNodes[from].begin(), outNodes[from].end(), to);
		if(it==outNodes[from].end())
			throw std::runtime_error("removeEdge: edge does not exists");
		it = std::find(inNodes[to].begin(), inNodes[to].end(), from);
		if(it==inNodes[to].end())
			throw std::runtime_error("removeEdge: edge does not exists");
		outNodes[from].remove(to);
		inNodes[to].remove(from);
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (너비 우선 탐색)
	std::vector<std::string> bfs(std::string startNode){
		if(outNodes.find(startNode)==outNodes.end())
			throw std::invalid_argument("bfs: no such starting node: "+startNode);
		std::queue<std::string> queue;
		std::unordered_map<std::string, bool> visited(inNodes.size()*1.3+1);
		std::vector<std::string> result;
		queue.push(startNode);
		visited[startNode] = true;
		while(!queue.empty()){
			std::string currNode(queue.front());
			queue.pop();
			result.push_back(currNode);
			for(auto nextNode: outNodes[currNode]){
				if(!visited[nextNode]){
					queue.push(nextNode);
					visited[nextNode] = true;
				}
			}
		}
		return result;
	}

	std::vector<std::string> constructRoute(
		std::unordered_map<std::string, std::string>& visited, const std::string& startNode, const std::string& endNode){
		std::vector<std::string> result;
		std::string currNode{endNode};
		while(currNode!=startNode){
			result.push_back(currNode);
			currNode = visited[currNode];
		}
		result.push_back(startNode);
		std::reverse(result.begin(), result.end());
		return result;
	}
	// 시작노드에서 목적노드까지의 경로
	std::vector<std::string> bfsWithRoute(std::string startNode, std::string endNode){
		if(outNodes.find(startNode)==outNodes.end())
			throw std::invalid_argument("bfs: no such start node: "+startNode);
		if(outNodes.find(endNode)==outNodes.end())
			throw std::invalid_argument("bfs: no such end node: "+startNode);
		struct Data{
			std::string node;
			int length{0};
			Data(std::string node, int length): node(node), length{length}{}
		};
		std::queue<Data> queue;
		std::unordered_map<std::string, std::string> visited(inNodes.size()*1.3+1);
		for(auto node: inNodes) visited[node.first] = "";
		queue.emplace(startNode,0);
		visited[startNode] = startNode;
		while(!queue.empty()){
			Data data(queue.front());
			queue.pop();
			if(data.node==endNode){
				return constructRoute(visited, startNode, endNode);
			}
			for(auto nextNode: outNodes[data.node]){
				if(visited[nextNode]==""){
					queue.emplace(nextNode,data.length+1);
					visited[nextNode] = data.node;
				}
			}
		}
		return std::vector<std::string>{};
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (깊이 우선 탐색)
	std::vector<std::string> dfs(std::string startNode){
		if(outNodes.find(startNode)==outNodes.end())
			throw std::invalid_argument("dfs: no such starting node: "+startNode);
		std::stack<std::string> stack;
		std::unordered_map<std::string, bool> visited(inNodes.size()*1.3+1);
		std::vector<std::string> result;
		stack.push(startNode);
		visited[startNode] = true;
		while(!stack.empty()){
			std::string currNode(stack.top());
			stack.pop();
			result.push_back(currNode);
			for(auto nextNode: outNodes[currNode]){
				if(!visited[nextNode]){
					stack.push(nextNode);
					visited[nextNode] = true;
				}
			}
		}
		return result;
	}
	std::unordered_map<std::string, std::list<std::string>>::iterator begin() {return outNodes.begin();}
	std::unordered_map<std::string, std::list<std::string>>::iterator end() {return outNodes.end();}
};

#endif /* GRAPH_H_ */
