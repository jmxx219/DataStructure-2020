/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접 리스트: 방향 가중치 그래프
 * std::map<std::string, std::list<std::string>>를 이용하여 표현
 * 다익스트라 알고리즘
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
#include <functional>
#include <unordered_map>

using data = std::pair<std::string, int>;
using pqueue = std::priority_queue<data, std::vector<data>, std::greater<data>>;

class Graph {
	struct Edge{
		std::string node;
		int weight;
		Edge(std::string node, int weight = -1):
			node(node), weight{weight}{}
	};
private:
	std::unordered_map<std::string, std::list<Edge>> outNodes;
	std::unordered_map<std::string, std::list<Edge>> inNodes;
	bool findNode(const std::list<Edge>& edges, const std::string& node){
		for(auto edge: edges)
			if(edge.node==node) return true;
		return false;
	}
public:
	Graph(int capacity = 7){
		outNodes.reserve(capacity);
		inNodes.reserve(capacity);
	}
	Graph(std::initializer_list<std::string> list): Graph{}{
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
		std::list<Edge> inList;
		std::list<Edge> outList;
		outNodes[node] = outList;
		inNodes[node] = inList;
	}
	void addEdge(const std::string& from, const std::string& to, int weight){
		if(outNodes.find(from)==outNodes.end()||outNodes.find(to)==outNodes.end())
			throw std::runtime_error("addEdge: node does not exists");
		outNodes[from].emplace_front(to, weight);
		inNodes[to].emplace_front(from, weight);
	}
	void removeNode(const std::string& node){
		if(isEmpty()) return;
		if(outNodes.find(node)==outNodes.end())
			throw std::runtime_error("removeNode: node does not exists");
		outNodes.erase(node);
		for(auto& other: outNodes){
			other.second.remove_if([&node](Edge neighbor){ return neighbor.node==node;});
		}
		inNodes.erase(node);
		for(auto& other: inNodes){
			other.second.remove_if([&node](Edge neighbor){ return neighbor.node==node;});
		}
	}
	void removeEdge(const std::string& from, const std::string& to){
		if(outNodes.find(from)==outNodes.end()||outNodes.find(to)==outNodes.end())
			throw std::runtime_error("removeEdge: node does not exists");
		if(!findNode(outNodes[from], to))
			throw std::runtime_error("removeEdge: edge does not exists");
		outNodes[from].remove_if([&to](Edge neighbor){ return neighbor.node==to;});
		inNodes[to].remove_if([&from](Edge neighbor){ return neighbor.node==from;});
	}
	int dijkstraAlgorithm(const std::string& src, const std::string& dest){
		const int INF{987654321};
		if(outNodes.find(src) == outNodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such source node: "+src);
		if(outNodes.find(dest) == outNodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such destination node: "+dest);

		std::unordered_map<std::string, int> distance(inNodes.size()*1.3+1);
		std::unordered_map<std::string, std::string> previousNode(inNodes.size()*1.3+1);
		for(auto node: inNodes) distance[node.first] = INF;

		pqueue queue;
		queue.emplace(src,0);
		distance[src] = 0;
		previousNode[src] = src;
		while(!queue.empty()){
			data curr(queue.top());
			queue.pop();
			for(auto edge: outNodes[curr.first]){
				int accumulatedWeight = curr.second+edge.weight;
				if(accumulatedWeight<distance[edge.node]){
					previousNode[edge.node] = curr.first;
					distance[edge.node] = accumulatedWeight;
					queue.emplace(edge.node, accumulatedWeight);
				}
			}
		}
		return distance[dest];
	}
	std::unordered_map<std::string, std::list<Edge>>::iterator begin() {return outNodes.begin();}
	std::unordered_map<std::string, std::list<Edge>>::iterator end() {return outNodes.end();}
};

#endif /* GRAPH_H_ */
