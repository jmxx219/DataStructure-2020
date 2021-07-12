/* 04 - parent
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * BST.h
 * 이진 검색 트리:
 * 1) 부모에 대한 포인터를 유지
 * 2) 재귀적으로 구현
 * 3) 중복을 허용하지 않음
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
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int key = -1, TreeNode* parent = nullptr,
			TreeNode* left = nullptr, TreeNode* right = nullptr):
			key{key}, parent{parent}, left{left}, right{right}{}
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
		if(isEmpty()) root = newNode;
		else{
			TreeNode* parentNode{findNode(key, root)};
			if(parentNode->key==key){ // 중복키
				delete newNode;
				return;
			}
			else if(parentNode->key>key) parentNode->left = newNode;
			else parentNode->right = newNode;
			newNode->parent = parentNode; // 추가
		}
		++size;
	}

	bool find(int key) const noexcept{
		if(isEmpty()) return false;
		return findNode(key, root)->key==key;
	}

	int next(int key) const{
		if(isEmpty()) throw std::runtime_error("next: empty tree");

		TreeNode* curr{findNode(key, root)};

		if(curr->key!=key) throw std::invalid_argument("next: key does not exists");
		if(curr->right){
			curr = curr->right;
			while(curr->left) curr = curr->left;
			return curr->key;
		}
		else{
			while(curr->parent){
				curr = curr->parent;
				if(curr->key>key) return curr->key;
			}
			return key; // 주어진 키가 BST에서 가장 큰 값
		}
	}

	int prev(int key) const{
		if(isEmpty()) throw std::runtime_error("prev: empty tree");

		TreeNode* curr{findNode(key, root)};

		if(curr->key!=key) throw std::invalid_argument("prev: key does not exists");
		if(curr->left){
			curr = curr->left;
			while(curr->right) curr = curr->right;
			return curr->key;
		}
		else{
			while(curr->parent){
				curr = curr->parent;
				if(curr->key<key) return curr->key;
			}
			return key; // 주어진 키가 BST에서 가장 작은 값
		}
	}

	void remove(int key) noexcept{
		if(isEmpty()) return;
		TreeNode* delNode{findNode(key, root)};
		if(delNode->key!=key) return;

		if(delNode->left&&delNode->right){
			TreeNode* prevNode{delNode->left};
			while(prevNode->right){
				prevNode = prevNode->right;
			}
			delNode->key = prevNode->key;
			delNode = prevNode;
		}
		removeSimpleNode(delNode);
	}

	std::vector<int> rangeSearch(int left, int right) const {
		if(left>right) throw std::invalid_argument("rangeSearch: left>right");
		std::vector<int> result;
		inorderRangeSearch(left, right, root, result);
		return result;
	}

	std::pair<int, int> nearestNeighbor(int key) const noexcept{
		std::pair<int, int> result;

		TreeNode* curr{findNode(key, root)};

		if(curr->key==key){ // key가 BST에 존재하는 경우
			result.first = prev(key);
			result.second = next(key);
		}
		else{
			bool prevFound = false;
			bool nextFound = false;
			while(curr && !(nextFound && prevFound)){
				if(!nextFound && curr->key>key){
					result.second = curr->key;
					nextFound = true;
				}
				else if(!prevFound && curr->key<key){
					result.first = curr->key;
					prevFound = true;
				}
				curr = curr->parent;
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
		else return numberOfNodes(node->left)+numberOfNodes(node->right)+1;
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

	TreeNode* findNode(int key, TreeNode* currNode) const noexcept{
		if(currNode->key==key) return currNode;
		TreeNode* nextNode{(currNode->key>key)? currNode->left: currNode->right};
		return nextNode? findNode(key, nextNode): currNode;
	}

	// 단말 또는 자식이 하나 있는 노드의 삭제
	void removeSimpleNode(TreeNode* delNode){
		TreeNode* subTree{(delNode->left)? delNode->left: delNode->right};
		if(delNode->parent==nullptr){
			root = subTree;
			if(subTree) subTree->parent = nullptr;
		}
		else{
			TreeNode* parent{delNode->parent};
			if(parent->key>=delNode->key) parent->left = subTree;
			else parent->right = subTree;
			if(subTree) subTree->parent = parent;
		}
		--size;
		delete delNode;
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
