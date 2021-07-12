/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author: 김상진
 * HashTable.h
 * key = 문자열
 * chaining 기법
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <list>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class HashTable {
	unsigned int capacity{7};
	unsigned int size{0};
	std::list<T> **list{nullptr};
	std::vector<T> iteratorList;
public:
	HashTable(int capacity = 7): capacity{7}, list{new std::list<T>*[capacity]{}}{}
	virtual ~HashTable(){
		clear();
	}

	HashTable(const HashTable& other):
		capacity{other.capacity}, size{other.size}, list{new std::list<T>*[capacity]{}}{
		for(int i=0; i<capacity; i++){
			if(other.list[i]) list[i] = new std::list<T>(*other.list[i]);
		}
	}
	HashTable(HashTable&& other):
		capacity{other.capacity}, size{other.size},list{other.list}{
		other.list = nullptr;
	}
	const HashTable& operator=(const HashTable& other) noexcept{
		clear();
		capacity = other.capacity;
		size = other.size;
		list = new std::list<T>*[capacity]{};
		for(int i=0; i<capacity; i++){
			if(other.list[i]) list[i] = new std::list<T>(*other.list[i]);
		}
		iteratorList = other.iteratorList;
		return *this;
	}
	HashTable& operator=(HashTable&& other) noexcept{
		clear();
		capacity = other.capacity;
		size = other.size;
		list = other.list;
		iteratorList = std::move(other.iteratorList);
		other.list = nullptr;
		return *this;
	}

	void clear(){
		if(list){
			for(unsigned int i=0; i<capacity; i++){
				if(list[i]) delete list[i];
			}
			delete [] list;
			list = nullptr;
		}
		size = 0;
		iteratorList.clear();
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
	void add(const T& key){
		unsigned int index{hash(key)};
		if(list[index]){
			if(std::find(list[index]->begin(), list[index]->end(), key)!=list[index]->end()) return;
		}
		else{
			list[index] = new std::list<T>();
		}
		list[index]->push_front(key);
		iteratorList.push_back(key);
		++size;
		if(static_cast<double>(size)/capacity>0.75 || list[index]->size()>2) increaseCapacity();
	}
	bool contains(const T& key) const noexcept{
		if(isEmpty()) return false;
		unsigned int index{hash(key)};
		if(list[index]){
			return std::find(list[index]->begin(), list[index]->end(), key)!=list[index]->end();
		}
		return false;
	}
	void remove(const T& key) noexcept{
		if(isEmpty()) return;
		unsigned int index{hash(key)};
		if(list[index]){
			auto it = std::find(list[index]->begin(), list[index]->end(), key);
			if(it!=list[index]->end()){
				list[index]->erase(it);
				iteratorList.erase(std::find(iteratorList.begin(), iteratorList.end(), key));
				--size;
			}
		}
	}
	void debugPrint(){
		for(unsigned int i=0; i<capacity; i++){
			std::cout << i << ": ";
			if(list[i]==nullptr) std::cout << "empty\n";
			else{
				for(auto key: *list[i])
					std::cout << key << "(" << hash(key) << "), ";
				std::cout << std::endl;
			}
		}
	}

	auto begin(){ return iteratorList.begin(); }
	auto end(){ return iteratorList.end(); }
	auto begin() const { return iteratorList.begin(); }
	auto end() const { return iteratorList.end(); }

private:
	bool isPrime(unsigned int n){
		for(int i=2; i<=static_cast<unsigned int>(std::sqrt(n)); i++){
			if(n%i==0) return false;
		}
		return true;
	}
	unsigned int getNextPrime(){
		unsigned int nextPrime{capacity*2};
		while(!isPrime(nextPrime)) ++nextPrime;
		return nextPrime;
	}
	void increaseCapacity(){
		unsigned int previousCapacity{capacity};
		capacity = getNextPrime();
		std::list<std::string> **tmp{new std::list<T>*[capacity]{}};
		for(unsigned int i=0; i<previousCapacity; i++){
			if(list[i]){
				for(auto key: *list[i]){
					unsigned int index{hash(key)};
					if(!tmp[index]) {
						tmp[index] = new std::list<T>();
					}
					tmp[index]->push_front(key);
				}
				delete list[i];
			}
		}
		delete [] list;
		list = tmp;
	}
	unsigned int hash(const T& key) const noexcept{
		auto hashvalue = std::hash<T>{}(key);
		return hashInteger(static_cast<unsigned int>(hashvalue));
	}
	unsigned int hashInteger(long x) const noexcept{
		constexpr static unsigned long P{4210098769L};
		constexpr unsigned long a{42283};
		constexpr unsigned long b{44267};
		unsigned long value = (a*x + b) % P;
		return static_cast<unsigned int>(value % capacity);
	}
};

#endif /* HASHTABLE_H_ */
