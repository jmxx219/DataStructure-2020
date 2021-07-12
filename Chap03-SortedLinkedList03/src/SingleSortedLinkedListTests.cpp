/*
 * SingleSortedLinkedListTests.cpp
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * prev, curr 두 개의 포인터를 이용하여 p, removeFirst, removeAll 구현
 * 코드 중복 제거, dummy 노드 활용
 */

#include <string>
#include "gtest/gtest.h"

#include "SingleSortedLinkedList.h"

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, listEmptyInitializationTest)
{
	SingleSortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, add_popFrontTest)
{
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.add(5);
	list.add(7);
	ASSERT_EQ(list.getSize(),3);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,5,7,");
	list.add(2);
	list.add(2);
	list.add(2);
	ASSERT_EQ(list.getSize(),1);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"2,");
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, add_popBackTest)
{
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	ASSERT_EQ(list.getSize(),3);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"7,5,3,");
	list.add(2);
	list.add(4);
	list.add(6);
	ASSERT_EQ(list.getSize(),3);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"6,4,2,");
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, listInitializationTest)
{
	// requires pushBack, popFront
	SingleSortedLinkedList list1{3,3,5,7,5,7,7};
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,");

	SingleSortedLinkedList list2{1,2,3,4,5,6,6,5,4,3,2,1};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,");
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, findTest){
	SingleSortedLinkedList list{3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, removeTest){
	SingleSortedLinkedList list{3,5,7,9,11};
	list.remove(7);	// 중간 삭제
	ASSERT_EQ(list.getSize(),4);
	list.remove(3);	// 첫 요소 삭제
	ASSERT_EQ(list.getSize(),3);
	list.remove(11);	// 맨 마지막 요소 삭제
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"5,9,");
	list.remove(5);
	ASSERT_EQ(list.getSize(),1);
	list.remove(9);
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

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, iteratorTest){
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SingleSortedLinkedList_NoDuplicate_WithTail, IndexOperator){
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	ASSERT_EQ(list[0], 3);
	list.add(2);
	ASSERT_EQ(list[0], 2);
}


TEST(SingleSortedLinkedList_NoDuplicate_WithTail, Big5)
{
	SingleSortedLinkedList list1{1,2,3,4,5};
	SingleSortedLinkedList list2{6,7,8,9,10};
	SingleSortedLinkedList list3;
	SingleSortedLinkedList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SingleSortedLinkedList list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}
