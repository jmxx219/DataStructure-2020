/* 01
 * CircularUnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
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
		int count{0};
	public:
		explicit ListIterator(CircularUnsortedArrayList* L, int *p) : L{L}, p{p} {}
		const ListIterator& operator++() noexcept {
			++p;
			if(p== L->list+MAX) p = L->list;
			return *this;
		}
		ListIterator operator++(int) noexcept {
			auto retval = *this;
			++p;
			if(p== L->list+MAX) p = L->list;
			return retval;}
		bool operator==(const ListIterator& other) noexcept {
			if(!L->isFull()) return p == other.p;
			else{
				if(p==other.p) ++count;
				return (count>=2);
			}
			return p == other.p;
		}
		bool operator!=(const ListIterator& other) noexcept { return !operator==(other); }
		int operator*() const noexcept {return *p;}
	};
	private:
	// 검사 목적으로 용량을 작게 설정
	const static unsigned int MAX{10}; //용량 고정
	int list[MAX];
	unsigned int head{0};
	unsigned int tail{0};
	unsigned int size{0};
	public:
	explicit CircularUnsortedArrayList() = default;
	explicit CircularUnsortedArrayList(const std::initializer_list<int>& initList){
		size = (initList.size()>MAX)? MAX: initList.size();
		tail = size % MAX;
		auto it{initList.begin()};
		for(int i=0; i<size; i++){
			list[i] = *it;
			++it;
		}
	}
	virtual ~CircularUnsortedArrayList() = default;

	bool isEmpty() const noexcept{
		return size==0;
	}
	bool isFull() const noexcept{
		return size==MAX;
	}
	unsigned int getSize() const noexcept{
		return size;
	}
	void clear(){
		size = head = tail = 0;
	}

	const int& operator[](int index) const{
		if(index>=0 && index<size) return list[(head+index) % MAX];
		else throw std::out_of_range("ERROR: [] const");
	}
	int& operator[](int index){
		if(index>=0 && index<size) return list[(head+index) % MAX];
		else throw std::out_of_range("ERROR: []");
	}

	void pushBack(int key){
		if(isFull()) throw std::runtime_error("ERROR: pushBack, isFull");
		list[tail] = key;
		tail = (tail+1)%MAX;
		++size;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("ERROR: popBack, isEmpty");
		tail = (tail+(MAX-1))%MAX;
		// if(tail==0) tail = MAX -1; else --tail;
		int ret{list[tail]};
		--size;
		return ret;
	}

	void pushFront(int key){
		if(isFull()) throw std::runtime_error("ERROR: pushFront, isFull");
		head = (head + (MAX-1)) %MAX;
		list[head] = key;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("ERROR: popFront, isEmpty");
		int ret{list[head]};
		head = (head+1)%MAX;
		--size;
		return ret;
	}

	int peekFront() const {
		if(isEmpty()) throw std::runtime_error("ERROR: peakFront, isEmpty");
		return list[head];
	}
	int peekBack() const {
		if(isEmpty()) throw std::runtime_error("ERROR: peekBack, isEmpty");
		unsigned tmp{(tail+(MAX-1))%MAX};

		return list[tmp];
	}

	bool find(int key) const noexcept{
		unsigned int loc{head};
		for(unsigned i=0; i<size; i++){
			if(list[loc]==key) return true;
			loc = (loc+1)%MAX;
		}
		return false;
	}

	void removeFirst(int key) noexcept{
		unsigned int loc{head};
		for(int i=0; i<size; i++){
			if(list[loc]==key){
				tail = (tail+(MAX-1))%MAX;
				while(loc!=tail){
					unsigned int next{(loc+1)%MAX};
					list[loc] = list[next];
					loc = next;
				}
				--size;
				break;
			}
			loc = (loc+1)%MAX;
		}
	}

	void removeAll(int key) noexcept {
		unsigned int loc{head};
		unsigned int numberOfElement{size};
		for(int i=0; i<numberOfElement; i++){
			if(list[loc]==key){
				tail = (tail+(MAX-1))%MAX;
				unsigned int curr{loc};
				while(curr!=tail){
					unsigned int next{(curr+1)%MAX};
					list[curr] = list[next];
					curr = next;
				}
				--size;
			}
			else loc = (loc+1)%MAX;
		}
	}

	ListIterator begin() {return ListIterator(this, &list[head]);}
	ListIterator end() {return ListIterator(this, &list[tail]);}
};

#endif /* CIRCULARUNSORTEDARRAYLIST_H_ */
