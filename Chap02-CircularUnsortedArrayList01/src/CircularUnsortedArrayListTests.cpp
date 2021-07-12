/* 01
 * CircularUnsortedArrayListTests.cpp
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */
#include <string>
#include "gtest/gtest.h"
#include "CircularUnsortedArrayList.h"

TEST(CircularUnsortedArrayList_Duplicate, listEmptyInitializationTest)
{
	CircularUnsortedArrayList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(CircularUnsortedArrayList_Duplicate, PushAndPopBackTest)
{
	CircularUnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.getSize(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");
}


TEST(CircularUnsortedArrayList_Duplicate, PushAndPopFrontTest)
{
	CircularUnsortedArrayList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.pushFront(7);
	ASSERT_EQ(list.getSize(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"7,3,7,5,3,");
}

TEST(CircularUnsortedArrayList_Duplicate, CircularTest)
{
	CircularUnsortedArrayList list{1,2,3,4,5,6,7,8,9,10,};
	ASSERT_TRUE(list.isFull());
	ASSERT_EQ(list.popFront(),1);
	ASSERT_EQ(list.popFront(),2);
	list.pushBack(11);
	list.pushBack(12);
	ASSERT_TRUE(list.isFull());

	std::string output{""};
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,4,5,6,7,8,9,10,11,12,");
}

TEST(CircularUnsortedArrayList_Duplicate, listInitializationTest)
{
	// requires pushBack, popFront
	CircularUnsortedArrayList list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	CircularUnsortedArrayList list2{1,2,3,4,5,6,7,8,9,10,11};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");
}

TEST(CircularUnsortedArrayList_Duplicate, findTest){
	CircularUnsortedArrayList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(CircularUnsortedArrayList_Duplicate, iteratorTest){
	CircularUnsortedArrayList list{1,1,1,1,1,6,7,8,9,10};
	ASSERT_EQ(list.popFront(),1);
	ASSERT_EQ(list.popFront(),1);
	ASSERT_EQ(list.popFront(),1);
	ASSERT_EQ(list.popFront(),1);
	ASSERT_EQ(list.popFront(),1);
	list.pushBack(3);
	list.pushBack(3);
	list.pushBack(3);
	list.pushBack(3);
	list.pushBack(3);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"6,7,8,9,10,3,3,3,3,3,");
}

TEST(CircularUnsortedArrayList_Duplicate, removeFirstTest){
	CircularUnsortedArrayList list{1,6,3,3,3,6,6,1,6,7};
	list.removeFirst(6); // 중간 요소 제거
	ASSERT_EQ(list.getSize(),9);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,3,3,3,6,6,1,6,7,");
	list.removeFirst(1); // 맨 앞 요소 제거
	ASSERT_EQ(list.getSize(),8);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,3,3,6,6,1,6,7,");
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(),7);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,3,3,6,6,1,6,");
	list.removeFirst(3);
	list.removeFirst(6);
	list.removeFirst(3);
	list.removeFirst(6);
	list.removeFirst(3);
	list.removeFirst(6);
	list.removeFirst(1);
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(7);
	list.pushFront(3);
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(3);
	list.removeFirst(7);
	ASSERT_TRUE(list.isEmpty());
}

TEST(CircularUnsortedArrayList_Duplicate, removeAllTest){
	CircularUnsortedArrayList list{1,3,1,1,3,4,5,4,4,6};
	list.removeAll(3);
	ASSERT_EQ(list.getSize(),8);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,1,1,4,5,4,4,6,");
	list.removeAll(1);
	ASSERT_EQ(list.getSize(),5);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,4,4,6,");
	list.removeFirst(5);
	ASSERT_EQ(list.getSize(),4);
	list.removeAll(4);
	ASSERT_EQ(list.getSize(),1);
	ASSERT_EQ(6,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(3);
	list.pushFront(3);
	ASSERT_EQ(list.getSize(),2);
	list.removeAll(3);
	ASSERT_TRUE(list.isEmpty());
}

TEST(CircularUnsortedArrayList_Duplicate, IndexOperator){
	CircularUnsortedArrayList list{10,10,10,10,10,0,1,2,3,4};
	list.removeAll(10);
	list.pushBack(5);
	list.pushBack(6);
	list.pushBack(7);
	list.pushBack(8);
	list.pushBack(9);
	for(int i=0; i<10; i++){
		ASSERT_EQ(list[i], i);
	}
	list[0] = 11;
	ASSERT_EQ(list[0], 11);
	list[9] = 10;
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"11,1,2,3,4,5,6,7,8,10,");
}

TEST(CircularUnsortedArrayList_Duplicate, clearTest){
	CircularUnsortedArrayList list{1,6,3,3,3,6,6,1,6,1,};
	ASSERT_EQ(list.getSize(),10);
	list.clear();
	ASSERT_EQ(list.getSize(),0);
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(4);
	list.pushFront(3);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"4,3,");
	list.clear();
	ASSERT_EQ(list.getSize(),0);
	ASSERT_TRUE(list.isEmpty());
}

TEST(CircularUnsortedArrayList_Duplicate, Big5)
{
	CircularUnsortedArrayList list1{1,2,3,4,5};
	CircularUnsortedArrayList list2{6,7,8,9,10};
	CircularUnsortedArrayList list3;
	CircularUnsortedArrayList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	CircularUnsortedArrayList list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}
