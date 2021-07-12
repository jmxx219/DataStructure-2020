/* 02
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BitVector.h
 * std::vector<bool> 이용
 * 합집합, 차집합, 교집합 구현
 */

#ifndef BITVECTOR_H_
#define BITVECTOR_H_
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>

using Long = uint64_t;

class BitVector{
private:
	std::vector<bool> bitVector;
	Long size;
public:
	explicit BitVector(Long size = 64): size{size}{
		bitVector.resize(size, false);
	}
	bool operator[](Long index) const{
		if(index<size) return bitVector[index];
		else throw std::range_error("ERROR: [] const");
	}
	virtual ~BitVector() = default;
	Long getSize() const{
		return size;
	}
	void set(Long index){
		bitVector[index] = true;
	}
	void unSet(Long index){
		bitVector[index] = false;
	}
	void flip(Long index){
		bitVector[index] = !bitVector[index];
	}

public:
	friend BitVector unionSet(const BitVector& A, const BitVector& B);
	friend BitVector differenceSet(const BitVector& A, const BitVector& B);
	friend BitVector intersectionSet(const BitVector& A, const BitVector& B);
};
//합집합
BitVector unionSet(const BitVector& A, const BitVector& B){
	if(A.size!=B.size) throw std::runtime_error("");
	BitVector tmp{A.size};
	for(int i=0; i<tmp.bitVector.size(); i++){
		tmp.bitVector[i] = A.bitVector[i] || B.bitVector[i];
	}
	return tmp;
}
// 차집합
BitVector differenceSet(const BitVector& A, const BitVector& B){
	if(A.size!=B.size) throw std::runtime_error("");
	BitVector tmp{A.size};
	for(int i=0; i<tmp.bitVector.size(); i++)
		tmp.bitVector[i] = (A.bitVector[i] && !B.bitVector[i]);
	return tmp;
}
//교집합
BitVector intersectionSet(const BitVector& A, const BitVector& B){
	if(A.size!=B.size) throw std::runtime_error("");
	BitVector tmp{A.size};
	for(int i=0; i<tmp.bitVector.size(); i++)
		tmp.bitVector[i] = A.bitVector[i] && B.bitVector[i];
	return tmp;
}

#endif /* BITVECTOR_H_ */
