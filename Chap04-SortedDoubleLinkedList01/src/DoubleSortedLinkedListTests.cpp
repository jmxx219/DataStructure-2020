/* 01
 * SortedLinkedListTests.cpp
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 */

#include <string>
#include "gtest/gtest.h"

#include "DoubleSortedLinkedList.h"

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, listEmptyInitializationTest)
{
	DoubleSortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, add_popFrontTest)
{
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.add(7);
	ASSERT_EQ(list.getSize(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,3,5,7,7,");
	list.add(2);
	list.add(4);
	list.add(6);
	ASSERT_EQ(list.getSize(),3);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"2,4,6,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, add_popBackTest)
{
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	ASSERT_EQ(list.getSize(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"7,5,3,3,");
	list.add(2);
	list.add(4);
	list.add(6);
	ASSERT_EQ(list.getSize(),3);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"6,4,2,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, listInitializationTest)
{
	// requires pushBack, popFront
	DoubleSortedLinkedList list1{5,3,7};
	list1.add(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	DoubleSortedLinkedList list2{1,9,3,2,8,10,4,5,7,6};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, findTest){
	DoubleSortedLinkedList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, removeFirstTest){
	DoubleSortedLinkedList list{11,7,5,7,9,3};

	list.removeFirst(7);	// 중간 삭제
	ASSERT_EQ(list.getSize(),5);
	list.removeFirst(3);	// 첫 요소 삭제
	ASSERT_EQ(list.getSize(),4);
	list.removeFirst(11);	// 맨 마지막 요소 삭제
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"5,7,9,");
	list.removeFirst(7);	// 중간 삭제
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(5);	// 첫 요소 삭제
	ASSERT_EQ(list.getSize(),1);
	list.removeFirst(9);	// 맨 마지막 요소 삭제
	ASSERT_TRUE(list.isEmpty());
	list.add(3);
	list.add(5);
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(5);
	list.removeFirst(3);
	ASSERT_TRUE(list.isEmpty());
}


TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, removeAllTest){
	DoubleSortedLinkedList list{3,3,3,7,3,3,5,3};
	list.removeAll(3);
	ASSERT_EQ(list.getSize(),2);
	list.add(7);
	list.removeAll(7);
	ASSERT_EQ(list.getSize(),1);
	list.removeAll(5);
	ASSERT_TRUE(list.isEmpty());
	list.add(3);
	list.add(3);
	ASSERT_EQ(list.popBack(), 3);
	ASSERT_EQ(list.popFront(), 3);
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, iteratorTest){
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, IndexOperator){
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	ASSERT_EQ(list[1], 5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}


TEST(DoubleSortedLinkedList_WithDuplicate_WithTail, Big5)
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
