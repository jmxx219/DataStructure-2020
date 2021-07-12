/* 01
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BST.h
 * 이진 검색 트리:
 * 1) 부모에 대한 포인터를 유지하지 않음
 * 2) 재귀적으로 구현
 * 3) 중복을 허용하지 않음
 * 각 메소드 독립적으로
 */

#ifndef BST_H_
#define BST_H_
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <stack>
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
		unsigned int numNodes = numberOfNodes(root);
		assert(numNodes==size);
		return numNodes;
	}
	long getHeight() const noexcept{
		return getHeight(root)-1;
	}
	void clear() noexcept{
		deleteNodes(root);
		root = nullptr;
		size = 0;
	}

	void add(int key){
		TreeNode* newNode{new TreeNode(key)};
		// version 1 (재귀함수)
		root = addNode(newNode, root);

		// version 2
//		if(isEmpty()){
//			root = newNode;
//			++size;
//		}
//		else addNode(newNode, root);
	}

	bool find(int key) const noexcept{
		return findNode(key, root);
	}

	// 재귀 X
	int next(int key) const{
		if(isEmpty()) throw std::runtime_error("next: empty tree");

		TreeNode* curr{root};
		std::stack<TreeNode*> parents;
		bool found{false};
		while(curr!=nullptr){
			if(curr->key==key){
				found = true;
				break;
			}
			parents.push(curr);
			curr = (curr->key>key)? curr->left: curr->right;
		}
		if(!found) throw std::invalid_argument("next: key does not exists");
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

		TreeNode* curr{root};
		std::stack<TreeNode*> parents;
		bool found{false};
		while(curr!=nullptr){
			if(curr->key==key){
				found = true;
				break;
			}
			parents.push(curr);
			curr = (curr->key>key)? curr->left: curr->right;
		}

		if(!found) throw std::invalid_argument("prev: key does not exists");
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
		// version 1
		root = removeNode(key, root);
	}

	/*
	// 방법1: low에 해당하는 값을 찾고, 해당 노드부터 next()함수를 이용하여 high까지 찾아감
	std::vector<int> rangeSearch(int left, int right) const {
		if(left>right) throw std::invalid_argument("rangeSearch: left>right");
		std::vector<int> result;
		if(isEmpty()) return result;

		std::stack<TreeNode*> parents;
		TreeNode* curr{root};
		while(curr!=nullptr){ // left 노드 찾기
			if(curr->key==left) break;
			parents.push(curr);
			curr = (curr->key>left)? curr->left: curr->right;
		}
		int nextKey;
		if(curr){ // 키를 찾았다면
			nextKey = left;
		}
		else{
			bool found = false;
			while(!parents.empty()){
				TreeNode* parent{parents.top()};
				parents.pop();
				if(parent->key>left){
					nextKey = parent->key;
					found = true;
					break;
				}
			}
			// left보다 큰 값이 없으므로 빈 리스트를 반환
			if(!found) return result;
		}
		while(nextKey<=right){
			result.push_back(nextKey);
			nextKey = next(nextKey);
			if(result.back()==nextKey) break;
		}
		return result;
	}
	*/

	// Inorder 이용
	std::vector<int> rangeSearch(int left, int right) const {
		if(left>right) throw std::invalid_argument("rangeSearch: left>right");
		std::vector<int> result;
		inorderRangeSearch(left, right, root, result);
		return result;
	}

	std::pair<int, int> nearestNeighbor(int key) const noexcept{
		std::pair<int, int> result;

		std::stack<TreeNode*> parents;
		TreeNode* curr{root};
		while(curr!=nullptr){
			if(curr->key==key) break;
			parents.push(curr);
			curr = (curr->key>key)? curr->left: curr->right;
		}

		if(curr){ // key가 BST에 존재하는 경우
			result.first = prev(key);
			result.second = next(key);
		}
		else{
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
		balanceTree(0, list.size()-1);
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
	unsigned int numberOfNodes(TreeNode* node) const noexcept{
		if(node==nullptr) return 0;
		else return numberOfNodes(node-> left)+numberOfNodes(node->right)+1;
	}
	long getHeight(TreeNode* node) const noexcept{
		if(node==nullptr) return 0L;
		else return std::max(getHeight(node->left),getHeight(node->right))+1;
	}
	void deleteNodes(TreeNode* node) noexcept{
		if(node==nullptr) return;
		deleteNodes(node->left);
		deleteNodes(node->right);
		delete node;
	}

	// version 1.
	TreeNode* addNode(TreeNode* newNode, TreeNode* currNode){
		if(currNode==nullptr){
			++size;
			return newNode;
		}
		if(currNode->key>newNode->key) currNode->left = addNode(newNode, currNode->left);
		else if(currNode->key<newNode->key) currNode->right = addNode(newNode, currNode->right);
		else delete newNode; // 중복 키는 허용하지 않음
		return currNode;
	}
/*
	// version 2
	void addNode(TreeNode* newNode, TreeNode* currNode){
		if(currNode->key>newNode->key){
			if(currNode->left) addNode(newNode, currNode->left);
			else{
				currNode->left = newNode;
				++size;
			}
		}
		else if(currNode->key<newNode->key){
			if(currNode->right) addNode(newNode, currNode->right);
			else{
				currNode->right = newNode;
				++size;
			}
		}
		else delete newNode; // 중복 키는 허용하지 않음
	}
*/
	bool findNode(int key, TreeNode* currNode) const noexcept{
		if(currNode==nullptr) return false;
		else if(currNode->key==key) return true;
		else if(currNode->key>key) return findNode(key, currNode->left);
		else return findNode(key, currNode->right);
	}

	TreeNode* removeNode(int key, TreeNode* currNode) noexcept{
		if(currNode==nullptr) return currNode;
		if(currNode->key==key) currNode = removeNode(currNode); // 노드 삭제
		else if(currNode->key<key) currNode->right = removeNode(key, currNode->right);
		else currNode->left = removeNode(key, currNode->left);
		return currNode;
	}

	TreeNode* removeNode(TreeNode* delNode) noexcept{
		if(delNode->left&&delNode->right){
			TreeNode* prevNode{delNode->left};
			while(prevNode->right) prevNode = prevNode->right;
			delNode->key = prevNode->key;
			delNode->left = removeNode(prevNode->key, delNode->left);
			return delNode;
		}
		else{
			TreeNode* subTree{delNode->right? delNode->right: delNode->left};
			delete delNode;
			--size;
			return subTree;
		}
	}

	void balanceTree(long lo, long hi){
		if(lo==hi) add(list[lo]);
		else if(lo+1==hi){
			add(list[hi]);
			add(list[lo]);
		}
		else{
			long mid{lo+(hi-lo)/2};
			add(list[mid]);
			balanceTree(lo, mid-1);
			balanceTree(mid+1, hi);
		}
	}

	void preOrder(TreeNode *node) noexcept{
		list.push_back(node->key);
		if(node->left!=nullptr) preOrder(node->left);
		if(node->right!=nullptr) preOrder(node->right);
	}
	void inOrder(TreeNode *node) noexcept{
		if(node->left!=nullptr) inOrder(node->left);
		list.push_back(node->key);
		if(node->right!=nullptr) inOrder(node->right);
	}
	void postOrder(TreeNode *node) noexcept{
		if(node->left!=nullptr) postOrder(node->left);
		if(node->right!=nullptr) postOrder(node->right);
		list.push_back(node->key);
	}

	void inorderRangeSearch(int left, int right, TreeNode *node, std::vector<int>& result) const{
		if(node->left!=nullptr) inorderRangeSearch(left, right, node->left, result);
		if(left<=node->key&&node->key<=right) result.push_back(node->key);
		if(node->key>right) return;
		if(node->right!=nullptr) inorderRangeSearch(left, right, node->right, result);
	}
};

#endif /* BST_H_ */
