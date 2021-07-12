/* 02 - 동적할당
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author: 2019136072 손지민
 * HashTable.h
 * 동적 할당 단일 버켓, key = 문자열
 * Linear Probing(+1), delete flag 사용 (열린 기법)
 */
/*
 * 열린 기법(선형조사 +1)의 해싱 (실습자료실 09에 포함된) Chap09-Hashing02 버전을 동적 배열 기법을 사용하도록 수정하세요.
 * 데이터를 삽입할 때마다 load factor((삽입된 요소 개수)/(해시 테이블 용량))를 계산하여 이 factor가 0.75 이상이면 배열의 용량을 확대하는 버전을 만들어야 합니다.
 * 이때 용량은 기존 용량의 2배보다는 크도록 만들어야 합니다.
 * 간단하게는 2*capacity+1을 사용할 수 있고, 2*capacity보다 큰 소수를 선택하도록 만들 수 있습니다.
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <string>
#include <vector>

class HashTable {
	enum class BucketState {EMPTY, OCCUPIED, DELETED};
	struct Bucket{
		std::string key;
		BucketState currentState{BucketState::EMPTY};
	};
	std::vector<std::string> iteratorList;
	unsigned int capacity{11};
	Bucket *list{nullptr};
	unsigned int size{0};
public:
	HashTable(int capacity = 11): capacity{11}, list{new Bucket[capacity]{}}{}
	virtual ~HashTable(){
		clear();
	}

	HashTable(const HashTable& other):
		capacity{other.capacity}, size{other.size}, list{new Bucket[capacity]}{
			std::copy(other.list, other.list+size, list);
		}
	HashTable(HashTable&& tmp):
		capacity{tmp.capacity}, size{tmp.size},list{tmp.list}{
		tmp.list = nullptr;
	}
	const HashTable& operator=(const HashTable& other){
		clear();
		capacity = other.capacity;
		size = other.size;
		list = new Bucket[capacity];
		std::copy(other.list, other.list+size, list);
		return *this;
	}
	const HashTable& operator=(HashTable&& tmp){
		clear();
		capacity = tmp.capacity;
		size = tmp.size;
		delete [] list;
		list = tmp.list;
		tmp.list = nullptr;
		return *this;
	}

	void clear(){
		delete [] list;
		list = nullptr;
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
	void add(const std::string& key){
		if(isFull()) throw std::runtime_error("HashTable Full: add");
		long deletedIndex{-1};
		unsigned int index{hashString(key)};
		for(unsigned int i=0; i<capacity; i++){
			// 중복된 키는 허용하지 않음
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key) return;
			else if(list[index].currentState==BucketState::DELETED&&deletedIndex==-1){
				deletedIndex = index;
			}
			else if(list[index].currentState==BucketState::EMPTY){
				deletedIndex = index;
				break;
			}
			index = (index+1)%capacity;
		}
		list[deletedIndex].key = key;
		list[deletedIndex].currentState = BucketState::OCCUPIED;
		++size;
		// std::cout<< "size: " <<size << std::endl;
		//(삽입된 요소 개수)/(해시 테이블 용량)가 0.75 이상이면 배열의 용량을 확대
		if(static_cast<double>(size)/capacity>=0.75) increaseCapacity();
	}
	bool contains(const std::string& key) const noexcept{
		if(isEmpty()) return false;
		std::cout << "searching: " << key;
		unsigned int index{hashString(key)};
		int count{1};
		for(unsigned int i=0; i<capacity; i++){
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key){
				std::cout << "> " << count << " > found \n";
				return true;
			}
			else if(list[index].currentState==BucketState::EMPTY){
				std::cout << "> " << count <<  " > failed\n";
				return false;
			}
			++count;
			index = (index+1)%capacity;
		}
		std::cout << "> " << count-1 <<  " > failed\n";
		return false;
	}
	void remove(const std::string& key) noexcept{
		if(isEmpty()) return;
		unsigned int index{hashString(key)};
		for(unsigned int i=0; i<capacity; i++){
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key){
				list[index].currentState = BucketState::DELETED;
				--size;
				return;
			}
			else if(list[index].currentState==BucketState::EMPTY) return;
			index = (index+1)%capacity;
		}
	}
	void debugPrint(){
		for(unsigned int i=0; i<capacity; i++){
			std::cout << i << ": ";
			if(list[i].currentState==BucketState::OCCUPIED){
				std::cout << list[i].key << " > "<< hashString(list[i].key) <<'\n';
			}
			else{
				std::cout << (list[i].currentState==BucketState::EMPTY? "empty\n": "deleted\n");

			}
		}
	}
	std::vector<std::string>::iterator begin(){
		iteratorList.clear();
		for(unsigned int i=0; i<capacity; i++){
			iteratorList.push_back(list[i].key);
		}
		return iteratorList.begin();
	}
	std::vector<std::string>::iterator end(){
		return iteratorList.end();
	}
private:
	void increaseCapacity(){
		//std::cout << "capacity이전: "<< capacity << std::endl;
		unsigned int previousCapacity{capacity};
		capacity = 2*capacity+1;
		//std::cout << "capacity이후: "<< capacity << std::endl;
		//std::cout << "으아 용량 증가 했슴돠아ㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏ\n";
		Bucket* tmp{new Bucket[capacity]};
		for(unsigned int i=0; i<previousCapacity; i++){
			unsigned int index{hashString(list[i].key)};
			tmp[index].key = list[i].key;
			tmp[index].currentState = list[i].currentState;
		}
		delete list;
		list = tmp;
	}
	unsigned int hashString(const std::string& key) const noexcept{
		constexpr static unsigned long P{13875551L};
		constexpr unsigned long x{62057};
		unsigned long value{0};
		for(long i{static_cast<long>(key.length())-1}; i>=0; i--)
			value = (value*x+static_cast<long>(key[i]))%P;
		return hashInteger(static_cast<unsigned int>(value));
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
