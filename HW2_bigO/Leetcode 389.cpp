/* 		=================================================================================================
 * 		Name: Leetcode 389.cpp
 *		Author: ������ 2019136072
 *      Version: 2020�⵵ 2�б�
 *      Copyright: leetcode 389
 *      Description: findTheDifference
 *      Additional Option: LeetCode ���
 *      Runtime: 100 ms, faster than 8.44% of C++ online submissions for Find the Difference.
 *		Memory Usage: 6.6 MB, less than 70.00% of C++ online submissions for Find the Difference.
 *      =================================================================================================
 */

#include <iostream>
using namespace std;
char findTheDifference(string,string);

/*
 * 2. �ҽ��� ���Ե� LeetCode 389�� �ذ�å�� ��O�� �м��� ����
 *
 *  ���� s.length() = n, t.length() = n + x(���)�϶�
 * 	 - for(int i = 0; i < s.length(); i++)�� �� ����Ǵ� �� : n��
 * 	 - for(int j = 0; j < t.length(); j++)�� �� ����Ǵ� �� : n + x��
 * 	 �̹Ƿ� n * (n + x) = n^2 + nx�̴�. �̶� nx�� n^2���� �����Ƿ� �����Ѵ�.
 * 	 ���� ����� O(n^2)�̴�.
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


