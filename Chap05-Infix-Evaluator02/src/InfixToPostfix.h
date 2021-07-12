/* 02
 * PostfixEvaluator.h
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2020년도 2학기
 * @author 김상진
 * 전위 표기 표현식을 후위 표기 표현식으로 바꾸어 주는 클래스
 * 이항 연산자, 단항연산자 지원
 */

#ifndef INFIXTOPOSTFIX_H_
#define INFIXTOPOSTFIX_H_

#include <stdexcept>
#include <cctype>
#include <stack>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include "Utility.h"

class InfixToPostfix {
private:
	std::string infix;
	std::stack<char> stack;
public:
	InfixToPostfix(std::string expression): infix(expression){
		if(!isValidExpression(infix)) throw std::runtime_error("유효하지 않은 식: "+infix);
		// remove whitespaces
		infix.erase(std::remove_if(infix.begin(), infix.end(), [](char c){return std::isspace(c);}), infix.end());
		if(!isValidParentheses(infix)) throw std::runtime_error("괄호 문제");
		replaceSubtractWithNegative(infix);
	}
	virtual ~InfixToPostfix() = default;
	void moveOperatorsToPostfix(std::string& postfix, std::function<bool(char)> pushPredicate, std::function<bool(char)> stopPredicate){
		while(!stack.empty()){
			int top = stack.top();
			if(pushPredicate(top)){
				postfix.push_back(static_cast<char>(top));
				postfix.push_back(' ');
				stack.pop();
			}
			else if(stopPredicate(top)){
				break;
			}
			else throw std::runtime_error("processing ) or Operators");
		}
	}
	std::string toPostfix(){
		std::string postfix(infix.size()*2,'\0');
		postfix.resize(0);
		int n = 0;
		bool processingDigit = false;
		for(char c: infix){
			if(std::isdigit(c)){
				processingDigit = true;
				n = static_cast<int>(c-'0')+n*10;
			}
			else if(c=='(') stack.push(c);
			else if(c==')'||isOperator(c)||c=='@'){
				if(processingDigit){
					postfix.append(std::to_string(n)+" ");
					n = 0;
					processingDigit = false;
				}
				if(isOperator(c)||c=='@'){
					if(stack.empty()) stack.push(c);
					else{
						// 왼쪽 괄호를 만나거나, 자신보다 낮은 우선순위 연산자를 만나거나, 스택이 empty가 될 때까지
						// 스택에 있는 연산자를 postfix 문자열에 추가
						if(c=='@'){
							moveOperatorsToPostfix(postfix,
								[](char c){return c=='@';},
								[](char c){return c=='('||isOperator(c);});
						}
						else if(isAddTypeOperator(c)){
							moveOperatorsToPostfix(postfix,
								[](char c){return isOperator(c)||c=='@';},
								[](char c){return c=='(';});
						}
						else{
							moveOperatorsToPostfix(postfix,
								[](char c){return isMultTypeOperator(c)||c=='@';},
								[](char c){return c=='('||isAddTypeOperator(c);});
						}
						// 연산자를 스택에 추가
						stack.push(c);
					}
				}
				else{ // 오른쪽 괄호:
					// 왼쪽 괄호를 만날 때까지 스택에 있는 연산자를 postfix 문자열에 추가 스택에서 왼쪽 괄호 제거
					moveOperatorsToPostfix(postfix,
						[](char c){return isOperator(c)||c=='@';},
						[](char c){return c=='(';});
					int top = stack.top();
					if(top=='(') stack.pop();
					else throw std::runtime_error("processing )");
				}
			}
			else{
				throw std::runtime_error("invalid character: "+std::to_string(c));
			}
		}
		if(processingDigit){
			postfix.append(std::to_string(n)+" ");
		}

		moveOperatorsToPostfix(postfix,
			[](char c){return isOperator(c)||c=='@';},
			[](char c){return false;});
		postfix.pop_back(); // 끝에 공백 문자 제거
		return postfix;
	}

};

#endif /* INFIXTOPOSTFIX_H_ */
