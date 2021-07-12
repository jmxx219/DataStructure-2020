/* 03
 * SingleUnsortedLinkedListTests.cpp
 * �ѱ�����������б� ��ǻ�Ͱ��к� �ڷᱸ���׽ǽ�
 * @version 2019�⵵ 2�б�
 * @author �����
 * ���� ���ᱸ��: ����, ������, �ߺ� ���, No Tail
 * �� ���� �����͸� �̿��Ͽ� popBack, removeFirst, removeAll ����
 * �ڵ� �ߺ��� ����, dummy ��� Ȱ��
 */

#include <string>
#include "gtest/gtest.h"
#include "SingleUnsortedLinkedList.h"

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, listEmptyInitializationTest)
{
	SingleUnsortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, PushAndPopFrontTest)
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, PushAndPopBackTest)
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, listInitializationTest)
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

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, findTest){
	SingleUnsortedLinkedList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, removeFirstTest){
	SingleUnsortedLinkedList list;
	list.pushFront(11);
	list.pushFront(7);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(9);
	list.pushFront(3);

	list.removeFirst(7);	// �߰� ����
	ASSERT_EQ(list.getSize(),5);
	list.removeFirst(3);	// ù ��� ����
	ASSERT_EQ(list.getSize(),4);
	list.removeFirst(11);	// �� ������ ��� ����
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"9,5,7,");
	list.removeFirst(5);	// �߰� ����
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(9);	// ù ��� ����
	ASSERT_EQ(list.getSize(),1);
	list.removeFirst(7);	// �� ������ ��� ����
	ASSERT_TRUE(list.isEmpty());
	list.pushFront(3);
	list.pushBack(5);
	ASSERT_EQ(list.getSize(),2);
	list.removeFirst(5);
	list.removeFirst(3);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, removeAllTest){
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


TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, iteratorTest){
	SingleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,5,3,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, IndexOperator){
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

TEST(SingleUnsortedLinkedList_WithDuplicate_NoTailV3, Big5)
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
