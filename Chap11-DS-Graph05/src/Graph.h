/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * Graph.h
 * 인접행렬: 방향 가중치 그래프
 * std::vector<std::vector<int>>를 이용하여 표현
 * 삭제를 쉽게 처리하기 위해 freeIndexes 큐 사용
 * 노드 이름은 std::string으로 처리
 * 노드 이름과 노드가 저장되는 색인을 연결시키기 위해 map 사용
 * 다익스트라 알고리즘
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
#include <stack>
#include <vector>
#include <unordered_map>
#include <functional>

using data = std::pair<std::string, int>;
using pqueue = std::priority_queue<data, std::vector<data>, std::greater<data>>;

class Graph {
private:
	unsigned int capacity{5};
	unsigned int size{0};
	std::vector<std::vector<int>> graph{capacity, std::vector<int>(capacity,-1)};
	std::queue<int> freeIndexes;
	std::unordered_map<std::string, int> nodes;
	std::unordered_map<int, std::string> inverseNodes;
// =================
	void increaseCapacity(){
		for(int i=capacity; i<capacity*2; i++)
			freeIndexes.push(i);
		capacity *= 2;
		graph.resize(capacity);
		for(int i=0; i<capacity; i++){
			graph[i].resize(capacity,-1);
			graph[i][i] = 0;
		}
		nodes.reserve(static_cast<int>(capacity*1.3+1));
		inverseNodes.reserve(static_cast<int>(capacity*1.3+1));
	}
public:
	Graph(){
		nodes.reserve(static_cast<int>(capacity*1.3+1));
		inverseNodes.reserve(static_cast<int>(capacity*1.3+1));
		for(int i=0; i<capacity; i++) freeIndexes.push(i);
		for(int i=0; i<capacity; i++) graph[i][i] = 0;
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
	int indegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("indegree: No such node: "+node);
		int idx{nodes[node]};
		int count{0};
		for(int i=0; i<capacity; i++){
			if(graph[i][idx]>0) ++count;
		}
		return count;
	}
	int outdegree(const std::string& node) {
		if(nodes.find(node) == nodes.end())
			throw std::invalid_argument("outdegree: No such node: "+node);
		int idx{nodes[node]};
		int count{0};
		for(int i=0; i<capacity; i++)
			if(graph[idx][i]>0) ++count;
		return count;
	}
	void addNode(const std::string& node){
		if(size==capacity) increaseCapacity();
		if(nodes.find(node)!=nodes.end())
			throw std::invalid_argument("node already exists");
		int idx{freeIndexes.front()};
		freeIndexes.pop();
		nodes[node] = idx;
		inverseNodes[idx] = node;
		++size;
	}
	void addEdge(const std::string& from, const std::string& to, int weight){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::invalid_argument("addEdge: node does not exists");
		int fromIdx{nodes[from]};
		int toIdx{nodes[to]};
		graph[fromIdx][toIdx] = weight;
	}
	void removeNode(const std::string& node){
		if(nodes.find(node)==nodes.end())
			throw std::invalid_argument("removeNode: node does not exists");
		if(isEmpty()) return;
		int delIdx{nodes[node]};
		nodes.erase(node);
		inverseNodes.erase(delIdx);
		freeIndexes.push(delIdx);
		for(int i=0; i<capacity; i++){
			graph[delIdx][i] = graph[i][delIdx] = -1;
		}
		graph[delIdx][delIdx] = 0;
		--size;
	}
	void removeEdge(const std::string& from, const std::string& to){
		if(nodes.find(from)==nodes.end()||nodes.find(to)==nodes.end())
			throw std::invalid_argument("removeEdge: node does not exists");
		int fromIdx{nodes[from]};
		int toIdx{nodes[to]};
		if(graph[fromIdx][toIdx]==-1)
			throw std::invalid_argument("removeEdge: edge does not exists");
		graph[fromIdx][toIdx] = 0;
	}
	int dijkstraAlgorithm(const std::string& src, const std::string& dest, std::vector<std::string>& path){
		const int INF{987654321};
		if(nodes.find(src) == nodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such source node: "+src);
		if(nodes.find(dest) == nodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such destination node: "+dest);

		// visited map 초기화
		std::unordered_map<std::string, int> distance(nodes.size()*1.3+1);
		std::unordered_map<std::string, std::string> previousNode(nodes.size()*1.3+1);
		for(auto node: nodes) distance[node.first] = INF;

 		pqueue queue;
		queue.emplace(src,0);
		distance[src] = 0;
		previousNode[src] = src;
		while(!queue.empty()){
			data curr(queue.top());
			queue.pop();
			int idx{nodes[curr.first]};
			for(int i=0; i<capacity; i++){
				if(graph[idx][i]>0){
					std::string nextNode(inverseNodes[i]);
					int accumulatedWeight = curr.second+graph[idx][i];
					// 새로 계산된 경로가 더 짧으면 갱신하고 큐에 포함
					if(accumulatedWeight<distance[nextNode]){
						previousNode[nextNode] = curr.first;
						distance[nextNode] = accumulatedWeight;
						queue.emplace(nextNode, accumulatedWeight);
					}
				}
			}
			debugPrint(queue, distance);
		}

		// 거꾸로 경로 설정
		std::string curr = dest;
		while(curr!=src){
			path.push_back(curr);
			curr = previousNode[curr];
		}
		path.push_back(curr);
		std::reverse(path.begin(), path.end());

		return distance[dest];
	}

	void debugPrint(pqueue queue, const std::unordered_map<std::string, int>& distance){
		std::cout << "distance:>> ";
		for(auto info: distance)
			std::cout << info.first << ":" << info.second << ", ";
		std::cout << "====\n";
		std::cout << "priority_queue:>> ";
		while(!queue.empty()){
			data curr(queue.top());
			queue.pop();
			std::cout << curr.first << ": " << curr.second << ", ";
		}
		std::cout << "====\n";
	}
	std::unordered_map<std::string, int>::iterator begin() {return nodes.begin();}
	std::unordered_map<std::string, int>::iterator end() {return nodes.end();}
};

#endif /* GRAPH_H_ */
