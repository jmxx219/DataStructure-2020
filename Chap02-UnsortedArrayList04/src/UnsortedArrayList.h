/* 04
 * UnsortedArrayList.h
 * 동적 배열, 중복 허용, 배열을 이용한 비정렬 범용 리스트
 * 순서를 유자하는 방법
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

template <typename T>
class UnsortedArrayList {
	class ListIterator: public std::iterator<std::input_iterator_tag,T>{
        T *p;
    public:
        explicit ListIterator(T *p) : p{p} {}
        const ListIterator& operator++() noexcept {++p; return *this;}
        ListIterator operator++(int) noexcept { auto retval = *this; ++p; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        T operator*() const noexcept {return *p;}
    };
private:
	// 검사 목적으로 용량을 작게 설정
	unsigned int capacity{5};
	T *list{nullptr};
	unsigned int size{0};

	void increaseCapacity(){
		capacity *= 2;
		T* tmp{new T[capacity]};
		std::copy(list, list+size, tmp);
		delete [] list;
		list = tmp;
	}
public:
	explicit UnsortedArrayList(unsigned int capacity = 5):
		capacity{capacity}, list{new T[capacity]}{}
	// UnsortedArrayList list{1,2,3,4,5};
	explicit UnsortedArrayList(const std::initializer_list<T>& initList):
		UnsortedArrayList(initList.size()){
		for(auto n: initList) pushBack(n);
	}
	virtual ~UnsortedArrayList() {
		if(list) delete [] list;
	}

	UnsortedArrayList(const UnsortedArrayList& other):
		UnsortedArrayList(other.capacity){
		size = other.size;
		std::copy(other.list, other.list+size, list);
	}

	UnsortedArrayList(UnsortedArrayList&& tmp):
		capacity{tmp.capacity}, size{tmp.size}{
		list = tmp.list;
		tmp.list = nullptr;
		//std::swap(list, tmp.list);
	}

	const UnsortedArrayList& operator=(const UnsortedArrayList& other){
		capacity = other.capacity;
		size = other.size;
		delete [] list;
		list = new T[capacity];
		std::copy(other.list, other.list+size, list);
		return *this;
	}

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

	const T& operator[](int index) const{
		if(index>=0&&index<size) return list[index];
		else throw std::out_of_range("ERROR: [] const");
	}

	T& operator[](int index){
		if(index>=0&&index<size) return list[index];
		else throw std::out_of_range("ERROR: []");
	}

	void pushBack(const T& key){
		if(size==capacity) increaseCapacity();
		list[size] = key;
		++size;
	}

	T popBack(){
		if(isEmpty()) throw std::runtime_error("ERROR: popBack, isEmpty");
		T ret{list[size-1]};
		--size;
		return ret;
	}

	void pushFront(const T& key){
		if(size==capacity) increaseCapacity();
		for(int i=size; i>=1; i--){
			list[i] = list[i-1];
		}
		list[0] = key;
		++size;
	}

	T popFront(){
		if(isEmpty()) throw std::runtime_error("ERROR: popFront, isEmpty");
		T ret{list[0]};
		for(int i=0; i<size-1; i++){
			list[i] = list[i+1];
		}
		--size;
		return ret;
	}

	const T& peekFront() const{
		if(isEmpty()) throw std::runtime_error("ERROR: peekFront, isEmpty");
		return list[0];
	}

	const T& peekBack() const{
		if(isEmpty()) throw std::runtime_error("ERROR: peekBack, isEmpty");
		return list[size-1];
	}

	bool find(const T& key) const noexcept{
		for(int i=0; i<size; i++){
			if(list[i]==key) return true;
		}
		return false;
	}

	void removeFirst(const T& key) noexcept{
		for(int i=0; i<size; i++){
			if(list[i]==key) {
				for(int j=i+1; j<size; j++){
					list[j-1] = list[j];
				}
				--size;
				break;
			}
		}
	}

	// 1 5 3 2
	void removeAll(const T& key) noexcept{
		int i{0};
		while(i<size){
			if(list[i]==key) {
				for(int j=i+1; j<size; j++){
					list[j-1] = list[j];
				}
				--size;
			}
			else ++i;
		}
	}

	ListIterator begin() {return ListIterator(list);}
	ListIterator end() {return ListIterator(list+size);}
};

#endif /* UNSORTEDARRAYLIST_H_ */
