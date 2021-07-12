/* 01
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2019년도 2학기
 * Author: 김상진
 * BitVector.h
 * 비트벡터 테스트 프로그램
 */

#include "BitVector.h"
#include "gtest/gtest.h"
#include <string>
#include <random>

std::random_device rd;
std::mt19937_64 mtRand(rd());

int getRandomInt(int n){
	std::uniform_int_distribution<std::int64_t> dist(1,n);
	return dist(mtRand);
}


TEST(BitVectorTest, setTest)
{
	BitVector vector;
	ASSERT_EQ(vector.size, 64);
	ASSERT_EQ(vector.length, 8);
	vector.set(11);
	ASSERT_TRUE(vector.get(11));
	ASSERT_FALSE(vector.get(12));
	vector.set(63);
	ASSERT_TRUE(vector.get(63));
	ASSERT_FALSE(vector.get(62));
	for(int i=0; i<5; i++){
		int x = getRandomInt(64);
		if(!vector.get(x-1)){
			vector.set(x-1);
			ASSERT_TRUE(vector.get(x-1));
		}
	}
}

TEST(BitVectorTest, unSetTest)
{
	BitVector vector;
	ASSERT_EQ(vector.length, 8);
	vector.set(27);
	ASSERT_TRUE(vector.get(27));
	vector.unSet(27);
	ASSERT_FALSE(vector.get(27));
	for(int i=0; i<5; i++){
		int x = getRandomInt(64);
		if(!vector.get(x-1)){
			vector.set(x-1);
			ASSERT_TRUE(vector.get(x-1));
			vector.unSet(x-1);
			ASSERT_FALSE(vector.get(x-1));
		}
	}
}

TEST(BitVectorTest, flipTest)
{
	BitVector vector;
	for(int i=0; i<10; i++){
		int x = getRandomInt(64);
		if(vector.get(x-1)){
			vector.flip(x-1);
			ASSERT_FALSE(vector.get(x-1));
		}
		else{
			vector.flip(x-1);
			ASSERT_TRUE(vector.get(x-1));
		}
	}
}

TEST(BitVectorTest, Big5)
{
	BitVector vector1;
	BitVector vector2;
	for(int i=0; i<10; i++){
		int x = getRandomInt(64);
		vector1.set(x-1);
		x = getRandomInt(64);
		vector2.set(x-1);
	}
	BitVector vector3;
	BitVector vector4(vector2);

	// copy constructor test
	for(int i=0; i<vector2.getSize(); i++)
		ASSERT_EQ(vector2[i], vector4[i]);

	vector3 = vector1;
	// copy assignment test
	for(int i=0; i<vector3.getSize(); i++)
		ASSERT_EQ(vector1[i], vector3.get(i));
	// move constructor test
	BitVector vector5(std::move(vector3));
	for(int i=0; i<vector5.getSize(); i++)
		ASSERT_EQ(vector5[i], vector1[i]);
	// move assignment test
	vector3 = std::move(vector4);
	for(int i=0; i<vector3.getSize(); i++){
		ASSERT_EQ(vector3[i], vector2[i]);
	}

}
