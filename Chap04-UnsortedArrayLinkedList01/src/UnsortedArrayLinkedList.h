 /* 01
 * UnsortedArrayLinkedList.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * 배열을 이용한 단일 연결구조: 정수, 비정렬, 중복 허용, 용량 제한, No Tail
 * 코드 중복을 제거
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
	const static unsigned int MAX_CAPACITY{10};
	Node list[MAX_CAPACITY];
	unsigned int size{0};
	long head{-1};
	long free{0};

	long getIndex(int index) const{
		if(index>=0&&index<size){
			long curr{head};
			for(int i=0; i<index; i++) curr = list[curr].next;
			return curr;
		}
		else throw std::range_error("get");
	}

	long getTailIndex() const{
		long tail{head};
		while(list[tail].next != -1) tail = list[tail].next;
		return tail;
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
	UnsortedArrayLinkedList() noexcept{
		for(int i=0; i < MAX_CAPACITY -1; i++)
			list[i].next = i+1;
		list[MAX_CAPACITY-1].next = -1;
	}

	UnsortedArrayLinkedList(const std::initializer_list<int>& initList):
		UnsortedArrayLinkedList(){
		for(auto it = std::rbegin(initList); it != std::rend(initList); ++it){
			pushFront(*it);
		}
	}

	virtual ~UnsortedArrayLinkedList() = default;

	bool isEmpty() const noexcept{
		// return size==0;
		return head==-1;
	}

	bool isFull() const noexcept{
		return size==MAX_CAPACITY;
	}

	unsigned int getSize() const noexcept{
		return size;
	}

	void clear(){
		for(int i=0; i < MAX_CAPACITY -1; i++)
			list[i].next = i+1;
		list[MAX_CAPACITY-1].next = -1;
		head = -1;
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
		if(isFull()) throw std::runtime_error("pushFront: list is full");
		long newNodeIndex{free};
		list[newNodeIndex].item = key;

		free = list[free].next;

		list[newNodeIndex].next = head;
		head = newNodeIndex;
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
		return ret;
	}

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

	ListIterator begin() { return ListIterator(list,&list[head]); }
	ListIterator end() { return ListIterator(list, nullptr); }
};

#endif /* UNSORTEDARRAYLINKEDLIST_H_ */
