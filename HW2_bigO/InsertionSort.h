/* 		=================================================================================================
 * 		Name: InsertionSort.h
 *		Author: 손지민 2019136072
 *      Version: 2020년도 2학기
 *      Copyright: ds-note01.pdf 연습문제 1번
 *      Description: insertionSort
 *      =================================================================================================
 */

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_


/*
 * <삽입 정렬 알고리즘>
 * 이 알고리즘의 최선과 최악의 경우 시간 비용을 분석하시오. 데이터가 어떤 형태일 때 최선, 최악인지 제시하고,
 * 그 때 소요되는 비용을 빅O 표기법으로 제시하여야 함. 최종적으로 이 알고리즘의 빅O를 제시하시오.
 *
 * <size = n>
 *
 * 1. 최선: 데이터가 정렬이 되어있는 경우(1, 2, ···, n)
 * 		=> while문 if에서 1번씩 비교가 이루어진다. 그래서 (n-1)번이므로 O(n)이다.
 *
 * 2. 최악: 데이터가 역순으로 정렬되어 있는 경우(n, (n -1), ···, 1)
 * 		=> while문 if가 항상 참이므로 j의 값이 i에서 1이 될때까지  반복이 이루어진다. 그래서 1 + ··· + (n-1) = n(n-1)/2번이므로 O(n^2)이다.
 *
 * 3. 최종 알고리즘의 빅O: O(n^2)
 *
 */

/* void insertionSort(int nums[], int size){
	for(int i = 1; i < size; i++){
		int j = i;
		while(j > 0){
			if(nums[j-1] > nums[j]) std::swap(nums[j-1], nums[j]);
			else break;
			--j;
		}
	}
}*/


#endif /* INSERTIONSORT_H_ */
