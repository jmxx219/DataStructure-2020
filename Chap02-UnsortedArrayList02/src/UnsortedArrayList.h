/* 02
 * UnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하지 않는 방법으로 pushFront, popFront, removeFrist, removeAll를 구현함
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class UnsortedArrayList {
	class ListIterator: public std::iterator<std::input_iterator_tag,int>{
        int *p;
    public:
        explicit ListIterator(int *p) : p{p} {}
        const ListIterator& operator++() noexcept {++p; return *this;}
        ListIterator operator++(int) noexcept { auto retval = *this; ++p; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        int operator*() const noexcept {return *p;}
    };
private:
	// 검사 목적으로 용량을 작게 설정
	const static unsigned int MAX{10};
	int list[MAX];
	unsigned int size{0};
public:
	explicit UnsortedArrayList() = default;
	explicit UnsortedArrayList(const std::initializer_list<int>& initList){
		size = (initList.size()>MAX)? MAX: initList.size();
		auto it{initList.begin()};
		for(int i=0; i<size; i++){
			list[i] = *it;
			++it;
		}
	}
	virtual ~UnsortedArrayList() = default;

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
		size = 0;
	}

	const int& operator[](int index) const{
		if(index>=0&&index<size) return list[index];
		else throw std::out_of_range("ERROR: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<size) return list[index];
		else throw std::out_of_range("ERROR: []");
	}

	void pushBack(int key){
		if(isFull()) throw std::runtime_error("ERROR: pushBack, isFull");
		list[size] = key;
		++size;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("ERROR: popBack, isEmpty");
		int ret{list[size-1]};
		--size;
		return ret;
	}

	void pushFront(int key){
		if(isFull()) throw std::runtime_error("ERROR: pushFront, isFull");
		list[size] = list[0];
		list[0] = key;
		++size;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("ERROR: popFront, isEmpty");
		int ret{list[0]};
		list[0] = list[size-1];
		--size;
		return ret;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("ERROR: peekFront, isEmpty");
		return list[0];
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("ERROR: peekBack, isEmpty");
		return list[size-1];
	}

	bool find(int key) const noexcept{
		for(int i=0; i<size; i++){
			if(list[i]==key) return true;
		}
		return false;
	}

	void removeFirst(int key) noexcept{
		for(int i=0; i<size; i++){
			if(list[i]==key) {
				list[i] = list[size-1];
				--size;
				break;
			}
		}
	}

	void removeAll(int key) noexcept{
		int i{0};
		while(i<size){
			if(list[i]==key) {
				list[i] = list[size-1];
				--size;
			}
			else ++i;
		}
	}


	ListIterator begin() {return ListIterator(list);}
	ListIterator end() {return ListIterator(list+size);}
};

#endif /* UNSORTEDARRAYLIST_H_ */
