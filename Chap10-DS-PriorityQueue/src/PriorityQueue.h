/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BinearyHeap.h
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include "BinaryHeap.h"

class PriorityQueue{
private:
	BinaryHeap heap;
public:
	PriorityQueue() = default;
	PriorityQueue(std::initializer_list<int> initList): heap{initList}{}
	virtual ~PriorityQueue() = default;
	PriorityQueue(const PriorityQueue& other) = default;
	PriorityQueue(PriorityQueue&& tmp) = default;
	PriorityQueue& operator=(const PriorityQueue& other) = default;
	PriorityQueue& operator=(PriorityQueue&& tmp) = default;
	bool isEmpty() const noexcept{
		return heap.isEmpty();
	}
	bool isFull() const noexcept{
		return heap.isFull();
	}
	int getSize() const noexcept{
		return heap.getSize();
	}
	void clear() noexcept{
		heap.clear();
	}
	void enqueue(int key) noexcept{
		heap.add(key);
	}
	int dequeue(){
		return heap.extractMax();
	}
	int peek() const{
		return heap.getMax();
	}
	auto begin() {return heap.begin();}
	auto end() {return heap.end();}
};

#endif /* PRIORITYQUEUE_H_ */
