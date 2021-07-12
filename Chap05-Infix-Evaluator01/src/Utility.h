/* 01
 * PostfixEvaluator.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2019년도 2학기
 * @author 김상진
 * 후위 표기 표현식 평가
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <cctype>
#include <string>
#include <stack>
#include <algorithm>
#include <iostream>

bool isAddTypeOperator(char c){
	return c=='+'||c=='-';
}
bool isMultTypeOperator(char c){
	return c=='*'||c=='/';
}
bool isOperator(char c){
	return isAddTypeOperator(c)||isMultTypeOperator(c);
}
bool isValid(char c){
	return std::isdigit(c)||isOperator(c)||c=='('||c==')';
}

bool isValidParentheses(std::string s) {
	s.erase(std::remove_if(s.begin(), s.end(), [](char c){return c!='('&&c!=')';}), s.end());
	if(s.length()==0) return true;
	if(s.length()%2==1) return false;
	std::stack<char> stack;
	for(char c: s){
		if(c=='(') stack.push(c);
		else if(c==')'){
			if(stack.empty()) return false;
			else stack.pop();
		}
		else return false;
	}
	return stack.empty();
}

#endif /* UTILITY_H_ */
