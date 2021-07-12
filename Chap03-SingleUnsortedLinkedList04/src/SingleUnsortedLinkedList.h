 /* 04
 * SingleUnsortedLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * 단일 연결구조: 정수, 비정렬, 중복 허용, With Tail
 * prev, curr 두 개의 포인터를 이용하여 popBack, removeFirst, removeAll 구현
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
	Node *tail{nullptr};
	unsigned int size{0};

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
		if(curr==tail) tail = (curr==head)? nullptr: prev;
		prev->next = curr->next;
		delete curr;
		--size;
	}

	void copyList(const SingleUnsortedLinkedList& other){
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(tail==nullptr){
				head = tail = newNode;
			}
			else{
				tail->next = newNode;
				tail = newNode;
			}
			++size;
			src = src->next;
		}
	}
public:
	SingleUnsortedLinkedList() = default;
	SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		for(auto n: initList){
			Node* newNode{new Node{n}};
			if(tail==nullptr){
				head = tail = newNode;
			}
			else{
				tail->next = newNode;
				tail = newNode;
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
		tail = tmp.tail;
		tmp.head = tmp.tail = nullptr;
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
		tmp.head = tmp.tail = nullptr;
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
		head = tail = nullptr;
	}

	const int& operator[](int index) const{
		return get(index);
	}

	int& operator[](int index){
		return get(index);
	}

	void pushFront(int key){
		Node* newNode{new Node{key}};
		if(isEmpty()) tail = newNode;
		newNode->next = head;
		head = newNode;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		Node* delNode{head};
		int ret{delNode->item};
		head = head->next;
		if(head==nullptr) tail = nullptr;
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
			tail->next = newNode;
			tail = newNode;
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

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{-1, head};
		Node* prev{&dummy};
		while(prev->next!=tail){
			prev = prev->next;
		} // O(n)
		prev->next = nullptr;
		--size;
		head = dummy.next;
		Node* delNode{tail};
		tail = prev;
		if(head==nullptr) tail = nullptr;
		int ret{delNode->item};
		delete delNode;
		return ret;
	}
	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: list is empty");
		return head->item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: list is empty");
		return tail->item;
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
		Node* curr{head};
		while(curr){
			if(curr->item==key){
				removeNode(prev, curr);
				head = dummy.next;
				break;
			}
			prev = curr;
			curr = curr->next;
		}
	}

	void removeAll(int key) noexcept{
		if(isEmpty()) return;
		Node dummy{-1, head};
		Node* prev{&dummy};
		Node* curr{head};
		while(curr){
			if(curr->item==key){
				removeNode(prev, curr);
				curr = prev->next;
			}
			else{
				prev = curr;
				curr = curr->next;
			}
		}
		head = dummy.next;
	}

	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
