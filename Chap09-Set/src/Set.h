/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2020년도 2학기
 * @author 김상진
 * 집합: HashTable을 이용한 구현
 */

#ifndef SET_H_
#define SET_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <list>
#include <iterator>
#include <string>
#include "HashTable.h"


template <typename T>
class Set;

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B);

template <typename T>
class Set {
private:
	HashTable<T> hTable;
public:
	Set() = default;
	Set(const Set<T>& other) = default;
	Set(Set<T>&& other) = default;
	Set<T>& operator=(const Set<T>& other) = default;
	Set<T>& operator=(Set<T>&& other) = default;
	virtual ~Set() = default;
	bool isEmpty() const{
		return hTable.isEmpty();
	}
	bool isFull() const{
		return hTable.isFull();
	}
	int getSize() const{
		return hTable.getSize();
	}
	void add(const T& key){
		hTable.add(key);
	}
	bool contains(const T& key) const{
		return hTable.contains(key);
	}
	void remove(const T& key){
		hTable.remove(key);
	}

	auto begin() { return hTable.begin(); }
	auto end() { return hTable.end(); }
	auto begin() const { return hTable.begin(); }
	auto end() const { return hTable.end(); }

	friend Set<T> operator+<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> operator-<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> intersection<>(const Set<T>& A, const Set<T>& B);
};

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	for(auto s: A) set.add(s);
	for(auto s: B) set.add(s);
	return set;
}

template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	for(auto s: A){
		if(!B.contains(s)) set.add(s);
	}
	return set;
}

template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	for(auto s: A){
		if(B.contains(s)) set.add(s);
	}
	return set;
}


#endif /* SET_H_ */
