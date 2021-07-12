/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 2019136072 손지민
 * TreeTest.cpp
 * 일반 트리구조 테스트 프로그램
 */

#include <string>
#include "gtest/gtest.h"
#include "Tree.h"

TEST(TreeTest, SizeTest)
{
	Node* root{new Node{1}};
	Node* node1{new Node{2}};
	Node* node2{new Node{3}};
	root->addChild(node1);
	root->addChild(node2);
	ASSERT_EQ(2,root->numOfChilds());
	delete root;
}

TEST(TreeTest, bfsIteratorTest)
{
	Node* root{new Node{0}};
	Node* node1{new Node{1}};
	Node* node2{new Node{2}};
	root->addChild(node1);
	root->addChild(node2);
	node1->addChild(new Node{3});
	node1->addChild(new Node{4});
	node2->addChild(new Node{5});

	std::string output = "";
	for(auto i: *root)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,1,2,3,4,5,");
	delete root;
}
/*
TEST(TreeTest, bfsIteratorTest)
{
	Node* root{new Node{0}};
	Node* node1{new Node{1}};
	Node* node2{new Node{2}};
	Node* node3{new Node{3}};
	Node* node6{new Node{6}};
	root->addChild(node1);
	root->addChild(node2);
	node1->addChild(node3);
	node1->addChild(new Node{4});
	node2->addChild(new Node{5});
	node2->addChild(node6);
	node3->addChild(new Node{7});
	node3->addChild(new Node{8});
	node3->addChild(new Node{9});
	node6->addChild(new Node{10});
	node6->addChild(new Node{11});

	std::string output = "";
	for(auto i: *root)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,1,2,3,4,5,6,7,8,9,10,11,");
	delete root;
}
*/
TEST(TreeTest, dfsIteratorTest)
{
	Node* root{new Node{0}};
	Node* node1{new Node{1}};
	Node* node2{new Node{2}};
	root->addChild(node1);
	root->addChild(node2);
	node1->addChild(new Node{3});
	node1->addChild(new Node{4});
	node2->addChild(new Node{5});

	root->setBFSIterator(false);

	std::string output = "";
	for(auto i: *root)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,2,5,1,4,3,");
	delete root;
}

/*
TEST(TreeTest, dfsIteratorTest)
{
	Node* root{new Node{0}};
	Node* node1{new Node{1}};
	Node* node2{new Node{2}};
	Node* node3{new Node{3}};
	Node* node6{new Node{6}};
	root->addChild(node1);
	root->addChild(node2);
	node1->addChild(node3);
	node1->addChild(new Node{4});
	node2->addChild(new Node{5});
	node2->addChild(node6);
	node3->addChild(new Node{7});
	node3->addChild(new Node{8});
	node3->addChild(new Node{9});
	node6->addChild(new Node{10});
	node6->addChild(new Node{11});

	root->setBFSIterator(false);

	std::string output = "";
	for(auto i: *root)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,2,6,11,10,5,1,4,3,9,8,7,");
	delete root;
}
*/
