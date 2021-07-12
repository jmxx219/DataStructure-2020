/* 02
 * PostfixEvaluator.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2019년도 2학기
 * @author 김상진
 * 후위 표기 표현식 평가
 * 이항 연산자, 단항연산자 처리할 수 있음
 */
#ifndef POSTFIXEVALUATOR_H_
#define POSTFIXEVALUATOR_H_

#include <stdexcept>
#include <cctype>
#include <stack>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include "Utility.h"

class PostfixEvaluator {
private:
	std::string postfix;
	std::stack<int> stack;
public:
	PostfixEvaluator(std::string expression): postfix(expression){
	}
	virtual ~PostfixEvaluator() = default;
	int evaluate(){
		int n = 0;
		bool processingDigit = false;
		for(char c: postfix){
			if(std::isdigit(c)){
				processingDigit = true;
				n = static_cast<int>(c-'0')+n*10;
			}
			else if(c==' '){
				if(processingDigit){
					stack.push(n);
					n = 0;
					processingDigit = false;
				}
			}
			else if(c=='@'){
				int n = stack.top();
				stack.pop();
				stack.push(-n);
			}
			else if(isOperator(c)){
				if(stack.size()<2) throw std::runtime_error("");
				int n2 = stack.top();
				stack.pop();
				int n1 = stack.top();
				stack.pop();
				int comp = 0;
				switch(c){
				case '+': comp = n1+n2; break;
				case '-': comp = n1-n2; break;
				case '*': comp = n1*n2; break;
				default: comp = n1/n2; break;
				}
				stack.push(comp);
			}
			else throw std::runtime_error("");
		}
		int result{stack.top()};
		stack.pop();
		return result;
	}
};

#endif /* POSTFIXEVALUATOR_H_ */
