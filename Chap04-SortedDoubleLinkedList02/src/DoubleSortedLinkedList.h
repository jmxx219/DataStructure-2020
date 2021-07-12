 /* 01
 * DoubleSortedLinkedList.h
 * �ѱ�����������б� ��ǻ�Ͱ��к� �ڷᱸ���׽ǽ�
 * @version 2020�⵵ 2�б�
 * @author 2019136072 ������
 * ���� ���ᱸ��: ����, ����, �ߺ� ���, With Tail
 * prev, curr �� ���� �����͸� �̿��Ͽ� popBack, removeFirst, removeAll ����
 * �ڵ� �ߺ��� ����, dummy ��� Ȱ��
 */

#ifndef DOUBLESORTEDLINKEDLIST_H_
#define DOUBLESORTEDLINKEDLIST_H_
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

	// ���� ����, curr�� prev�� nullptr�� �ƴ�. dummy ����� ������
	void removeNode(Node* curr){
		Node* prev{curr->prev};
		if(curr==tail) tail = (curr==head) ? nullptr: prev;
		prev->next = curr->next;
		if(curr->next)	curr->next->prev = prev; // ������ ��� �����ϴ� ���
		delete curr;
		--size;
	}

	void copyList(const DoubleSortedLinkedList& other){
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(tail==nullptr){
				head = tail = newNode;
			}
			else{
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
			++size;
			src = src->next;
		}
	}

public:
	DoubleSortedLinkedList() = default;
	DoubleSortedLinkedList(const std::initializer_list<int>& initList){
		for(auto n: initList) add(n);
	}
	DoubleSortedLinkedList(const DoubleSortedLinkedList& other){
		copyList(other);
	}
	DoubleSortedLinkedList(DoubleSortedLinkedList&& tmp){
		size = tmp.size;
		head = tmp.head;
		tail = tmp.tail;
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

	void clear() noexcept{
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

	void add(int key){
		Node* newNode{new Node{key}};
		if(isEmpty()){
			head = tail = newNode;
		}
		else if(key<= head->item){
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		else if(key>= tail->item){
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		else {
			Node* curr{head->next};
			while(curr){
				if(key<= curr->item){
					// ���� �߿����� ����
					curr->prev->next = newNode;
					newNode->prev = curr->prev;
					newNode->next = curr;
					curr->prev = newNode;
					break;
				}
				curr = curr->next;
			}
		}
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		Node* delNode{head};
		int ret{delNode->item};
		head = head->next;
		if(head) head->prev = nullptr;
		else tail = nullptr;	// ��尡 �ϳ��ۿ� ���� ��� ���
		delete delNode;
		--size;
		return ret;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		int ret{tail->item};
		Node* prev{tail->prev};
		delete tail;
		if(prev) {
			prev->next = nullptr;
			tail = prev;
		}
		else head = tail = nullptr;	// ��尡 �ϳ��ۿ� ���� ��� ���
		--size;
		return ret;
	}
	/*
	//���� ��带 �� ��� -> ���̸� ���� �� ��������. �Ⱦ��� �͵� ���� ���
	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{nullptr, head};
		head->prev = &dummy;
		Node* tail{getTail()};
		Node* prev{tail->prev};
		prev->next = nullptr;
		head = dummy.next;	// ��尡 �ϳ��ۿ� ���� ��� ���
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
			else if(curr->item > key) break;	//�߰�
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
				removeNode(curr);
			}
			else if(curr->item > key) break;	//�߰�
			curr = curr->next;
		}
		head = dummy.next;
		if(head) head->prev = nullptr;
	}

	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* DOUBLESORTEDLINKEDLIST_H_ */
