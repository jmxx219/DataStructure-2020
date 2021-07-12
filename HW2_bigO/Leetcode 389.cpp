/* 		=================================================================================================
 * 		Name: Leetcode 389.cpp
 *		Author: 손지민 2019136072
 *      Version: 2020년도 2학기
 *      Copyright: leetcode 389
 *      Description: findTheDifference
 *      Additional Option: LeetCode 통과
 *      Runtime: 100 ms, faster than 8.44% of C++ online submissions for Find the Difference.
 *		Memory Usage: 6.6 MB, less than 70.00% of C++ online submissions for Find the Difference.
 *      =================================================================================================
 */

#include <iostream>
using namespace std;
char findTheDifference(string,string);

/*
 * 2. 소스에 포함된 LeetCode 389번 해결책의 빅O을 분석한 내용
 *
 *  만약 s.length() = n, t.length() = n + x(상수)일때
 * 	 - for(int i = 0; i < s.length(); i++)일 때 실행되는 수 : n번
 * 	 - for(int j = 0; j < t.length(); j++)일 때 실행되는 수 : n + x번
 * 	 이므로 n * (n + x) = n^2 + nx이다. 이때 nx는 n^2보다 작으므로 무시한다.
 * 	 따라서 빅오는 O(n^2)이다.
 *
 */

int main() {
	string s("ae");
	string t("aea");

	cout << "Output: " << findTheDifference(s,t) << endl;
}

char findTheDifference(string s, string t) {
	char plus;
	int n = 0;

	if(s.length() == 0)	n = 1;

	if (n == 1)	plus = t.at(0); // s = "", t = "a"

	else if (n == 0) { // s = "ae", t = "aea"
		for(int i = 0; i < s.length(); i++){
			for(int j = 0; j < t.length(); j++) {
				if(s.at(i) == t.at(j)){
					t.at(j) = 1;
					break;
				}
			}
		}
		for(int i = 0; i < t.length(); i++){
			if(t.at(i) != 1){
				plus = t.at(i);
			}
		}
	}

	return plus;
}


