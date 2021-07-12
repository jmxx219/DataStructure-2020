/* 02
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author: 김상진
 * HashTable.h
 * 용량 고정 단일 버켓, key = 문자열
 * Linear Probing, 해댕 위치 없을 때 delete flag 사용하지 않고 전체 탐색
 * 테스트 프로그램
 */
#include "gtest/gtest.h"
#include "HashTable.h"
#include <string>
#include <set>

TEST(HashTable_LinearProbing, addTest)
{
	HashTable hTable;
	hTable.add("peach"); 	// 1
	hTable.add("grape");	// 6
	hTable.add("orange");	// 5
	ASSERT_EQ(hTable.getSize(), 3);
	ASSERT_TRUE(hTable.contains("peach"));
	ASSERT_FALSE(hTable.contains("melon"));
	hTable.add("kiwi");		// 0
	hTable.add("mango");	// 1
	hTable.add("tomato");	// 2
	hTable.add("melon");	// 3

	//hTable.add("strawberry");	// 2
	//hTable.add("blueberry");	// 6

	ASSERT_EQ(hTable.getSize(), 7);
	ASSERT_FALSE(hTable.contains("strawberry"));
	ASSERT_TRUE(hTable.contains("tomato"));
	ASSERT_TRUE(hTable.contains("melon"));
	//hTable.debugPrint();
}

TEST(HashTable_LinearProbing, removeTest)
{
	HashTable hTable;
	hTable.add("peach");
	hTable.add("mango");
	hTable.add("melon");
	hTable.remove("peach");
	ASSERT_FALSE(hTable.contains("peach"));
	hTable.add("mango");
	ASSERT_EQ(hTable.getSize(), 2);
	hTable.add("peach");
	ASSERT_TRUE(hTable.contains("peach"));
	hTable.add("kiwi");
	hTable.add("strawberry");
	hTable.add("tomato");
	ASSERT_EQ(hTable.getSize(), 6);
	hTable.remove("kiwi");
	ASSERT_EQ(hTable.getSize(), 5);
	ASSERT_TRUE(hTable.contains("tomato"));
	hTable.remove("strawberry");
	hTable.remove("tomato");
	ASSERT_EQ(hTable.getSize(), 3);
	ASSERT_FALSE(hTable.contains("kiwi"));
	ASSERT_FALSE(hTable.contains("strawberry"));
	ASSERT_FALSE(hTable.contains("cocunut"));
}

TEST(HashTable_LinearProbing, iteratorTest)
{
	HashTable hTable;
	std::set<std::string> fruits;
	hTable.add("apple");
	fruits.insert("apple");
	hTable.add("peach");
	fruits.insert("peach");
	hTable.add("grape");
	fruits.insert("grape");
	hTable.add("orange");
	fruits.insert("orange");
	hTable.add("mango");
	fruits.insert("mango");
	hTable.add("coconut");
	fruits.insert("coconut");
	hTable.add("strawberry");
	fruits.insert("strawberry");

	for(auto fruit: hTable){
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
