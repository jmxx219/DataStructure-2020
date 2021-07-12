/* 02
 * SortedArrayList.h
 * 용량 고정, 중복 허용하지 않음, 배열을 이용한 정렬 정수 리스트
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */

#ifndef SORTEDARRAYLIST_H_
#define SORTEDARRAYLIST_H_
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SortedArrayList {
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

	unsigned int search(int key) const noexcept{
		long low{0};	// low = 0, high = 7, mid = 3;
		long high{size-1};
		while(low<=high){
			long mid{low+(high-low)/2};	//overflow
			if(list[mid]==key) return mid;
			else if(list[mid]>key) high = mid - 1;
			else low = mid + 1;
		}
		return low;
	}

public:
	explicit SortedArrayList() = default;
	explicit SortedArrayList(const std::initializer_list<int>& initList){
		unsigned int numberOfElements = (initList.size()>MAX)? MAX: initList.size();
		auto it{initList.begin()};
		for(int i=0; i<numberOfElements; i++){
			add(*it);
			++it;
		}
	}
	virtual ~SortedArrayList() = default;

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

	/*
	//순차탐색 -> 앞에서부터
	void add(int key){
		if(isFull()) throw std::runtime_error("ERROR: add, isFull");
		if(isEmpty() || list[size-1] <= key){
			list[size] = key;
		}
		else{
			for(int i=0; i<size; i++){
				if(list[i] > key){
					for(int j = size-1; j>=i; j--){
						list[j+1] = list[j];
					}
					list[i] = key;
					break;
				}
			}
		}
		++size;
	}

	//순차탐색 -> 뒤에서부터
	void add(int key){
		if(isFull()) throw std::runtime_error("ERROR: add, isFull");
		if(isEmpty() || list[size-1] <= key){
			list[size] = key;
		}
		else{
			long i{size-1};
			while(i>=0 && key<list[i]){
				list[i+1] = list[i];
				--i;
			}
			list[++i] = key;
		}
		++size;
	}
	*/

	//이진탐색
	void add(int key){
		if(isFull()) throw std::runtime_error("ERROR: add, isFull");
		if(isEmpty() || list[size-1] < key){
			list[size] = key;
		}
		else{
			long int index{search(key)};
			if(list[index]==key) return;
			for(long j=size-1; j>=index; j--){
				list[j+1] = list[j];
			}
			list[index] = key;
		}
		++size;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("ERROR: popBack, isEmpty");
		int ret{list[size-1]};
		--size;
		return ret;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("ERROR: popFront, isEmpty");
		int ret{list[0]};
		for(int i=0; i<size-1; i++){
			list[i] = list[i+1];
		}
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

	//순차검색
//	bool find(int key) const noexcept{
//		for(int i = 0; i < size; i++){
//			if(list[i] == key) return true;
//		}
//		return false;
//	}

	//이진검색
	bool find(int key) const noexcept{
		if(isEmpty()) return false;
		return list[search(key)] == key;
	}

	void remove(int key) noexcept{
		if(isEmpty()) return;
		long index{search(key)};
		if(list[index] == key){
			for(int j = index+1; j < size; j++){
				list[j-1] = list[j];
			}
			--size;
		}
	}

	ListIterator begin() {return ListIterator(list);}
	ListIterator end() {return ListIterator(list+size);}
};

#endif /* SORTEDARRAYLIST_H_ */
