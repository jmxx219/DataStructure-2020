/* 01
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BitVector.h
 */

#ifndef BITVECTOR_H_
#define BITVECTOR_H_
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cstdint>

using Byte = uint8_t;
using Long = uint64_t;

class BitVector{
public:
	const Long size;
	const Long length;
	// bitMask[i]는 1 바이트의 i번째 비트만 1인 바이트 값
	const Byte bitMasks[8] = {
		(Byte)128, (Byte)64, (Byte)32, (Byte)16, (Byte)8, (Byte)4, (Byte)2, (Byte)1,
	}; // 1000 0000
private:
	/*
	 *  비트 백터: 0000 0000 0000 0000
	 *  색인    : 0123 4567 89
	 *  예) 색인 10: 0000 1010
	 *  byteIndex: 10/8 = 0x1010>>3 = 0x0001 = 1
	 *  bitIndex:  10%8 = 0x1010 & 0x0111 = 0x0010 = 2
	 *  bitMask = 32 = 0010 0000
	 */
	Byte* vector{nullptr};
public:
	explicit BitVector(unsigned int size = 64):
		size{size}, length{size/8}, vector{new Byte[length]{}}{}
	virtual ~BitVector(){
		if(vector) delete [] vector;
	}
	BitVector(const BitVector& other): BitVector(other.size){
		std::copy(other.vector, other.vector+length, vector);
	}
	BitVector(BitVector&& tmp):
		size{tmp.size}, length{tmp.length}, vector{tmp.vector}{
		tmp.vector = nullptr;
	}
	const BitVector& operator=(const BitVector& other){
		if(size!=other.size) throw std::runtime_error("");
		std::copy(other.vector, other.vector+length, vector);
		return *this;
	}
	const BitVector& operator=(BitVector&& tmp){
		if(size!=tmp.size) throw std::runtime_error("");
		if(vector) delete [] vector;
		vector = tmp.vector;
		tmp.vector = nullptr;
		return *this;
	}
	Long getSize() const noexcept{
		return size;
	}

	bool operator[](int index) const{
		return get(index);
	}

	// 특정 비트만 1로 변경: OR, xx1x xxxx = aaaa aaaa | 0010 0000
	void set(Long index){
		Long byteIndex{getByteNumber(index)};
		//Byte bitmask = 0x80 >> (index&0x07);
		//vector[byteIndex] |= bitmask;

		vector[byteIndex] |= bitMasks[index&0x07];
	}
	// 특정 비트만 0으로 변경: AND, xx0x xxxx = aaaa aaaa & 1101 1111
	void unSet(Long index){
		Long byteIndex{getByteNumber(index)};
		//Byte unMask = (0x80 >> (index&0x07)) ^ (Byte)0xFF; // 0010 0000 ^ 1111 1111 = 1101 1111
		//vector[byteIndex] &= unMask;

		vector[byteIndex] &= (bitMasks[index&0x07]^(Byte)0xFF);
	}
	// 특정 비트만 뒤집기: XOR, xxyx xxxx = aaaa aaaa ^ 0010 00000
	void flip(Long index){
		Long byteIndex{getByteNumber(index)};
		//Byte bitmask = 0x80 >> (index&0x07);
		//vector[byteIndex] ^= bitmask;

		vector[byteIndex] ^= bitMasks[index&0x07];
	}
	// 해당 비트가 1이면 true 아니면 false
	// computedMask는 해당 비트값만 유지하고 나머지는 0
	bool get(Long index) const{
		Long byteIndex{getByteNumber(index)};
		Byte bitmask = 0x80 >> (index&0x07);
		Byte computedMask = vector[byteIndex] & bitmask;  // xxax xxxx & 0010 0000 = 00a0 0000
		return computedMask!=(Byte)0; // 0이 아니면 true
	}
private:
	Long getByteNumber(Long index) const{
		if(index>=size) throw std::range_error("색인 범위 초과");
		index = index >> 3;
		return index;
	}
};


#endif /* BITVECTOR_H_ */
