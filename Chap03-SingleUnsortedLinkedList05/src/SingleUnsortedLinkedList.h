 /* 05
 * SingleUnsortedLinkedList.h
 * �ѱ�����������б� ��ǻ�Ͱ��к� �ڷᱸ���׽ǽ�
 * @version 2020�⵵ 2�б�
 * @author �����
 * ���� ���ᱸ��: ����, ������, �ߺ� ���, No Tail
 * prev, curr �� ���� �����͸� �̿��Ͽ� popBack, removeFirst, removeAll ����
 * �ڵ� �ߺ��� ����, dummy ��带 Ȱ��
 */

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

template <typename T>
class SingleUnsortedLinkedList {
private:
	// =============================== //
	struct Node{
		T item{};
		Node* next{nullptr};
		Node() = default;
		Node(const T& value, Node* next=nullptr) noexcept: item{value}, next{next}{}
		Node(Node* next) noexcept: next{next}{}
	};
	// =============================== //
	class ListIterator: public std::iterator<std::input_iterator_tag,T>{
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
		T& operator*() const noexcept {return p->item;}
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

	T& get(int index) const{
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
	SingleUnsortedLinkedList(const std::initializer_list<T>& initList){
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

	const T& operator[](int index) const{
		return get(index);
	}

	T& operator[](int index){
		return get(index);
	}

	void pushFront(const T& key){
		Node* newNode{new Node{key}};
		newNode->next = head;
		head = newNode;
		++size;
	}

	T popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: list is empty");
		Node* delNode{head};
		T ret{delNode->item};
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

	void pushBack(const T& key){
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
		if(prev==nullptr){ // ��尡 �ϳ��ۿ� ����
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

	T popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: list is empty");
		Node dummy{head};
		Node* prev{&dummy};
		Node* curr{head};
		while(curr->next){
			prev = curr;
			curr = curr->next;
		}
		prev->next = nullptr;
		--size;
		head = dummy.next;
		T ret{curr->item};
		delete curr;
		return ret;
	}
	const T& peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: list is empty");
		return head->item;
	}

	const T& peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: list is empty");
		return getTail()->item;
	}

	bool find(const T& key) const noexcept{
		Node* curr{head};
		while(curr){
			if(curr->item==key) return true;
			curr = curr->next;
		}
		return false;
	}

	void removeFirst(const T& key) noexcept{
		if(isEmpty()) return;
		Node dummy{head};
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

	void removeAll(const T& key) noexcept{
		if(isEmpty()) return;
		Node dummy{head};
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
