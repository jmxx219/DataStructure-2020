/* 01
 * UnsortedArrayList.h
 * 동적 배열, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하는 방법
 * in-place로 removeAll 구현
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <iostream>
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
		unsigned int capacity{5}; //용량 고정
		int *list{nullptr};
		unsigned int size{0};

		void increaseCapacity(){
			capacity *= 2;
			int* tmp{new int[capacity]};
			std::copy(list, list+size, tmp);
			delete [] list;
			list = tmp;
		}
	public:
		explicit UnsortedArrayList(unsigned int capacity = 5):
			capacity{capacity}, list{new int[capacity]} {};
		explicit UnsortedArrayList(const std::initializer_list<int>& initList):
			UnsortedArrayList(initList.size()){
				for(auto n: initList) pushBack(n);
		}
	virtual ~UnsortedArrayList(){
		if(list) delete [] list;
	}

	//복사생성자
	UnsortedArrayList(const UnsortedArrayList& other):
		UnsortedArrayList(other.capacity){
		size = other.size;
		std::copy(other.list, other.list+size, list);
	}

	//이동생성자
	UnsortedArrayList(UnsortedArrayList&& tmp):
		capacity{tmp.capacity}, size{tmp.size} {
		list = tmp.list;
		tmp.list = nullptr;
		//std::swap(list, tmp.list);
	}

	//복사대입연산자
	const UnsortedArrayList& operator=(const UnsortedArrayList& other){
		capacity = other.capacity;
		size = other.size;
		delete [] list;
		list = new int[capacity];
		std::copy(other.list, other.list+size, list);

		return *this;
	}

	//이동대입연산자
	const UnsortedArrayList& operator=(UnsortedArrayList&& tmp){
		capacity = tmp.capacity;
		size = tmp.size;
		delete [] list;
		list = tmp.list;
		tmp.list = nullptr;

		return *this;
	}

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
		size = 0;
	}

	const int& operator[](int index) const{
		if(index>=0 && index<size) return list[index];
		else throw std::out_of_range("ERROR: [] const");
	}
	int& operator[](int index){
		if(index>=0 && index<size) return list[index];
		else throw std::out_of_range("ERROR: []");
	}

	void pushBack(int key){
		if(size == capacity) increaseCapacity();
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
		for(int i = size; i >= 1; i--){
			list[i] = list[i-1];
		}
		list[0] = key;
		++size;
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

	int peekFront() const {
		if(isEmpty()) throw std::runtime_error("ERROR: peakFront, isEmpty");
		return list[0];
	}
	int peekBack() const {
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
			if(list[i]==key){
				for(int j=i+1; j<size; j++){
					list[j-1] = list[j];
				}
				--size;
				break;
			}
		}
	}
	// 삭제할 키를 만날 때마다 그 뒤에 있는 요소를 모두 옮기지 X -> in-place로 구현
	void removeAll(int key) noexcept {
		int keyCount = 0; //key의 개수 구하기
		for(int i=0; i<size; i++){
			if(list[i] == key){
				keyCount++;
			}
			else{
				list[i-keyCount] = list[i]; //
			}
		}
		size -= keyCount;
	}
	//Input: [0,1,0,3,12]
	//Output: [1,3,12,0,0]
	/*
	void moveZeroes() {
		int cnt{0};
		for(int i=0; i<size; i++){
			if (list[i] != 0){
				list[cnt++] = list[i];
			}
		}
		while (cnt < size)
			list[cnt++] = 0;
	}
	*/
	void moveZeroes() {
		int cnt{0};
		for(int i=0; i<size; i++){
			if(list[i] == 0){
				cnt++;
			}
			else{
				list[i-cnt] = list[i]; //
			}
		}
		while (cnt < size)
			list[++cnt] = 0;
	}

	ListIterator begin() {return ListIterator(list);}
	ListIterator end() {return ListIterator(list+size);}
};

#endif /* UNSORTEDARRAYLIST_H_ */
