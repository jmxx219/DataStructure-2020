/* 03
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BST.h
 * 이진 검색 트리:
 * 1) 부모에 대한 포인터를 유지하지 않음
 * 2) 비재귀적으로 구현
 * 3) 중복을 허용하지 않음
 * 실습 2를 비재귀적으로
 */

#ifndef BST_H_
#define BST_H_
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <utility>

class BST {
public:
	enum class TreeTraversal {INORDER, PREORDER, POSTORDER};
private:
	struct TreeNode{
		int key;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int key = -1, TreeNode* left = nullptr, TreeNode* right = nullptr):
			key{key}, left{left}, right{right}{}
	};
	TreeNode* root{nullptr};
	unsigned int size{0};
	// 반복자를 위해 필요한 요소
	std::vector<int> list;
	TreeTraversal traversalMethod{TreeTraversal::INORDER};
public:
	BST() = default;
	BST(const std::initializer_list<int>& initList){
		for(auto key: initList) add(key);
	}
	BST(const BST& other){
		preOrder(other.root);
		for(auto key: list) add(key);
	}
	BST(BST&& tmp){
		root = tmp.root;
		size = tmp.size;
		tmp.root = nullptr;
		tmp.size = 0;
	}
	virtual ~BST(){
		clear();
	}

	const BST& operator=(const BST& other){
		clear();
		list.clear();
		preOrder(other.root);
		for(auto key: list) add(key);
		return *this;
	}
	const BST& operator=(BST&& tmp){
		root = tmp.root;
		size = tmp.size;
		tmp.root = nullptr;
		tmp.size = 0;
		return *this;
	}

	bool isEmpty() const noexcept{
		return size==0;
	}
	unsigned int numberOfNodes() const noexcept{
		if(isEmpty()) return 0;
		std::queue<TreeNode*> queue;
		queue.push(root);
		unsigned int count{0};
		while(!queue.empty()){
			TreeNode* curr{queue.front()};
			queue.pop();
			++count;
			if(curr->left) queue.push(curr->left);
			if(curr->right) queue.push(curr->right);
		}
		return count;
	}
	long getHeight() const noexcept{
		if(isEmpty()) return -1;
		struct Height{
			TreeNode* node;
			long height;
			Height(TreeNode* node, long height): node{node}, height{height}{}
		};
		std::stack<Height> stack;
		stack.emplace(root, 0);
		long maxHeight{0};
		while(!stack.empty()){
			Height curr(stack.top());
			stack.pop();
			maxHeight = std::max(maxHeight, curr.height);
			if(curr.node->left) stack.emplace(curr.node->left, curr.height+1);
			if(curr.node->right) stack.emplace(curr.node->right, curr.height+1);
		}
		return maxHeight;
	}
	void clear() noexcept{
		deleteNodes(root);
		root = nullptr;
		size = 0;
	}

	void add(int key){
		TreeNode* newNode{new TreeNode(key)};
		if(isEmpty()){
			root = newNode;
		}
		else{
			TreeNode* parentNode{findNode(key, root)};
			if(parentNode->key==key){ // 중복키
				delete newNode;
				return;
			}
			else if(parentNode->key>key){
				parentNode->left = newNode;
			}
			else{
				parentNode->right = newNode;
			}
		}
		++size;
	}

	bool find(int key) const noexcept{
		if(isEmpty()) return false;
		return findNode(key, root)->key==key;
	}

	int next(int key) const{
		if(isEmpty()) throw std::runtime_error("next: empty tree");

		std::stack<TreeNode*> parents;
		TreeNode* curr{findNode(key, root, parents)};

		if(curr->key!=key) throw std::invalid_argument("next: key does not exists");
		if(curr->right){
			curr = curr->right;
			while(curr->left) curr = curr->left;
			return curr->key;
		}
		else{
			while(!parents.empty()){
				TreeNode* parent{parents.top()};
				parents.pop();
				if(parent->key>key) return parent->key;
			}
			return key; // 주어진 키가 BST에서 가장 큰 값
		}
	}

	int prev(int key) const{
		if(isEmpty()) throw std::runtime_error("prev: empty tree");

		std::stack<TreeNode*> parents;
		TreeNode* curr{findNode(key, root, parents)};

		if(curr->key!=key) throw std::invalid_argument("prev: key does not exists");
		if(curr->left){
			curr = curr->left;
			while(curr->right) curr = curr->right;
			return curr->key;
		}
		else{
			while(!parents.empty()){
				TreeNode* parent{parents.top()};
				parents.pop();
				if(parent->key<key) return parent->key;
			}
			return key; // 주어진 키가 BST에서 가장 작은 값
		}
	}

	void remove(int key) noexcept{
		if(isEmpty()) return;

		std::stack<TreeNode*> parents;
		TreeNode* delNode{findNode(key, root, parents)};
		if(delNode->key!=key) return;

		TreeNode* parent{delNode};
		if(delNode->left&&delNode->right){
			TreeNode* prevNode{delNode->left};
			while(prevNode->right){
				parent = prevNode;
				prevNode = prevNode->right;
			}
			delNode->key = prevNode->key;
			delNode = prevNode;
		}
		else{
			parent =  parents.empty()? nullptr: parents.top();
		}
		removeSimpleNode(delNode, parent);
	}

	std::vector<int> rangeSearch(int left, int right) const {
		if(left>right) throw std::invalid_argument("rangeSearch: left>right");
		std::vector<int> result;
		inorderRangeSearch(left, right, root, result);
		return result;
	}

	std::pair<int, int> nearestNeighbor(int key) const noexcept{
		std::pair<int, int> result;

		std::stack<TreeNode*> parents;
		TreeNode* curr{findNode(key, root, parents)};

		if(curr->key==key){ // key가 BST에 존재하는 경우
			result.first = prev(key);
			result.second = next(key);
		}
		else{
			parents.push(curr);
			bool prevFound = false;
			bool nextFound = false;
			while(!parents.empty() && !(nextFound && prevFound)){
				TreeNode* parent{parents.top()};
				parents.pop();
				if(!nextFound && parent->key>key){
					result.second = parent->key;
					nextFound = true;
				}
				else if(!prevFound && parent->key<key){
					result.first = parent->key;
					prevFound = true;
				}
			}
			if(!prevFound) result.first = result.second;
			if(!nextFound) result.second = result.first;
		}
		return result;
	}

	void balanceTree(){
		list.clear();
		inOrder(root);
		clear();
		std::queue<long> queue;
		queue.push(0);
		queue.push(list.size()-1);
		while(!queue.empty()){
			long lo{queue.front()}; queue.pop();
			long hi{queue.front()}; queue.pop();
			if(lo==hi) add(list[lo]);
			else if(lo+1==hi){
				add(list[hi]);
				add(list[lo]);
			}
			else{
				long mid{lo+(hi-lo)/2};
				add(list[mid]);
				queue.push(lo);
				queue.push(mid-1);
				queue.push(mid+1);
				queue.push(hi);
			}
		}
	}

	void setIteratorType(BST::TreeTraversal traversalMethod) noexcept{
		this->traversalMethod = traversalMethod;
	}
	std::vector<int>::iterator begin(){
		list.clear();
		switch(traversalMethod){
		case TreeTraversal::INORDER: inOrder(root); break;
		case TreeTraversal::PREORDER: preOrder(root); break;
		case TreeTraversal::POSTORDER: postOrder(root); break;
		}
		return list.begin();
	}
	std::vector<int>::iterator end(){
		return list.end();
	}
private:
	void deleteNodes(TreeNode* node) noexcept{
		if(isEmpty()) return;
		std::queue<TreeNode*> queue;
		queue.push(root);
		while(!queue.empty()){
			TreeNode* curr{queue.front()};
			queue.pop();
			if(curr->left) queue.push(curr->left);
			if(curr->right) queue.push(curr->right);
			delete curr;
		}
	}

	TreeNode* findNode(int key, TreeNode* currNode) const noexcept{
		TreeNode* parent{nullptr};
		while(currNode){
			if(currNode->key==key) return currNode;
			parent = currNode;
			currNode = (currNode->key>key)? currNode->left: currNode->right;
		}
		return parent;
	}
	TreeNode* findNode(int key, TreeNode* currNode, std::stack<TreeNode*>& parents) const noexcept{
		TreeNode* parent{nullptr};
		while(currNode){
			if(currNode->key==key) return currNode;
			parent = currNode;
			parents.push(parent);
			currNode = (currNode->key>key)? currNode->left: currNode->right;
		}
		return parent;
	}

	// 단말 또는 자식이 하나 있는 노드의 삭제
	void removeSimpleNode(TreeNode* delNode, TreeNode* parent){
		TreeNode* subTree{(delNode->left)? delNode->left: delNode->right};
		if(parent==nullptr) root = subTree;
		else{
			if(parent->key>=delNode->key) parent->left = subTree;
			else parent->right = subTree;
		}
		--size;
		delete delNode;
	}

	void preOrder(TreeNode *node) noexcept{
		std::stack<TreeNode*> stack;
		stack.push(node);
		while(!stack.empty()){
			TreeNode* curr{stack.top()};
			stack.pop();
			list.push_back(curr->key);
			if(curr->right) stack.push(curr->right);
			if(curr->left) stack.push(curr->left);
		}
	}
	void inOrder(TreeNode *node) noexcept{
		std::stack<TreeNode*> stack;
		TreeNode* curr{node};
		while(true){
			while(curr){
				stack.push(curr);
				curr = curr->left;
			}
			if(!stack.empty()){
				TreeNode* top{stack.top()};
				stack.pop();
				list.push_back(top->key);
				curr = top->right;
			}
			else break;
		}
	}
	void postOrder(TreeNode *node) noexcept{
		std::stack<TreeNode*> stack;
		TreeNode* curr{node};
		while(true){
			while(curr){
				if(curr->right) stack.push(curr->right);
				stack.push(curr);
				curr = curr->left;
			}
			if(!stack.empty()){
				TreeNode* top{stack.top()};
				stack.pop();
				if(!stack.empty()&&top->right&&top->right==stack.top()){
					stack.pop();
					stack.push(top);
					curr = top->right;
				}
				else{
					list.push_back(top->key);
					curr = nullptr;
				}
			}
			else break;
		}
	}

	void inorderRangeSearch(int left, int right, TreeNode *node, std::vector<int>& result) const{
		std::stack<TreeNode*> stack;
		TreeNode* curr{node};
		while(true){
			while(curr){
				stack.push(curr);
				curr = curr->left;
			}
			if(!stack.empty()){
				TreeNode* top{stack.top()};
				stack.pop();
				//
				if(top->key>=left&&top->key<=right) result.push_back(top->key);
				else if(top->key>right) return;
				curr = top->right;
			}
			else break;
		}
	}
};

#endif /* BST_H_ */
