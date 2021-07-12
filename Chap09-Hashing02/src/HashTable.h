/* 02
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author: 김상진
 * HashTable.h
 * 용량 고정 단일 버켓, key = 문자열
 * Linear Probing(+1), delete flag 사용 (열린 기법)
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <string>

class HashTable {
	enum class BucketState {EMPTY, OCCUPIED, DELETED};
	struct Bucket{
		std::string key;
		BucketState currentState{BucketState::EMPTY};
	};
	class TableIterator: public std::iterator<std::input_iterator_tag,std::string>{
        Bucket *p;
        Bucket *end;
    public:
        explicit TableIterator(Bucket *p) : p{p}, end{p+MAX} {}
        const TableIterator& operator++() noexcept {
        	++p;
        	while(p->currentState!=BucketState::OCCUPIED&&p!=end) ++p;
        	return *this;
        }
        TableIterator operator++(int) noexcept {
        	TableIterator retval(*this);
        	while(p->currentState!=BucketState::OCCUPIED&&p!=end) ++p;
        	return retval;
        }
        bool operator==(const TableIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const TableIterator& other) const noexcept {return !(p == other.p);}
        const std::string& operator*() const noexcept {
        	return p->key;
        }
    };
private:
	const static unsigned int MAX{11};
	Bucket list[MAX];
	unsigned int size{0};
public:
	HashTable() = default;
	virtual ~HashTable() = default;
	bool isEmpty() const noexcept{
		return size==0;
	}
	bool isFull() const noexcept{
		return size==MAX;
	}
	unsigned int getSize() const noexcept{
		return size;
	}
	void add(const std::string& key){
		if(isFull()) throw std::runtime_error("HashTable Full: add");
		long deletedIndex{-1};
		unsigned int index{hashString(key)};
		for(unsigned int i=0; i<MAX; i++){
			// 중복된 키는 허용하지 않음
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key) return;
			else if(list[index].currentState==BucketState::DELETED&&deletedIndex==-1){
				deletedIndex = index;
			}
			else if(list[index].currentState==BucketState::EMPTY){
				deletedIndex = index;
				break;
			}
			index = (index+1)%MAX;
		}
		list[deletedIndex].key = key;
		list[deletedIndex].currentState = BucketState::OCCUPIED;
		++size;
	}
	bool contains(const std::string& key) const noexcept{
		if(isEmpty()) return false;
		std::cout << "searching: " << key;
		unsigned int index{hashString(key)};
		int count{1};
		for(unsigned int i=0; i<MAX; i++){
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key){
				std::cout << "> " << count << " > found \n";
				return true;
			}
			else if(list[index].currentState==BucketState::EMPTY){
				std::cout << "> " << count <<  " > failed\n";
				return false;
			}
			++count;
			index = (index+1)%MAX;
		}
		std::cout << "> " << count-1 <<  " > failed\n";
		return false;
	}
	void remove(const std::string& key) noexcept{
		if(isEmpty()) return;
		unsigned int index{hashString(key)};
		for(unsigned int i=0; i<MAX; i++){
			if(list[index].currentState==BucketState::OCCUPIED && list[index].key==key){
				list[index].currentState = BucketState::DELETED;
				--size;
				return;
			}
			else if(list[index].currentState==BucketState::EMPTY) return;
			index = (index+1)%MAX;
		}
	}
	void debugPrint(){
		for(unsigned int i=0; i<MAX; i++){
			std::cout << i << ": ";
			if(list[i].currentState==BucketState::OCCUPIED){
				std::cout << list[i].key << " > "<< hashString(list[i].key) <<'\n';
			}
			else{
				std::cout << (list[i].currentState==BucketState::EMPTY? "empty\n": "deleted\n");

			}
		}
	}
	TableIterator begin() {return TableIterator(list);}
	TableIterator end() {return TableIterator(list+MAX);}
private:
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
		return static_cast<unsigned int>(value % MAX);
	}
};

#endif /* HASHTABLE_H_ */
