 /* 02
 * UnsortedArrayLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * 배열을 이용한 단일 연결구조: 정수, 비정렬, 중복 허용, 동적 배열, With Tail
 */

#ifndef UNSORTEDARRAYLINKEDLIST_H_
#define UNSORTEDARRAYLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class UnsortedArrayLinkedList {
private:
	// =============================== //
	struct Node{
		int item{0};
		long next{-1};
		Node(int item = -1, int next=-1): item{item}, next{next}{}
	};
	// =============================== //
	class ListIterator: public std::iterator<std::input_iterator_tag,int>{
		Node *list;
		Node *p;
	public:
		explicit ListIterator(Node *list, Node *p) : list{list}, p{p} {}
		const ListIterator& operator++() noexcept {
			p = (p->next == -1) ? nullptr : &list[p->next];
			return *this;
		}
		ListIterator operator++(int) noexcept {
			auto retval = *this;
			p = (p->next == -1) ? nullptr : &list[p->next];
			return retval;
		}
		bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
		bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
		int operator*() const noexcept {return p->item;}
	};
	// =============================== //
	unsigned int capacity{5};
	Node *list{nullptr};
	long head{-1};
	long tail{-1};
	long free{0};
	unsigned int size{0};

	void increaseCapacity(){
		capacity *= 2;
		Node *tmp{new Node[capacity]};
		std::copy(list, list+size, tmp);
		delete [] list;
		list = tmp;
		free = capacity/2;
		for(long i = free; i<capacity-1; i++){
			list[i].next = i+1;
		}
		list[capacity-1].next = -1;
	}

	long getIndex(int index) const{
		if(index>=0&&index<size){
			long curr{head};
			for(int i=0; i<index; i++) curr = list[curr].next;
			return curr;
		}
		else throw std::range_error("get");
	}

	void removeNode(long prev, long curr){
		if(prev==-1) head = list[curr].next;
		else{
			list[prev].next = list[curr].next;
		}
		list[curr].next = free;
		free = curr;
		--size;
	}

public:
	UnsortedArrayLinkedList(unsigned int capacity=5):
		capacity{capacity}, list{new Node[capacity]}{
		for(long i=0; i < capacity -1; i++)
			list[i].next = i+1;
		list[capacity-1].next = -1;
	}

	UnsortedArrayLinkedList(const std::initializer_list<int>& initList):
		UnsortedArrayLinkedList(){
		for(auto it = std::rbegin(initList); it != std::rend(initList); ++it){
			pushFront(*it);
		}
	}
	UnsortedArrayLinkedList(const UnsortedArrayLinkedList& other)
		:capacity{other.capacity}, list{new Node[capacity]},
		 head{other.head}, tail{other.tail}, free{other.free}, size{other.size}{
		std::copy(other.list, other.list+size, list);
	}
	UnsortedArrayLinkedList(UnsortedArrayLinkedList&& tmp):
		capacity{tmp.capacity}, list{tmp.list}, head{tmp.head},
		tail{tmp.tail}, free{tmp.free}, size{tmp.size} {
		tmp.list = nullptr;
	}
	const UnsortedArrayLinkedList& operator=(const UnsortedArrayLinkedList& other){
		head = other.head;
		tail = other.tail;
		free = other.free;
		size = other.size;
		if(list) delete [] list;
		list = new Node[capacity];
		std::copy(other.list, other.list+size, list);

		return *this;
	}
	const UnsortedArrayLinkedList& operator=(UnsortedArrayLinkedList&& tmp) {
		head = tmp.head;
		tail = tmp.tail;
		free = tmp.free;
		size = tmp.size;
		if(list) delete [] list;
		list = tmp.list;
		tmp.list = nullptr;

		return *this;
	}

	virtual ~UnsortedArrayLinkedList(){
		if(list) delete [] list;
	}

	bool isEmpty() const noexcept{
		return head==-1;
	}

	bool isFull() const noexcept{
		return false;
	}

	unsigned int getSize() const noexcept{
		return size;
	}

	void clear(){
		for(int i=0; i < capacity -1; i++)
			list[i].next = i+1;
		list[capacity-1].next = -1;
		head = tail = -1;
		free = 0;
		size = 0;
	}

	const int& operator[](int index) const{
		return list[getIndex(index)].item;
	}

	int& operator[](int index){
		return list[getIndex(index)].item;
	}

	void pushFront(int key){
		if(size == capacity) increaseCapacity();
		long newNodeIndex{free};
		list[newNodeIndex].item = key;

		free = list[free].next;

		list[newNodeIndex].next = head;
		head = newNodeIndex;
		if(size == 0) tail = newNodeIndex;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		long popNode{head};
		int ret{list[popNode].item};
		head = list[head].next;

		list[popNode].next = free;
		free = popNode;

		--size;
		if(size == 0) tail = -1;
		return ret;
	}
/*
	// 해보기
	void pushBack(int key){
		if(isFull()) throw std::runtime_error("pushBack: list is full");
		else if(isEmpty()) pushFront(key);
		else{
			long newNodeIndex{free};
			list[newNodeIndex].item = key;
			free = list[free].next;

			long tailIndex{getTailIndex()};
			list[tailIndex].next = newNodeIndex;
			list[newNodeIndex].next = -1;
			++size;
		}
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		long prev{-1};
		long curr{head};
		while(list[curr].next != -1){
			prev = curr;
			curr = list[curr].next;
		}
		if(prev!= -1) list[prev].next = -1;
		else head = -1;
		int ret{list[curr].item};

		list[curr].next = free;
		free = curr;

		--size;
		return ret;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: list is empty");
		return list[head].item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: list is empty");
		return list[getTailIndex()].item;
	}

	bool find(int key) const noexcept{
		long curr{head};

		while(curr!= -1){
			if(list[curr].item == key) return true;
			curr = list[curr].next;
		}
		return false;
	}

	void removeFirst(int key) noexcept{
		if(isEmpty()) return;
		long prev{-1};
		long curr{head};

		while(curr!=-1){
			if(list[curr].item == key){
				removeNode(prev, curr);
				break;
			}
			prev = curr;
			curr = list[curr].next;
		}
	}

	void removeAll(int key) noexcept{
		if(isEmpty()) return;
		long prev{-1};
		long curr{head};

		while(curr!=-1){
			if(list[curr].item == key){
				long next{list[curr].next};
				removeNode(prev, curr);
				curr = next;
			}
			else{
				prev = curr;
				curr = list[curr].next;
			}

		}
	}
*/
	ListIterator begin() { return ListIterator(list,&list[head]); }
	ListIterator end() { return ListIterator(list, nullptr); }
};

#endif /* UNSORTEDARRAYLINKEDLIST_H_ */
