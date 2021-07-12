/* 04
 * UnsortedArrayListTests.cpp
 * 동적 배열, 중복 허용, 배열을 이용한 범용 비정렬 리스트
 * Copyright: 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * Version: 2020년도 2학기
 * Author: 손지민 2019136072
 */
#include <iostream>
#include <string>
#include <utility>
#include "UnsortedArrayList.h"
#include "gtest/gtest.h"


TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, listEmptyInitializationTest)
{
	UnsortedArrayList<int> list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());

	UnsortedArrayList<std::string> list2{};
	ASSERT_EQ(list2.getSize(), 0);
	ASSERT_TRUE(list2.isEmpty());
	ASSERT_FALSE(list2.isFull());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushAndPopBackTest)
{
	UnsortedArrayList<int> list1;
	list1.pushBack(3);
	list1.pushBack(5);
	list1.pushBack(7);
	list1.pushBack(3);
	ASSERT_EQ(list1.getSize(),4);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");

	UnsortedArrayList<std::string> list2;
	list2.pushBack("apple");
	list2.pushBack("banana");
	list2.pushBack("grape");
	list2.pushBack("apple");
	ASSERT_EQ(list2.getSize(),4);
	output = "";
	while(!list2.isEmpty())
		output += list2.popBack()+",";
	ASSERT_EQ(output,"apple,grape,banana,apple,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushAndPopFrontTest)
{
	UnsortedArrayList<int> list1;
	list1.pushFront(3);
	list1.pushFront(5);
	list1.pushFront(7);
	list1.pushFront(3);
	list1.pushFront(7);
	ASSERT_EQ(list1.getSize(),5);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"7,3,7,5,3,");

	UnsortedArrayList<std::string> list2;
	list2.pushBack("apple");
	list2.pushBack("banana");
	list2.pushBack("grape");
	list2.pushBack("apple");
	ASSERT_EQ(list2.getSize(),4);
	output = "";
	while(!list2.isEmpty())
		output += list2.popBack()+",";
	ASSERT_EQ(output,"apple,grape,banana,apple,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, listInitializationTest)
{
	// requires pushBack, popFront
	UnsortedArrayList<std::string> list1{"apple","banana","grape"};
	std::string output = "";
	while(!list1.isEmpty())
		output += list1.popFront()+",";
	ASSERT_EQ(output,"apple,banana,grape,");

	UnsortedArrayList<int> list2{1,2,3,4,5,6,7,8,9,10,11};
	list2.pushBack(12);
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,11,12,");

	// dynamic array test
	// cannot use list3{2}
	UnsortedArrayList<int> list3(2);	// capacity = 2
	list3.pushBack(1);
	list3.pushBack(2);
	list3.pushBack(3);
	list3.pushBack(4);
	list3.pushBack(5);
	list3.pushBack(6);
	list3.pushBack(7);
	list3.pushBack(8);
	list3.pushBack(9);
	output = "";
	while(!list3.isEmpty())
		output += std::to_string(list3.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, findTest){
	UnsortedArrayList<int> list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));

	UnsortedArrayList<std::string> list2{"apple","banana","apple","grape","mango"};
	ASSERT_TRUE(list2.find("apple"));
	ASSERT_TRUE(list2.find("banana"));
	ASSERT_TRUE(list2.find("grape"));
	ASSERT_TRUE(list2.find("mango"));
	ASSERT_FALSE(list2.find("kiwi"));
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, removeFirstTest){
	UnsortedArrayList<int> list1;
	list1.pushBack(3);
	list1.pushBack(5);
	list1.pushBack(7);
	list1.removeFirst(3);
	ASSERT_EQ(list1.getSize(),2);
	list1.removeFirst(7);
	ASSERT_EQ(list1.getSize(),1);
	ASSERT_EQ(5,list1.popFront());
	ASSERT_TRUE(list1.isEmpty());
	list1.pushFront(3);
	list1.pushBack(5);
	ASSERT_EQ(list1.getSize(),2);
	list1.removeFirst(5);
	list1.removeFirst(3);
	ASSERT_TRUE(list1.isEmpty());

	UnsortedArrayList<std::string> list2;
	list2.pushBack("apple");
	list2.pushBack("grape");
	list2.pushBack("mango");
	list2.removeFirst("mango");
	ASSERT_EQ(list2.getSize(),2);
	list2.removeFirst("apple");
	ASSERT_EQ(list2.getSize(),1);
	ASSERT_EQ(list2.popFront(),"grape");
	ASSERT_TRUE(list2.isEmpty());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, removeAllTest){
	UnsortedArrayList<int> list1{1,3,1,6,3,4,5,4,4,1};
	list1.removeAll(3);
	ASSERT_EQ(list1.getSize(),8);
	list1.removeAll(1);
	ASSERT_EQ(list1.getSize(),5);
	list1.removeFirst(5);
	ASSERT_EQ(list1.getSize(),4);
	list1.removeAll(4);
	ASSERT_EQ(list1.getSize(),1);
	ASSERT_EQ(6,list1.popFront());
	ASSERT_TRUE(list1.isEmpty());
	list1.pushFront(3);
	list1.pushFront(3);
	list1.pushBack(3);
	ASSERT_EQ(list1.getSize(),3);
	list1.removeAll(3);
	ASSERT_TRUE(list1.isEmpty());

	UnsortedArrayList<std::string> list2{"apple","apple","banana","grape","banana",
		"grape","kiwi","apple","banana","apple"};
	list2.removeAll("apple");
	ASSERT_EQ(list2.getSize(),6);
	list2.removeAll("banana");
	ASSERT_EQ(list2.getSize(),3);
	list2.removeFirst("kiwi");
	ASSERT_EQ(list2.getSize(),2);
	list2.removeAll("grape");
	ASSERT_TRUE(list2.isEmpty());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, iteratorTest){
	UnsortedArrayList<int> list1;
	list1.pushBack(3);
	list1.pushBack(5);
	list1.pushBack(7);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");

	UnsortedArrayList<std::string> list2;
	list2.pushBack("apple");
	list2.pushBack("grape");
	list2.pushBack("mango");
	output = "";
	for(std::string s: list2)
		output += s+",";
	ASSERT_EQ(output,"apple,grape,mango,");
	ASSERT_EQ(list2.getSize(),3);
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, IndexOperator){
	UnsortedArrayList<int> list;
	list.pushBack(3);
	list.pushBack(5);
	ASSERT_EQ(list[1], 5);
	list.pushBack(7);
	list[0] = 4;
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,7,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, copyProblem)
{
	UnsortedArrayList<std::string> list{"apple", "grape", "banana"};
	std::string fruit{"mango"};
	list.pushBack(fruit);
	fruit[0] = 'M';
	std::string output = "";
	for(auto s: list)
		output += s+",";
	ASSERT_EQ(output,"apple,grape,banana,mango,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, clearTest){
	UnsortedArrayList<int> list1{1,3,1,1,3,4,5,4,4,6};
	list1.clear();
	ASSERT_TRUE(list1.isEmpty());
	list1.pushBack(4);
	ASSERT_EQ(list1.getSize(),1);
	ASSERT_EQ(4,list1.popFront());
	ASSERT_TRUE(list1.isEmpty());

	UnsortedArrayList<std::string> list2{"apple","mango","kiwi","banana","melon"};
	list2.clear();
	list2.pushBack("strawberry");
	ASSERT_EQ(list2.getSize(),1);
	ASSERT_EQ("strawberry", list2.popFront());
	ASSERT_TRUE(list2.isEmpty());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, Big5_intTest)
{
	UnsortedArrayList<int> list1{1,2,3,4,5};
	UnsortedArrayList<int> list2{6,7,8,9,10};
	UnsortedArrayList<int> list3;
	UnsortedArrayList<int> list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	UnsortedArrayList<int> list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, Big5_stringTest)
{
	UnsortedArrayList<std::string> list1{"apple","mango","kiwi","banana","melon"};
	UnsortedArrayList<std::string> list2{"dog", "cat", "rabbit", "hamster", "parrot"};
	UnsortedArrayList<std::string> list3;
	UnsortedArrayList<std::string> list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	UnsortedArrayList<std::string> list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}
