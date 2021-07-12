/* 		=================================================================================================
 * 		Name: Heapsort.cpp
 *		Author: ������ 2019136072
 *      Version: 2020�⵵ 2�б�
 *      Copyright:
 *      Description: Heapsort
 *      �迭�� �־����� �� �װ��� heapsort�� �̿��Ͽ� �����ϴ� ���� �Լ��� �ϼ�
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

	std::cout << "���� ��: ";
	for(auto list: lists)std::cout << list << ", ";

	sort(lists,size);

	std::cout << "\n���� ��: ";
	for(auto list: lists) std::cout << list << ", ";

}

// �θ��� ��ġ: (index-1)/2
// ���� �ڽ��� ��ġ: (index*2)+1
// ������ �ڽ��� ��ġ: (index*2)+2
void sort(int list[], int size){
	int firstIndex{(size-2)/2}; // �ڽ��� �ִ� ù ��° ��� == ������ ����� �θ� ���
	while(firstIndex>=0){ // ������ �����
		reheapDown(firstIndex, list, size); // �ܸ��� �ƴ� ��忡 reheapDown ����
		firstIndex--;
	}
	// ���� �������� ����
	for(int i=size-1; i>=0; i--){
		std::swap(list[0], list[i]);
		reheapDown(0, list, --size);
	}
}

void reheapDown(int ParentIndex, int list[], int size){
	while(ParentIndex<size){ // �ڽ��� �ִ� ù ��° ������
		//std::cout<<"\n�θ� �ε���:" <<ParentIndex;
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


