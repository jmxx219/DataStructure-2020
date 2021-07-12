/* 03
 * SingleUnsortedLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * 단일 연결구조: 정수, 비정렬, 중복 허용, No Tail
 * 한 개의 포인터를 이용하여 popBack, removeFirst, removeAll 구현
 * 코드 중복을 제거, dummy 노드를 활용
 */

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleUnsortedLinkedList {
private:
	// =============================== //
	struct Node{
		int item{0};
		Node* next{nullptr};
		Node() = default;
		Node(int value, Node* next=nullptr) noexcept: item{value}, next{next}{}
		Node(Node* next) noexcept: next{next}{}
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

	/*
	void removeNode(Node* prev, Node* curr){
		if(prev==nullptr)
			head = curr->next;
		else prev->next = curr->next;
		delete curr;
		--size;
	}
	 */
	void removeNode(Node* prev, Node* curr){
		prev->next = curr->next;
		delete curr;
		--size;
	}

	void copyList(const SingleUnsortedLinkedList& other){
		Node* curr{nullptr};
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(curr==nullptr){
				head = curr = newNode;
			}
			else{
				curr->next = newNode;
				curr = newNode;
			}
			++size;
			src = src->next;
		}
	}
	public:
	SingleUnsortedLinkedList() = default;
	SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		Node* curr{nullptr};
		for(auto n: initList){
			Node* newNode{new Node{n}};
			if(curr==nullptr){
				head = curr = newNode;
			}
			else{
				curr->next = newNode;
				curr = newNode;
			}
			++size;
		}
	}
	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other){
		copyList(other);
	}
	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& tmp){
		size = tmp.size;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.size = 0;
	}

	virtual ~SingleUnsortedLinkedList(){
		clear();
	}

	const SingleUnsortedLinkedList& operator=(const SingleUnsortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}
	const SingleUnsortedLinkedList& operator=(SingleUnsortedLinkedList&& tmp){
		clear();
		size = tmp.size;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.size = 0;
		return *this;
	}

	bool isEmpty() const noexcept{
		// return size==0;
		return head==nullptr;
	}

	bool isFull() const noexcept{
		return false;
	}

	unsigned int getSize() const noexcept{
		return size;
	}

	void clear(){
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
		head = newNode;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		Node* delNode{head};
		int ret{delNode->item};
		head = head->next;
		delete delNode;
		--size;
		return ret;
	}

	/*
	void pushBack(int key){
		Node* newNode{new Node{key}};
		if(head==nullptr){
			head = newNode;
		}
		else{
			Node* tail{getTail()};
			tail->next = newNode;
		}
		++size;
	}
	 */

	void pushBack(int key){
		if(isEmpty()) pushFront(key);
		else{
			Node* newNode{new Node{key}};
			Node* tail{getTail()};
			tail->next = newNode;
			++size;
		}
	}

	/*
	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node* prev{nullptr};
		Node* curr{head};
		while(curr->next){
			prev = curr;
			curr = curr->next;
		}
		if(prev==nullptr){ // 노드가 하나밖에 없음
			head = nullptr;
		}
		else{
			prev->next = nullptr;
		}
		--size;
		int ret{curr->item};
		delete curr;
		return ret;
	}
	 */

	/*
	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{-1, head};
		Node* prev{&dummy};
		Node* curr{head};
		while(curr->next){
			prev = curr;
			curr = curr->next;
		}
		prev->next = nullptr;
		--size;
		head = dummy.next;
		int ret{curr->item};
		delete curr;
		return ret;
	}
	 */

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{-1, head};
		Node* prev{&dummy};
		while(prev->next->next){
			prev = prev->next;
		}
		Node* tail{prev->next};
		prev->next = nullptr;
		--size;
		head = dummy.next;
		int ret{tail->item};
		delete tail;
		return ret;
	}

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
		Node dummy{-1, head};
		Node* prev{&dummy};
		while(prev->next){
			if(prev->next->item == key){
				prev->next = prev->next->next;
				delete prev->next;
				--size;
				head = dummy.next;
				break;
			}
			prev = prev->next;
		}
	}
	void removeAll(int key) noexcept{
		if(isEmpty()) return;
		Node dummy{-1,head};
		Node* prev{&dummy};
		while(prev->next){
			if(prev->next->item == key){
				prev->next = prev->next->next;
				delete prev->next;
				size--;
			}
			else
				prev = prev->next;
		}
		head = dummy.next;
	}

	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
