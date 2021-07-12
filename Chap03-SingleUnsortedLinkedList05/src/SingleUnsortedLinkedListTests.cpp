/* 05
 * SingleUnsortedLinkedListTests.cpp
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2019년도 2학기
 * @author 김상진
 * 단일 연결구조: 범용, 비정렬, 중복 허용, No Tail
 * prev, curr 두 개의 포인터를 이용하여 popBack, removeFirst, removeAll 구현
 * 코드 중복을 제거, dummy 노드를 활용
 */

#include <string>
#include "gtest/gtest.h"
#include "SingleUnsortedLinkedList.h"

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, listEmptyInitializationTest)
{
	SingleUnsortedLinkedList<int> list1{};
	ASSERT_EQ(list1.getSize(), 0);
	ASSERT_TRUE(list1.isEmpty());
	ASSERT_FALSE(list1.isFull());

	SingleUnsortedLinkedList<std::string> list2{};
	ASSERT_EQ(list2.getSize(), 0);
	ASSERT_TRUE(list2.isEmpty());
	ASSERT_FALSE(list2.isFull());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, PushAndPopFrontTest)
{
	SingleUnsortedLinkedList<int> list1;
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
	list1.pushFront(2);
	list1.pushFront(4);
	list1.pushFront(6);
	ASSERT_EQ(list1.getSize(),3);
	output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"6,4,2,");

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushFront("apple");
	list2.pushFront("banana");
	list2.pushFront("grape");
	list2.pushFront("apple");
	list2.pushFront("banana");
	ASSERT_EQ(list2.getSize(),5);
	output = "";
	while(!list2.isEmpty())
		output += list2.popFront()+",";
	ASSERT_EQ(output,"banana,apple,grape,banana,apple,");
	list2.pushFront("melon");
	list2.pushFront("kiwi");
	list2.pushFront("cherry");
	ASSERT_EQ(list2.getSize(),3);
	output = "";
	while(!list2.isEmpty())
		output += list2.popFront()+",";
	ASSERT_EQ(output,"cherry,kiwi,melon,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, PushAndPopBackTest)
{
	SingleUnsortedLinkedList<int> list1;
	list1.pushBack(3);
	list1.pushBack(5);
	list1.pushBack(7);
	list1.pushBack(3);
	ASSERT_EQ(list1.getSize(),4);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");
	list1.pushBack(2);
	list1.pushBack(4);
	list1.pushBack(6);
	ASSERT_EQ(list1.getSize(),3);
	output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popBack())+",";
	ASSERT_EQ(output,"6,4,2,");

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushBack("dog");
	list2.pushBack("cat");
	list2.pushBack("hamster");
	list2.pushBack("dog");
	ASSERT_EQ(list2.getSize(),4);
	output = "";
	while(!list2.isEmpty())
		output += list2.popBack()+",";
	ASSERT_EQ(output,"dog,hamster,cat,dog,");
	list2.pushBack("hen");
	list2.pushBack("duck");
	list2.pushBack("swan");
	ASSERT_EQ(list2.getSize(),3);
	output = "";
	while(!list2.isEmpty())
		output += list2.popBack()+",";
	ASSERT_EQ(output,"swan,duck,hen,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, listInitializationTest)
{
	SingleUnsortedLinkedList<int> list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	SingleUnsortedLinkedList<int> list2{1,2,3,4,5,6,7,8,9,10,};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");

	SingleUnsortedLinkedList<std::string> list3{"dog","cat","pig"};
	output = "";
	while(!list3.isEmpty())
		output += list3.popFront()+",";
	ASSERT_EQ(output,"dog,cat,pig,");

	SingleUnsortedLinkedList<std::string> list4{"duck","tiger","monkey","dog","cat","hamster","hen","pigeon"};
	output = "";
	while(!list4.isEmpty())
		output += list4.popFront()+",";
	ASSERT_EQ(output,"duck,tiger,monkey,dog,cat,hamster,hen,pigeon,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, findTest){
	SingleUnsortedLinkedList<int> list1{3,3,5,7,9};
	ASSERT_TRUE(list1.find(3));
	ASSERT_TRUE(list1.find(5));
	ASSERT_TRUE(list1.find(7));
	ASSERT_TRUE(list1.find(9));
	ASSERT_FALSE(list1.find(2));
	ASSERT_FALSE(list1.find(4));
	ASSERT_FALSE(list1.find(11));

	SingleUnsortedLinkedList<std::string> list2{"apple","grape","banana","kiwi","peach"};
	ASSERT_TRUE(list2.find("apple"));
	ASSERT_TRUE(list2.find("grape"));
	ASSERT_TRUE(list2.find("kiwi"));
	ASSERT_TRUE(list2.find("peach"));
	ASSERT_FALSE(list2.find("mango"));
	ASSERT_FALSE(list2.find("berry"));
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, removeFirstTest){
	SingleUnsortedLinkedList<int> list1;
	list1.pushFront(11);
	list1.pushFront(7);
	list1.pushFront(5);
	list1.pushFront(7);
	list1.pushFront(9);
	list1.pushFront(3);

	list1.removeFirst(7);	// 중간 삭제
	ASSERT_EQ(list1.getSize(),5);
	list1.removeFirst(3);	// 첫 요소 삭제
	ASSERT_EQ(list1.getSize(),4);
	list1.removeFirst(11);	// 맨 마지막 요소 삭제
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"9,5,7,");
	list1.removeFirst(5);	// 중간 삭제
	ASSERT_EQ(list1.getSize(),2);
	list1.removeFirst(9);	// 첫 요소 삭제
	ASSERT_EQ(list1.getSize(),1);
	list1.removeFirst(7);	// 맨 마지막 요소 삭제
	ASSERT_TRUE(list1.isEmpty());
	list1.pushFront(3);
	list1.pushBack(5);
	ASSERT_EQ(list1.getSize(),2);
	list1.removeFirst(5);
	list1.removeFirst(3);
	ASSERT_TRUE(list1.isEmpty());

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushFront("apple");
	list2.pushFront("banana");
	list2.pushFront("mango");
	list2.pushFront("banana");
	list2.pushFront("melon");

	list2.removeFirst("banana");
	list2.removeFirst("apple");
	list2.removeFirst("melon");
	ASSERT_EQ(list2.getSize(),2);
	list2.removeFirst("banana");
	list2.removeFirst("mango");
	ASSERT_TRUE(list2.isEmpty());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, removeAllTest){
	SingleUnsortedLinkedList<int> list1{3,3,3,7,3,3,5,3};
	list1.removeAll(3);
	ASSERT_EQ(list1.getSize(),2);
	list1.pushBack(7);
	list1.removeAll(7);
	ASSERT_EQ(list1.getSize(),1);
	list1.removeAll(5);
	ASSERT_TRUE(list1.isEmpty());
	list1.pushBack(3);
	list1.pushFront(5);
	ASSERT_EQ(list1.popBack(), 3);
	ASSERT_EQ(list1.popFront(), 5);

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushFront("apple");
	list2.pushFront("apple");
	list2.pushFront("mango");
	list2.pushFront("banana");
	list2.pushFront("banana");
	list2.pushFront("mango");
	list2.pushBack("banana");
	list2.pushBack("apple");
	list2.pushBack("apple");
	list2.pushBack("apple");
	list2.pushBack("mango");
	list2.pushBack("mango");
	list2.pushBack("apple");
	list2.removeAll("apple");
	ASSERT_EQ(list2.getSize(),7);
	list2.removeAll("mango");
	ASSERT_EQ(list2.getSize(),3);
	list2.removeAll("banana");
	ASSERT_TRUE(list2.isEmpty());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, iteratorTest){
	SingleUnsortedLinkedList<int> list1;
	list1.pushFront(3);
	list1.pushFront(5);
	list1.pushFront(7);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,5,3,");

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushFront("apple");
	list2.pushFront("banana");
	list2.pushFront("grape");
	output = "";
	for(auto f: list2)
		output += f+",";
	ASSERT_EQ(output,"grape,banana,apple,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, IndexOperator){
	SingleUnsortedLinkedList<int> list1;
	list1.pushFront(3);
	list1.pushFront(5);
	ASSERT_EQ(list1[1], 3);
	list1.pushFront(7);
	list1[0] = 4;
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,3,");

	SingleUnsortedLinkedList<std::string> list2;
	list2.pushFront("apple");
	list2.pushFront("banana");
	ASSERT_EQ(list2[1], "apple");
	list2.pushFront("mango");
	list2[0] = "kiwi";
	output = "";
	for(auto f: list2)
		output += f+",";
	ASSERT_EQ(output,"kiwi,banana,apple,");
}


TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, Big5_int)
{
	SingleUnsortedLinkedList<int> list1{1,2,3,4,5};
	SingleUnsortedLinkedList<int> list2{6,7,8,9,10};
	SingleUnsortedLinkedList<int> list3;
	SingleUnsortedLinkedList<int> list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SingleUnsortedLinkedList<int> list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Generic, Big5_string)
{
	SingleUnsortedLinkedList<std::string> list1{"apple","banana","cherry","melon","kiwi"};
	SingleUnsortedLinkedList<std::string> list2{"peach","grape","watermelon","orange","mango"};
	SingleUnsortedLinkedList<std::string> list3;
	SingleUnsortedLinkedList<std::string> list4(list2);
	// copy constructor test
	for(int i=0; i<list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SingleUnsortedLinkedList<std::string> list5(std::move(list3));
	for(int i=0; i<list5.getSize(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.getSize(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}
