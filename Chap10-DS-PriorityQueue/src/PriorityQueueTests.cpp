/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2020년도 2학기
 * PriorityQueueTests.cpp
 * 테스트 프로그램
 * Author: 김상진
 */

#include "PriorityQueue.h"
#include "gtest/gtest.h"
#include <string>

TEST(PriorityQueue, enqueue_dequeue_Test)
{
	PriorityQueue queue1;
	queue1.enqueue(3);
	queue1.enqueue(5);
	queue1.enqueue(7);
	queue1.enqueue(9);
	queue1.enqueue(11);
	ASSERT_EQ(5, queue1.getSize());
	std::string output = "";
	while(!queue1.isEmpty())
		output += std::to_string(queue1.dequeue())+",";
	ASSERT_EQ(output,"11,9,7,5,3,");

	PriorityQueue queue2;
	queue2.enqueue(3);
	queue2.enqueue(11);
	queue2.enqueue(5);
	queue2.enqueue(7);
	queue2.enqueue(13);
	ASSERT_EQ(5, queue2.getSize());
	output = "";
	while(!queue2.isEmpty())
		output += std::to_string(queue2.dequeue())+",";
	ASSERT_EQ(output,"13,11,7,5,3,");
}

TEST(PriorityQueue, InitializerTest)
{
	PriorityQueue queue1{3,5,7,9,11};
	ASSERT_EQ(5, queue1.getSize());
	std::string output = "";
	while(!queue1.isEmpty())
		output += std::to_string(queue1.dequeue())+",";
	ASSERT_EQ(output,"11,9,7,5,3,");

	PriorityQueue queue2{11,2,8,5,9};
	ASSERT_EQ(5, queue2.getSize());
	output = "";
	while(!queue2.isEmpty())
		output += std::to_string(queue2.dequeue())+",";
	ASSERT_EQ(output,"11,9,8,5,2,");
}

TEST(BinaryHeap, Big5)
{
	PriorityQueue queue1{1,2,3,4,5};
	PriorityQueue queue2{6,7,8,9,10};
	PriorityQueue queue3;
	PriorityQueue queue4(queue2);
	// copy constructor test
	auto it2 = queue2.begin();
	auto it4 = queue4.begin();
	while(it2!=queue2.end()&&it4!=queue4.end()){
		ASSERT_EQ(*it2, *it4);
		++it2;
		++it4;
	}
	// copy assignment test
	queue3 = queue1;
	auto it1 = queue1.begin();
	auto it3 = queue3.begin();
	while(it1!=queue1.end()&&it3!=queue3.end()){
		ASSERT_EQ(*it1, *it3);
		++it1;
		++it3;
	}
	// move constructor test
	PriorityQueue queue5(std::move(queue3));
	it1 = queue1.begin();
	auto it5 = queue5.begin();
	while(it1!=queue1.end()&&it5!=queue5.end()){
		ASSERT_EQ(*it1, *it5);
		++it1;
		++it5;
	}
	// move assignment test
	queue3 = std::move(queue4);
	it3 = queue3.begin();
	it2 = queue2.begin();
	while(it3!=queue3.end()&&it2!=queue2.end()){
		ASSERT_EQ(*it3, *it2);
		++it3;
		++it2;
	}
}
