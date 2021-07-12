/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * Tree.h
 * 일반 트리구조: 자식 노드에 대한 제한이 없음
 * 각 노드는 자식에 대한 포인터 벡터 유지
 * 부모에 대한 포인터는 유지하지 않음
 */

#ifndef TREE_H_
#define TREE_H_
#include <stdexcept>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Node {
private:
	int key = -1;
	// 자식들의 리스트
	std::vector<Node*> childs;
	// 순회 방법: bfs 또는 dfs
	bool bfsFlag{true};
	// 순회할 때 방문한 노드의 값들을 저장하는 리스트
	std::vector<int> list;
public:
	explicit Node() = default;
	explicit Node(int key): key{key}{}
	virtual ~Node(){
		for(auto node: childs)
			delete node;
	}
	void setValue(int key) noexcept {  this->key = key; }
	int getValue() const noexcept { return key;	}
	int numOfChilds() const { return childs.size(); } // 자식 갯수
	void addChild(Node* node){
		childs.push_back(node);
	}
	Node* getChild(int index) const{ // 자식 접근
		if(index<0||index>childs.size()) throw std::range_error("");
		return childs[index];
	}
	void removeChild(int index){
		if(index<0||index>childs.size()) throw std::range_error("");
		childs.erase(childs.begin()+index);
	}
	void setBFSIterator(bool flag){
		bfsFlag = flag;
	}
	std::vector<int>::iterator begin(){
		if(bfsFlag) bfs();
		else dfs();
		return list.begin();
	}
	std::vector<int>::iterator end(){
		return list.end();
	}
private:
	/*
	 * 이 메소드는 주어진 노드를 루트로 생각하여 트리를 bfs 또는 dfs로 탐색하게 되며,
	 * 탐색하는 과정에서 만나는 노드의 값을 차례로 list라는 멤버 변수에 저장합니다.
	 * bfs는 FIFO 큐를 이용하고, dfs는 stack 자료구조를 이용하여 구현합니다.
	 */

	// 너비 우선 -> FIFO 큐를 이용
	// 너비 우선으로 현재 노드를 루트로 가정하고 탐색하면서 방문한 순서대로 list에 저장함
	void bfs(){ // 큐 사용
		list.clear();
		std::queue<Node*> queue;
		queue.push(this);
		Node* curr{nullptr};

		while(!queue.empty()){
			curr = queue.front();
			list.push_back(curr->key);
			queue.pop();

			// 자식 노드 스택에 push
//			for(int i = 0; i < curr->numOfChilds(); i++){
//				queue.push(curr->childs[i]);
//			}
			for(auto node: curr->childs){
				queue.push(node);
			}

		}

	}
	// 깊이 우선 -> LIFO 스택 이용
	// 깊 우선으로 현재 노드를 루트로 가정하고 탐색하면서 방문한 순서대로 list에 저장함
	void dfs(){ // 스택 사용
		list.clear();

		std::stack<Node*> stack;
		stack.push(this);
		Node* curr{nullptr};

		while(!stack.empty()){
			curr = stack.top();
			list.push_back(curr->key);
			stack.pop();

			// 자식 노드를 스택에 push
			for(int i = 0; i < curr->numOfChilds(); i++){
				stack.push(curr->childs[i]);
			}

		}
	}
};

#endif /* TREE_H_ */
