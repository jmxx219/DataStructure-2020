/* 02
 * SortedArrayListTests.cpp
 * 용량 고정, 중복 허용하지 않음, 배열을 이용한 비정렬 정수 리스트
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */
#include <string>
#include "gtest/gtest.h"
#include "SortedArrayList.h"


TEST(SortedArrayListWithDuplicate, listEmptyInitializationTest)
{
	SortedArrayList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SortedArrayListWithDuplicate, addfindTest){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.add(9);
	list.add(9); // 3, 3, 5, 7, 9, 9
	ASSERT_EQ(list.getSize(),4);
	std::string output = "";
	for(auto n: list){
		output += std::to_string(n)+",";
	}
	ASSERT_EQ(output,"3,5,7,9,");

	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SortedArrayListWithDuplicate, popTest)
{
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	ASSERT_EQ(list.getSize(),3);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"7,5,3,");
	ASSERT_TRUE(list.isEmpty());

	list.add(5);
	list.add(5);
	ASSERT_EQ(list.getSize(),1);
	list.add(3);
	list.add(7);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SortedArrayListWithDuplicate, listInitializationTest)
{
	// requires pushBack, popFront
	SortedArrayList list1{3,5,7};
	list1.add(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	SortedArrayList list2{1,11,2,7,8,5,6,3,4,9,10,};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,11,");
}

TEST(SortedArrayListWithDuplicate, removeTest){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(6);
	list.add(9);
	list.remove(3);
	ASSERT_EQ(list.getSize(),3);
	list.remove(9);
	ASSERT_EQ(list.getSize(),2);
	list.remove(6);
	ASSERT_EQ(list.getSize(),1);
	ASSERT_EQ(5,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.add(7);
	list.add(3);
	list.add(5);
	ASSERT_EQ(list.getSize(),3);
	list.remove(5);
	list.remove(3);
	list.remove(7);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayListWithDuplicate, iteratorTest){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SortedArrayListWithDuplicate, IndexOperator){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	ASSERT_EQ(list[1], 5);
	list.add(7);
	//list[0] = 4;
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SortedArrayListWithDuplicate, clearTest){
	SortedArrayList list{1,3,1,1,3,4,5,4,4,6};
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	list.add(4);
	ASSERT_EQ(list.getSize(),1);
	ASSERT_EQ(4,list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayListWithDuplicate, Big5)
{
	SortedArrayList list1{1,2,3,4,5};
	SortedArrayList list2{6,7,8,9,10};
	SortedArrayList list3;
	SortedArrayList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SortedArrayList list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

