/* 03
 * SingleSortedLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * 단일 연결구조: 정수, 비정렬, 중복 허용하지 않음, With Tail
 * prev, curr 두 개의 포인터를 이용하여 popBack, remove 구현
 * 코드 중복 제거, dummy 노드 활용
 */

#ifndef SINGLESORTEDLINKEDLIST_H_
#define SINGLESORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleSortedLinkedList {
private:
	// =============================== //
	struct Node{
		int item{0};
		Node* next{nullptr};
		Node() = default;
		Node(int value, Node* next=nullptr): item{value}, next{next}{}
		Node(Node* next): next{next}{}
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

	void removeNode(Node* prev, Node* curr){
		if(curr==tail) tail = (head==curr)? nullptr: prev;
		prev->next = curr->next;
		delete curr;
		--size;
	}

	void copyList(const SingleSortedLinkedList& other){
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
	SingleSortedLinkedList() = default;
	SingleSortedLinkedList(const std::initializer_list<int>& initList){
		for(auto n: initList) add(n);
	}
	SingleSortedLinkedList(const SingleSortedLinkedList& other){
		copyList(other);
	}
	SingleSortedLinkedList(SingleSortedLinkedList&& tmp){
		size = tmp.size;
		head = tmp.head;
		tail = tmp.tail;
		tmp.head = nullptr;
		tmp.size = 0;
	}

	virtual ~SingleSortedLinkedList(){
		clear();
	}

	const SingleSortedLinkedList& operator=(const SingleSortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}
	const SingleSortedLinkedList& operator=(SingleSortedLinkedList&& tmp){
		clear();
		size = tmp.size;
		head = tmp.head;
		tail = tmp.tail;
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

	void add(int key){
		Node* newNode{new Node{key}};
		if(isEmpty()) head = tail = newNode;
		else if(head->item>key){
			newNode->next = head;
			head = newNode;
		}
		else if(tail->item<key){
			tail->next = newNode;
			tail = newNode;
		}
		else{ // 중간 삽입
			if(head->item==key||tail->item==key) return;
			Node* prev{head};
			Node* curr{head->next};
			while(curr&&curr->item<key){
				prev = curr;
				curr = curr->next;
			}
			if(curr&&curr->item==key) return;
			// 맨 처음(head의 변화), 중간, 맨 끝
			prev->next = newNode;
			newNode->next = curr;
		}
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
		tail = prev;
		--size;
		head = dummy.next;
		if(head==nullptr) tail = nullptr;
		int ret{curr->item};
		delete curr;
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
		while(curr&&curr->item<=key){
			if(curr->item==key) return true;
			curr = curr->next;
		}
		return false;
	}

	void remove(int key) noexcept{
		if(isEmpty()) return;
		Node dummy{-1, head};
		Node* prev{&dummy};
		Node* curr{head};
		while(curr&&curr->item<=key){
			if(curr->item==key){
				removeNode(prev, curr);
				head = dummy.next;
				break;
			}
			prev = curr;
			curr = curr->next;
		}
	}

	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* SINGLESORTEDLINKEDLIST_H_ */
