/* 01
 * PostfixEvaluator.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * 후위 표기 표현식 평가 테스트 프로그램
 */

#include <cctype>
#include <algorithm>
#include "gtest/gtest.h"
#include "InfixToPostfix.h"
#include "PostfixEvaluator.h"

TEST(InfixPostfixTest, exceptionTest)
{
	InfixToPostfix infix1("3#4");
	ASSERT_THROW(infix1.toPostfix(), std::runtime_error);

	InfixToPostfix infix2("3 + 4a");
	ASSERT_THROW(infix2.toPostfix(), std::runtime_error);

	ASSERT_THROW(InfixToPostfix infix3("(3 + 4*2"), std::runtime_error);
	ASSERT_THROW(InfixToPostfix infix3("(3 + 4)*2)"), std::runtime_error);
}

TEST(InfixPostfixTest, simpleTest)
{
	InfixToPostfix infix1("3+4");
	ASSERT_EQ("3 4 +", infix1.toPostfix());
	PostfixEvaluator postfix1(infix1.toPostfix());
	ASSERT_EQ(7, postfix1.evaluate());

	InfixToPostfix infix2("3 + 4 * 2");
	ASSERT_EQ("3 4 2 * +", infix2.toPostfix());
	PostfixEvaluator postfix2(infix2.toPostfix());
	ASSERT_EQ(11, postfix2.evaluate());

	InfixToPostfix infix3("(3+4)*2");
	ASSERT_EQ("3 4 + 2 *", infix3.toPostfix());
	PostfixEvaluator postfix3(infix3.toPostfix());
	ASSERT_EQ(14, postfix3.evaluate());
}

TEST(InfixPostfixTest, advancedTest)
{
	InfixToPostfix infix1("3+4-2*7");
	ASSERT_EQ("3 4 + 2 7 * -", infix1.toPostfix());
	PostfixEvaluator postfix1(infix1.toPostfix());
	ASSERT_EQ(-7, postfix1.evaluate());

	InfixToPostfix infix2("3+(4-6/3)*7");
	ASSERT_EQ("3 4 6 3 / - 7 * +", infix2.toPostfix());
	PostfixEvaluator postfix2(infix2.toPostfix());
	ASSERT_EQ(17, postfix2.evaluate());

	InfixToPostfix infix3("312+472/25-120");
	ASSERT_EQ("312 472 25 / + 120 -", infix3.toPostfix());
	PostfixEvaluator postfix3(infix3.toPostfix());
	ASSERT_EQ(210, postfix3.evaluate());
}
