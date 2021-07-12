/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author: 김상진
 * HashMap.h
 * key = 문자열
 * chaining 기법
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <list>
#include <unordered_set>
#include <string>
#include <vector>
#include <utility>
#include <functional>

template <typename K, typename V>
class HashMap {
	using Pair = std::pair<K,V>;
	using List = std::list<Pair>;
	unsigned int capacity{7};
	unsigned int size{0};
	List **list{nullptr};
	std::vector<Pair> entryList;

public:
	HashMap(int capacity = 7): capacity{7}, list{new List*[capacity]{}}{}
	virtual ~HashMap(){
		clear();
	}

	HashMap(const HashMap& other):
		capacity{other.capacity}, size{other.size}, list{new List*[capacity]{}}{
		for(int i=0; i<capacity; i++){
			if(other.list[i]) list[i] = new List(*other.list[i]);
		}
	}
	HashMap(HashMap&& other):
		capacity{other.capacity}, size{other.size},list{other.list}{
		other.list = nullptr;
	}
	const HashMap& operator=(const HashMap& other) noexcept{
		clear();
		capacity = other.capacity;
		size = other.size;
		list = new List*[capacity]{};
		for(int i=0; i<capacity; i++){
			if(other.list[i]) list[i] = new List(*other.list[i]);
		}
		return *this;
	}
	HashMap& operator=(HashMap&& other) noexcept{
		clear();
		capacity = other.capacity;
		size = other.size;
		list = other.list;
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
	void put(const K& key, const V& value){
		unsigned int index{hash(key)};
		bool found{false};
		if(list[index]){
			for(auto it = list[index]->begin(); it!=list[index]->end(); ++it){
				if(it->first==key){
					it->second = value;
					found = true;
					break;
				}
			}
		}
		else{
			list[index] = new List();
		}
		if(!found) list[index]->emplace_front(key,value);
		++size;
		if(static_cast<double>(size)/capacity>0.75 || list[index]->size()>2) increaseCapacity();
	}
	bool containsKey(const K& key) const noexcept{
		if(isEmpty()) return false;
		unsigned int index{hash(key)};
		if(list[index]){
			for(auto it = list[index]->begin(); it!=list[index]->end(); ++it){
				if(it->first==key){
					return true;
				}
			}
		}
		return false;
	}
	const V& get(const K& key) const{
		if(isEmpty()) throw std::runtime_error("HashMap: get, empty");
		unsigned int index{hash(key)};
		if(list[index]){
			for(auto it = list[index]->begin(); it!=list[index]->end(); ++it){
				if(it->first==key){
					return it->second;
				}
			}
		}
		throw std::runtime_error("HashMap: get, key does not exists");
	}
	void remove(const K& key) noexcept{
		if(isEmpty()) return;
		unsigned int index{hash(key)};
		if(list[index]){
			for(auto it = list[index]->begin(); it!=list[index]->end(); ++it){
				if(it->first==key){
					list[index]->erase(it);
					--size;
					break;
				}
			}
		}
	}

	std::unordered_set<K> getKeySet() const noexcept{
		std::unordered_set<K> set(getNextPrime());
		for(int i=0; i<capacity; i++){
			if(list[i]){
				for(auto entry: *list[i]) set.insert(entry.first);
			}
		}
		return set;
	}
	std::unordered_set<V> getValueSet() const noexcept{
		std::unordered_set<V> set(getNextPrime());
		for(int i=0; i<capacity; i++){
			if(list[i]){
				for(auto entry: *list[i]) set.insert(entry.second);
			}
		}
		return set;
	}

	void debugPrint(){
		for(unsigned int i=0; i<capacity; i++){
			std::cout << i << ": ";
			if(list[i]==nullptr) std::cout << "empty\n";
			else{
				for(auto entry: *list[i])
					std::cout << entry.first << ": " << entry.second << "(" << hash(entry.first) << "), ";
				std::cout << std::endl;
			}
		}
	}

	typename std::vector<Pair>::iterator begin(){
		entryList.clear();
		for(unsigned int i=0; i<capacity; i++){
			if(list[i]){
				for(auto entry: *list[i])
					entryList.push_back(entry);
			}
		}
		return entryList.begin();
	}
	typename std::vector<Pair>::iterator end(){
		return entryList.end();
	}
private:
	bool isPrime(unsigned int n) const{
		for(int i=2; i<=static_cast<unsigned int>(std::sqrt(n)); i++){
			if(n%i==0) return false;
		}
		return true;
	}
	unsigned int getNextPrime() const{
		unsigned int nextPrime{capacity*2};
		while(!isPrime(nextPrime)) ++nextPrime;
		return nextPrime;
	}
	void increaseCapacity(){
		unsigned int previousCapacity{capacity};
		capacity = getNextPrime();
		List **tmp{new List*[capacity]{}};
		for(unsigned int i=0; i<previousCapacity; i++){
			if(list[i]){
				for(auto entry: *list[i]){
					unsigned int index{hash(entry.first)};
					if(!tmp[index]) {
						tmp[index] = new List();
					}
					tmp[index]->push_front(entry);
				}
				delete list[i];
			}
		}
		delete [] list;
		list = tmp;
	}
	unsigned int hash(const K& key) const noexcept{
		auto hashvalue = std::hash<K>{}(key);
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

#endif /* HASHMAP_H_ */
