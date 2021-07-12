/* 06
 * SingleUnsortedLinkedListTests.cpp
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2019년도 2학기
 * @author 김상진
 * 단일 연결구조: 정수, 비정렬, 중복 허용, No Tail
 * prev, curr 두 개의 포인터를 이용하여 pushBack, removeFirst, removeAll 구현
 * 코드 중복을 제거하지 않고 구현하고, dummy 노드도 활용하지 않음
 * reverse, middleOfTheList 추가
 */

#include <string>
#include "gtest/gtest.h"
#include "SingleUnsortedLinkedList.h"

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, listEmptyInitializationTest)
{
	SingleUnsortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, PushAndPopFrontTest)
{
	SingleUnsortedLinkedList list;
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, PushAndPopBackTest)
{
	SingleUnsortedLinkedList list;
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, listInitializationTest)
{
	// requires pushBack, popFront
	SingleUnsortedLinkedList list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	SingleUnsortedLinkedList list2{1,2,3,4,5,6,7,8,9,10,};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, findTest){
	SingleUnsortedLinkedList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, removeFirstTest){
	SingleUnsortedLinkedList list;
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

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, removeAllTest){
	SingleUnsortedLinkedList list{3,3,3,7,3,3,5,3};
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, iteratorTest){
	SingleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,5,3,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, IndexOperator){
	SingleUnsortedLinkedList list;
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

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, Big5)
{
	SingleUnsortedLinkedList list1{1,2,3,4,5};
	SingleUnsortedLinkedList list2{6,7,8,9,10};
	SingleUnsortedLinkedList list3;
	SingleUnsortedLinkedList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SingleUnsortedLinkedList list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV1, reverseTest)
{
	SingleUnsortedLinkedList list1{1};
	list1.reverse();
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,");
	SingleUnsortedLinkedList list2{1,2};
	list2.reverse();
	output = "";
	for(auto i: list2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"2,1,");
	SingleUnsortedLinkedList list3{1,2,3,4,5};
	list3.reverse();
	output = "";
	for(auto i: list3)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"5,4,3,2,1,");
	SingleUnsortedLinkedList list4{5,7,2,4,1,9};
	list4.reverse();
	output = "";
	for(auto i: list4)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"9,1,4,2,7,5,");
}



// 5, 7, 2, 4, 1, 9
// x, y,
//    x,    y,
//       x,       y,
//          x,       ---
TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV1, middleOfTheListTest)
{
	SingleUnsortedLinkedList list1{1};
	SingleUnsortedLinkedList list2{1,2};
	SingleUnsortedLinkedList list3{1,2,3,4,5};
	SingleUnsortedLinkedList list4{5,7,2,4,1,9};
	ASSERT_EQ(list1.middleOfTheList(), 1);
	ASSERT_EQ(list2.middleOfTheList(), 2);
	ASSERT_EQ(list3.middleOfTheList(), 3);
	ASSERT_EQ(list4.middleOfTheList(), 4);
}


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV4, getNthFromEnd)
{
   std::string output = "";

   SingleUnsortedLinkedList list1{1,2,3,4,5};
   list1.getNthFromEnd(5);
   while(!list1.isEmpty())
      output += std::to_string(list1.popFront())+",";
   ASSERT_EQ(output,"2,3,4,5,");

   SingleUnsortedLinkedList list2{1};
   list2.getNthFromEnd(1);
   output = "";
   while(!list2.isEmpty())
      output += std::to_string(list2.popFront())+",";
   ASSERT_EQ(output,"");

   SingleUnsortedLinkedList list3{1,2};
   list3.getNthFromEnd(2);
   output = "";
   while(!list3.isEmpty())
      output += std::to_string(list3.popFront())+",";
   ASSERT_EQ(output,"2,");

   SingleUnsortedLinkedList list4{1,2,3,4,5};
   list4.getNthFromEnd(2);
   output = "";
    while(!list4.isEmpty())
       output += std::to_string(list4.popFront())+",";
    ASSERT_EQ(output,"1,2,3,5,");

    SingleUnsortedLinkedList list5{1,2,3,4,5};
    ASSERT_EQ(list5.getNthFromEnd(3),3);
}
