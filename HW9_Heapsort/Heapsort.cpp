/* 		=================================================================================================
 * 		Name: Heapsort.cpp
 *		Author: 손지민 2019136072
 *      Version: 2020년도 2학기
 *      Copyright:
 *      Description: Heapsort
 *      배열이 주어졌을 때 그것을 heapsort를 이용하여 정렬하는 다음 함수를 완성
 *      =================================================================================================
 */

#include <iostream>
#include <algorithm>
#include <utility>
void heapSort(int list[], int size);

void sort(int list[], int size);
void reheapDown(int ParentIndex, int list[], int size);

int main() {
	int lists[] = {4, 7, 0, 3, 9, 17, 19, 6, 2};
	int size{9};

	std::cout << "정렬 전: ";
	for(auto list: lists)std::cout << list << ", ";

	sort(lists,size);

	std::cout << "\n정렬 후: ";
	for(auto list: lists) std::cout << list << ", ";

}

// 부모의 위치: (index-1)/2
// 왼쪽 자식의 위치: (index*2)+1
// 오른쪽 자식의 위치: (index*2)+2
void sort(int list[], int size){
	int firstIndex{(size-2)/2}; // 자식이 있는 첫 번째 노드 == 마지막 노드의 부모 노드
	while(firstIndex>=0){ // 이진힙 만들기
		reheapDown(firstIndex, list, size); // 단말이 아닌 노드에 reheapDown 진행
		firstIndex--;
	}
	// 오름 차순으로 정렬
	for(int i=size-1; i>=0; i--){
		std::swap(list[0], list[i]);
		reheapDown(0, list, --size);
	}
}

void reheapDown(int ParentIndex, int list[], int size){
	while(ParentIndex<size){ // 자식이 있는 첫 번째 노드부터
		//std::cout<<"\n부모 인덱스:" <<ParentIndex;
		int leftChild{2*ParentIndex+1};
		int rightChild{leftChild+1};
		if(leftChild>=size) return;
		int maxChild{leftChild};
		if(rightChild<size && list[leftChild]<list[rightChild])
			maxChild = rightChild;
		if(list[maxChild]>list[ParentIndex]) std::swap(list[maxChild],list[ParentIndex]);
		else return;
		ParentIndex = maxChild;
	}
}


