 /* 01
 * DoubleUnsortedLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * 이중 연결구조: 정수, 비정렬, 중복 허용, No Tail
 * prev, curr 두 개의 포인터를 이용하여 popBack, removeFirst, removeAll 구현
 * 코드 중복을 제거, dummy 노드 활용
 */

#ifndef DOUBLEUNSORTEDLINKEDLIST_H_
#define DOUBLEUNSORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class DoubleSortedLinkedList {
private:
	// =============================== //
	struct Node{
		int item{0};
		Node* prev{nullptr};
		Node* next{nullptr};
		Node() = default;
		Node(int value, Node* prev=nullptr, Node* next=nullptr) noexcept:
			item{value}, prev{prev}, next{next}{}
		Node(Node* prev, Node* next) noexcept: prev{prev}, next{next}{}
	};
	// =============================== //
	class ListIterator: public std::iterator<std::input_iterator_tag,int>{
		Node *p;
	public:
		explicit ListIterator(Node *p) : p{p} {}
		const ListIterator& operator++() noexcept {
			p = p->next; return *this;
		}
		ListIterator operator++(int) noexcept {
			auto retval = *this; p = p->next; return retval;
		}
		bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
		bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
		int operator*() const noexcept {return p->item;}
	};
	// =============================== //
	Node *head{nullptr};
	unsigned int size{0};

	Node* getTail() const{
		if(isEmpty()) return nullptr;
		Node* tail{head};
		while(tail->next){
			tail = tail->next;
		}
		return tail;
	}

	int& get(int index) const{
		if(index>=0&&index<size){
			Node* curr{head};
			for(int i=0; i<index; i++) curr = curr->next;
			return curr->item;
		}
		else throw std::range_error("get");
	}

	// 사전 조건, curr의 prev는 nullptr이 아님. dummy 사용을 가정함
	void removeNode(Node* curr){
		Node* prev{curr->prev};
		prev->next = curr->next;
		if(curr->next)	curr->next->prev = prev; // 마지막 노드 삭제하는 경우
		delete curr;
		--size;
	}
	void copyList(const DoubleSortedLinkedList& other){
		Node* curr{nullptr};
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(curr==nullptr){
				head = curr = newNode;
			}
			else{
				curr->next = newNode;
				newNode->prev = curr;
				curr = newNode;
			}
			++size;
			src = src->next;
		}
	}

public:
	DoubleSortedLinkedList() = default;
	DoubleSortedLinkedList(const std::initializer_list<int>& initList){
		Node* curr{nullptr};
		for(auto n: initList){
			Node* newNode{new Node{n}};
			if(curr==nullptr){
				head = curr = newNode;
			}
			else{
				curr->next = newNode;
				newNode->prev = curr;
				curr = newNode;
			}
			++size;
		}
	}
	DoubleSortedLinkedList(const DoubleSortedLinkedList& other){
		copyList(other);
	}
	DoubleSortedLinkedList(DoubleSortedLinkedList&& tmp){
		size = tmp.size;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.size = 0;
	}

	virtual ~DoubleSortedLinkedList(){
		clear();
	}

	const DoubleSortedLinkedList& operator=(const DoubleSortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}
	const DoubleSortedLinkedList& operator=(DoubleSortedLinkedList&& tmp){
		clear();
		size = tmp.size;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.size = 0;
		return *this;
	}

	bool isEmpty() const noexcept{
		return head==nullptr;
	}

	bool isFull() const noexcept{
		return false;
	}

	unsigned int getSize() const noexcept{
		return size;
	}

	void clear() noexcept{
		Node* curr{head};
		while(curr){
			Node* delNode{curr};
			curr = curr->next;
			delete delNode;
		}
		size = 0;
		head = nullptr;
	}

	const int& operator[](int index) const{
		return get(index);
	}

	int& operator[](int index){
		return get(index);
	}

	void pushFront(int key){
		Node* newNode{new Node{key}};
		newNode->next = head;
		if(head) head->prev = newNode; // 리스트가 빈 경우
		head = newNode;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		Node* delNode{head};
		int ret{delNode->item};
		head = head->next;
		if(head) head->prev = nullptr; // 노드가 하나밖에 없는 경우 고려
		delete delNode;
		--size;
		return ret;
	}

	void pushBack(int key){
		if(isEmpty()) pushFront(key);
		else{ // 노드가 있으면
			Node* newNode{new Node{key}};
			Node* tail{getTail()};
			newNode->prev = tail;
			tail->next = newNode;
			++size;
		}
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node* tail{getTail()};
		Node* prev{tail->prev};
		if(prev) prev->next = nullptr;
		else head = nullptr;	// 노드가 하나밖에 없는 경우 고려
		--size;
		int ret{tail->item};
		delete tail;
		return ret;
	}
	/*
	//더미 노드를 쓸 경우 -> 더미를 쓰면 더 복잡해짐. 안쓰는 것도 좋은 방법
	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{nullptr, head};
		head->prev = &dummy;
		Node* tail{getTail()};
		Node* prev{tail->prev};
		prev->next = nullptr;
		head = dummy.next;	// 노드가 하나밖에 없는 경우 고려
		if(head) head->prev = nullptr;
		--size;
		int ret{tail->item};
		delete tail;
		return ret;
	}
	*/

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: list is empty");
		return head->item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: list is empty");
		return getTail()->item;
	}

	bool find(int key) const noexcept{
		Node* curr{head};
		while(curr){
			if(curr->item==key) return true;
			curr = curr->next;
		}
		return false;
	}

	void removeFirst(int key) noexcept{
		if(isEmpty()) return;
		Node dummy{nullptr, head};
		head->prev = &dummy;
		Node* curr{head};
		while(curr){
			if(curr->item==key){
				removeNode(curr);
				head = dummy.next;
				if(head) head->prev = nullptr;
				break;
			}
			curr = curr->next;
		}
	}

	void removeAll(int key) noexcept{
		if(isEmpty()) return;
		Node dummy{nullptr, head};
		head->prev = &dummy;
		Node* curr{head};
		while(curr){
			if(curr->item==key){
				Node* next{curr->next};
				removeNode(curr);
				curr = next;
			}
			else curr = curr->next;
		}
		head = dummy.next;
		if(head) head->prev = nullptr;
	}

	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* DOUBLEUNSORTEDLINKEDLIST_H_ */
