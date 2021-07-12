/* 02
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

bool isValidExpression(std::string s){
	char prev{0};
	int operandCount{0};
	int operatorCount{0};
	for(char curr: s){
		if(!isValid(curr) && !std::isspace(curr)){
			std::cout << "유효하지 않은 문자 사용\n";
			return false;
		}
		else if(isOperator(curr)){
			if(operandCount==0&&curr!='-'){
				std::cout << "맨 앞에 올 수 있는 연산자는 -만 가능\n";
				return false;
			}
			operandCount = 0;
			++operatorCount;
			if(operatorCount==2&&curr!='-'){
				std::cout << "연속 연산자는 -만 가능\n";
				return false;
			}
			else if(operatorCount>=3){
				std::cout << "연속 연산자가 3개 이상\n";
				return false;
			}
		}
		else if(!std::isdigit(prev)&&std::isdigit(curr)){
			operatorCount = 0;
			++operandCount;
			if(operandCount>=2){
				std::cout << "연속 피연산자가 2개 이상\n";
				return false;
			}
		}
		prev = curr;
	}
	return operatorCount==0;
}

void replaceSubtractWithNegative(std::string& s){
	char prev{0};
	int operandCount{0};
	int operatorCount{0};
	for(char& curr: s){
		if(isOperator(curr)){
			if(operandCount==0) curr='@';
			else operandCount = 0;
			++operatorCount;
			if(operatorCount==2&&curr=='-') curr='@';
		}
		else if(!std::isdigit(prev)&&std::isdigit(curr)){
			operatorCount = 0;
			++operandCount;
		}
		prev = curr;
	}
}
#endif /* UTILITY_H_ */
