/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BinearyHeap.h
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <cmath>

class BinaryHeap {
	class HeapIterator: public std::iterator<std::input_iterator_tag,int>{
        int *p;
    public:
        explicit HeapIterator(int *p): p{p} {}
        const HeapIterator& operator++() {++p; return *this;}
        HeapIterator operator++(int) {HeapIterator retval = *this; ++p; return retval;}
        bool operator==(const HeapIterator& other) const {return p == other.p;}
        bool operator!=(const HeapIterator& other) const {return !(*this == other);}
        int operator*() const {return *p;}
    };
private:
	int capacity; // 2^h-1
	int* heap;
	int size = 0;
	bool needMoreSpace() const{
		return size==capacity;
	}
	void increaseCapacity(){
		capacity = capacity*2+1; // 2^{h+1}-1
		int *tmp{new int[capacity]};
		std::copy(heap, heap+size, tmp);
		delete [] heap;
		heap = tmp;
	}
public:
	BinaryHeap(): capacity{15}, heap{new int[capacity]}{}
	BinaryHeap(std::initializer_list<int> initList): BinaryHeap{}{
		for(auto n: initList) add(n);
	}
	virtual ~BinaryHeap(){
		if(heap) delete [] heap;
	}
	BinaryHeap(const BinaryHeap& other): capacity{other.capacity}, heap{new int[capacity]}, size(other.size){
		std::copy(other.heap, other.heap+size, heap);
	}
	BinaryHeap(BinaryHeap&& tmp): capacity{tmp.capacity}, heap{tmp.heap}, size(tmp.size){
		tmp.heap = nullptr;
	}
	const BinaryHeap& operator=(const BinaryHeap& other){
		capacity = other.capacity;
		size = other.size;
		if(heap) delete [] heap;
		heap = new int[capacity];
		std::copy(other.heap, other.heap+size, heap);
		return *this;
	}
	const BinaryHeap& operator=(BinaryHeap&& tmp){
		capacity = tmp.capacity;
		size = tmp.size;
		if(heap) delete [] heap;
		heap = tmp.heap;
		tmp.heap = nullptr;
		return *this;
	}

	bool isEmpty() const noexcept{
		return size==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	int getSize() const noexcept{
		return size;
	}
	void clear() noexcept{
		size = 0;
	}
	void add(int key) noexcept{
		if(needMoreSpace()) increaseCapacity();
		heap[size] = key;
		reheapUp(size);
		++size;
	}
	int getMax() const{
		if(isEmpty()) throw std::runtime_error("extract Max: heap is empty");
		return heap[0];
	}
	int extractMax(){
		if(isEmpty()) throw std::runtime_error("extract Max: heap is empty");
		int retval{heap[0]};
		std::swap(heap[0], heap[size-1]);
		--size;
		reheapDown(0);
		return retval;
	}
	void changePriority(int index, int key){
		if(isEmpty()) throw std::runtime_error("changePriority: heap is empty");
		if(index<0||index>=size) throw std::range_error("changePriority: illegal index");
		int prevKey{heap[index]};
		heap[index] = key;
		if(prevKey>key) reheapDown(index);
		else reheapUp(index);
	}
	void remove(int index){
		if(isEmpty()) throw std::runtime_error("remove: heap is empty");
		if(index<0||index>=size) throw std::range_error("remove: illegal index");
		if(index==size-1) --size;
		else{
			--size;
			changePriority(index, heap[size]);
		}
	}
	/*
	void remove(int index){
		if(isEmpty()) throw std::runtime_error("remove: heap is empty");
		if(index<0||index>=size) throw std::range_error("remove: illegal index");
		changePriority(index, heap[0]+1);
		extractMax();
	}
	*/
	HeapIterator begin() {return HeapIterator(heap);}
	HeapIterator end() {return HeapIterator(heap+size);}
private:
	void reheapUp(int index){
		int currIndex = index;
		while(currIndex>0){
			int parentIndex{(currIndex-1)/2};
			if(heap[parentIndex]>heap[currIndex]) return;
			else std::swap(heap[parentIndex], heap[currIndex]);
			currIndex = parentIndex;
		}
	}
	void reheapDown(int index){
		int currIndex = index;
		while(currIndex<size){
			int leftChild{2*currIndex+1};
			int rightChild{leftChild+1};
			// 단말노드?
			if(leftChild>=size) return;
			// 왼쪽 자식만 있는 경우
			int maxChild{leftChild};
			// 둘 다 있는 경우
			if(rightChild<size && heap[leftChild]<heap[rightChild])
				maxChild = rightChild;
			if(heap[maxChild]<heap[currIndex]) return;
			else std::swap(heap[maxChild], heap[currIndex]);
			currIndex = maxChild;
		}

	}
};

#endif /* BINARYHEAP_H_ */
