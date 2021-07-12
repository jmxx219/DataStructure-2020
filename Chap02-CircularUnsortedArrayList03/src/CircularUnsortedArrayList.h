/* 03
 * CircularUnsortedArrayList.h
 * 동적 배열, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 공간 하나를 사용하지 않고 구현함
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */

#ifndef CIRCULARUNSORTEDARRAYLIST_H_
#define CIRCULARUNSORTEDARRAYLIST_H_
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class CircularUnsortedArrayList {
	class ListIterator: public std::iterator<std::input_iterator_tag,int>{
		CircularUnsortedArrayList* L;
		int *p;
	public:
		explicit ListIterator(CircularUnsortedArrayList* L, int *p) : L{L}, p{p} {}
		const ListIterator& operator++() noexcept {
			++p;
			if(p== L->list + L->capacity) p = L->list;
			return *this;
		}
		ListIterator operator++(int) noexcept {
			auto retval = *this;
			++p;
			if(p== L->list + L->capacity) p = L->list;
			return retval;}
		bool operator==(const ListIterator& other) noexcept { return p == other.p; }
		bool operator!=(const ListIterator& other) noexcept { return !operator==(other); }
		int operator*() const noexcept {return *p;}
	};
private:
	// 검사 목적으로 용량을 작게 설정
	unsigned int capacity{10};
	int* list{nullptr};
	unsigned int head{0};
	unsigned int tail{0};
	unsigned int size{0};

	void increaseCapacity(){
		int *tmp{new int[capacity*2]};
		for(int i=0; i<size; i++){
			tmp[i] = list[head];
			head = (head+1)%capacity;
		}
		capacity *= 2;
		head = 0;
		tail = size;
		if(list) delete [] list;
		list = tmp;
	}
public:
	explicit CircularUnsortedArrayList(unsigned int capacity = 10):
		capacity{capacity}, list{new int[capacity]} {}
	explicit CircularUnsortedArrayList(const std::initializer_list<int>& initList):
		CircularUnsortedArrayList(initList.size()+1){
		auto it{initList.begin()};
		for(int i=0; i<initList.size(); i++){
			list[i] = *it;
			++it;
		}
		size = initList.size();
		tail = size;
	}
	//복사생성자
	CircularUnsortedArrayList(const CircularUnsortedArrayList& other):
		CircularUnsortedArrayList(other.capacity){
		/*
		head = other.head;
		tail = other.tail;
		size = other.size;
		std::copy(other.list, other.list+capacity, list);
		*/
		size = other.size;
		unsigned int loc{other.head};
		for(int i=0; i<size; i++){
			list[i] = other.list[loc];
			loc = (loc+1) % other.capacity;
		}
		head = 0;
		tail = size;

	}
	//이동생성자
	CircularUnsortedArrayList(CircularUnsortedArrayList&& tmp){
		capacity = tmp.capacity;
		head = tmp.head;
		tail = tmp.tail;
		size = tmp.size;
		list = tmp.list;
		tmp.list = nullptr;
	}
	//복사대입연산자
	const CircularUnsortedArrayList& operator=(const CircularUnsortedArrayList& other){
		capacity = other.capacity;
		head = other.head;
		tail = other.tail;
		size = other.size;
		if(list) delete [] list;
		list = new int[capacity];
		std::copy(other.list, other.list+capacity, list);
		return *this;
	}
	//이동대입 연산자
	const CircularUnsortedArrayList& operator=(CircularUnsortedArrayList&& tmp){
		capacity = tmp.capacity;
		head = tmp.head;
		tail = tmp.tail;
		size = tmp.size;
		delete [] list;
		list = tmp.list;
		tmp.list = nullptr;

		return *this;
	}

	virtual ~CircularUnsortedArrayList() = default;

	bool isEmpty() const noexcept{
		return size==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	unsigned int getSize() const noexcept{
		return size;
	}
	void clear(){
		size = head = tail = 0;
	}

	const int& operator[](int index) const{
		if(index>=0 && index<size) return list[(head+index) % capacity];
		else throw std::out_of_range("ERROR: [] const");
	}
	int& operator[](int index){
		if(index>=0 && index<size) return list[(head+index) % capacity];
		else throw std::out_of_range("ERROR: []");
	}

	void pushBack(int key){
		if(size==capacity-1) increaseCapacity();
		list[tail] = key;
		tail = (tail+1)%capacity;
		++size;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("ERROR: popBack, isEmpty");
		tail = (tail+(capacity-1))%capacity;
		// if(tail==0) tail = MAX -1; else --tail;

		int ret{list[tail]};
		--size;
		return ret;
	}

	void pushFront(int key){
		if(size==capacity-1) increaseCapacity();
		head = (head + (capacity-1)) %capacity;
		list[head] = key;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("ERROR: popFront, isEmpty");
		int ret{list[head]};
		head = (head+1)%capacity;
		--size;
		return ret;
	}

	int peekFront() const {
		if(isEmpty()) throw std::runtime_error("ERROR: peakFront, isEmpty");
		return list[head];
	}
	int peekBack() const {
		if(isEmpty()) throw std::runtime_error("ERROR: peekBack, isEmpty");
		unsigned tmp{(tail+(capacity-1))%capacity};

		return list[tmp];
	}

	bool find(int key) const noexcept{
		unsigned int loc{head};
		for(unsigned i=0; i<size; i++){
			if(list[loc]==key) return true;
			loc = (loc+1)%capacity;
		}
		return false;
	}

	void removeFirst(int key) noexcept{
		unsigned int loc{head};
		for(int i=0; i<size; i++){
			if(list[loc]==key){
				tail = (tail+(capacity-1))%capacity;
				while(loc!=tail){
					unsigned int next{(loc+1)%capacity};
					list[loc] = list[next];
					loc = next;
				}
				--size;
				break;
			}
			loc = (loc+1)%capacity;
		}
	}

	void removeAll(int key) noexcept {
		unsigned int loc{head};
		unsigned int numberOfElement{size};
		for(int i=0; i<numberOfElement; i++){
			if(list[loc]==key){
				tail = (tail+(capacity-1))%capacity;
				unsigned int curr{loc};
				while(curr!=tail){
					unsigned int next{(curr+1)%capacity};
					list[curr] = list[next];
					curr = next;
				}
				--size;
			}
			else loc = (loc+1)%capacity;
		}
	}

	ListIterator begin() {return ListIterator(this, &list[head]);}
	ListIterator end() {return ListIterator(this, &list[tail]);}
};

#endif /* CIRCULARUNSORTEDARRAYLIST_H_ */
