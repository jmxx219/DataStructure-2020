/* 01
 * DoubleUnsortedLinkedListTests.cpp
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 */

#include <string>
#include "gtest/gtest.h"
#include "DoubleUnsortedLinkedList.h"

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, listEmptyInitializationTest)
{
	DoubleSortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, PushAndPopFrontTest)
{
	DoubleSortedLinkedList list;
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
	list.pushFront(2);
	list.pushFront(4);
	list.pushFront(6);
	ASSERT_EQ(list.getSize(),3);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"6,4,2,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, PushAndPopBackTest)
{
	DoubleSortedLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.getSize(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");
	list.pushBack(2);
	list.pushBack(4);
	list.pushBack(6);
	ASSERT_EQ(list.getSize(),3);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"6,4,2,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, listInitializationTest)
{
	// requires pushBack, popFront
	DoubleSortedLinkedList list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	DoubleSortedLinkedList list2{1,2,3,4,5,6,7,8,9,10,};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, findTest){
	DoubleSortedLinkedList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, removeFirstTest){
	DoubleSortedLinkedList list;
	list.pushFront(11);
	list.pushFront(7);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(9);
	list.pushFront(3);

	list.removeFirst(7);	// 중간 삭제
	ASSERT_EQ(list.getSize(),5);
	list.removeFirst(3);	// 첫 요소 삭제
	ASSERT_EQ(list.getSize(),4);
	list.removeFirst(11);	// 맨 마지막 요소 삭제
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"9,5,7,");
	list.removeFirst(5);	// 중간 삭제
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(9);	// 첫 요소 삭제
	ASSERT_EQ(list.getSize(),1);
	list.removeFirst(7);	// 맨 마지막 요소 삭제
	ASSERT_TRUE(list.isEmpty());
	list.pushFront(3);
	list.pushBack(5);
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(5);
	list.removeFirst(3);
	ASSERT_TRUE(list.isEmpty());
}


TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, removeAllTest){
	DoubleSortedLinkedList list{3,3,3,7,3,3,5,3};
	list.removeAll(3);
	ASSERT_EQ(list.getSize(),2);
	list.pushBack(7);
	list.removeAll(7);
	ASSERT_EQ(list.getSize(),1);
	list.removeAll(5);
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(3);
	list.pushFront(5);
	ASSERT_EQ(list.popBack(), 3);
	ASSERT_EQ(list.popFront(), 5);
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, iteratorTest){
	DoubleSortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,5,3,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, IndexOperator){
	DoubleSortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	ASSERT_EQ(list[1], 3);
	list.pushFront(7);
	list[0] = 4;
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,3,");
}


TEST(DoubleUnsortedLinkedList_WithDuplicate_NoTail, Big5)
{
	DoubleSortedLinkedList list1{1,2,3,4,5};
	DoubleSortedLinkedList list2{6,7,8,9,10};
	DoubleSortedLinkedList list3;
	DoubleSortedLinkedList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	DoubleSortedLinkedList list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}
