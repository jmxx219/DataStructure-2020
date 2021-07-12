/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * BinearyHeapTests.cpp
 * 테스트 프로그램
 */

#include <list>
#include <string>
#include "gtest/gtest.h"
#include "BinaryHeap.h"


TEST(BinaryHeap, AddTest)
{
	BinaryHeap heap1;
	heap1.add(3);
	heap1.add(5);
	heap1.add(7);
	std::string output = "";
	for(auto i: heap1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,3,5,");
	heap1.add(9);
	heap1.add(11);
	ASSERT_EQ(5, heap1.getSize());
	output = "";
	for(auto i: heap1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"11,9,5,3,7,");

	BinaryHeap heap2;
	heap2.add(3);
	heap2.add(11);
	heap2.add(5);
	heap2.add(7);
	heap2.add(13);
	ASSERT_EQ(5, heap2.getSize());
	output = "";
	for(auto i: heap2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"13,11,5,3,7,");
}

TEST(BinaryHeap, InitializerTest)
{
	BinaryHeap heap1{3,5,7,9,11};
	ASSERT_EQ(5, heap1.getSize());
	std::string output = "";
	for(auto i: heap1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"11,9,5,3,7,");

	BinaryHeap heap2{11,2,8,5,9};
	ASSERT_EQ(5, heap2.getSize());
	output = "";
	for(auto i: heap2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"11,9,8,2,5,");
}

TEST(BinaryHeap, ExtractMaxTest)
{
	BinaryHeap heap;
	heap.add(3);
	heap.add(5);
	heap.add(7);
	heap.add(9);
	heap.add(11);

	std::list<int> list{11,9,7,5,3};
	while(!heap.isEmpty()){
		ASSERT_EQ(list.front(), heap.extractMax());
		list.pop_front();
		ASSERT_EQ(list.size(), heap.getSize());
	}
}

TEST(BinaryHeap, ChangePriorityTest)
{
	BinaryHeap heap;
	heap.add(3);
	heap.add(5);
	heap.add(7);
	heap.add(9);
	heap.add(11);
	heap.changePriority(2,15);
	heap.changePriority(1,1);
	std::string output = "";
	for(auto i: heap)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"15,7,11,3,1,");
}

TEST(BinaryHeap, removeTest)
{
	BinaryHeap heap;
	heap.add(3);
	heap.add(5);
	heap.add(7);
	heap.add(9);
	heap.add(11);
	heap.remove(1);
	std::string output = "";
	for(auto i: heap)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"11,7,5,3,");

	heap.remove(0);
	output = "";
	for(auto i: heap)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,3,5,");
}

TEST(BinaryHeap, Big5)
{
	BinaryHeap heap1{1,2,3,4,5};
	BinaryHeap heap2{6,7,8,9,10};
	BinaryHeap heap3;
	BinaryHeap heap4(heap2);
	// copy constructor test
	auto it2 = heap2.begin();
	auto it4 = heap4.begin();
	while(it2!=heap2.end()&&it4!=heap4.end()){
		ASSERT_EQ(*it2, *it4);
		++it2;
		++it4;
	}
	// copy assignment test
	heap3 = heap1;
	auto it1 = heap1.begin();
	auto it3 = heap3.begin();
	while(it1!=heap1.end()&&it3!=heap3.end()){
		ASSERT_EQ(*it1, *it3);
		++it1;
		++it3;
	}
	// move constructor test
	BinaryHeap heap5(std::move(heap3));
	it1 = heap1.begin();
	auto it5 = heap5.begin();
	while(it1!=heap1.end()&&it5!=heap5.end()){
		ASSERT_EQ(*it1, *it5);
		++it1;
		++it5;
	}
	// move assignment test
	heap3 = std::move(heap4);
	it3 = heap3.begin();
	it2 = heap2.begin();
	while(it3!=heap3.end()&&it2!=heap2.end()){
		ASSERT_EQ(*it3, *it2);
		++it3;
		++it2;
	}
}
