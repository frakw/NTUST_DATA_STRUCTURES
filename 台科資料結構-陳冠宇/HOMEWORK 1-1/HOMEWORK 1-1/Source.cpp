#include<iostream>
using namespace std;
int main() {
	int N, M, index = 0, prev = -2147483648, count = 0;
	cin >> N >> M;
	int* arr = new int[N] {};
	for (int i = 0;i < N;i++) {
		cin >> arr[i];
	}
	for (int i = 0;i < N;i++) {
		if (arr[i] > prev) ++count;
		else count = 1;
		if (count == M) {
			int holecount = 1;
			int holestart = i - M + 1;
			while (1) {
				if (holestart == 0 || holestart == (N - M)) break;
				int start = (holestart - holecount * M + holecount) > 0 ? (holestart - holecount * M + holecount) : 0;
				int j;
				for (j = start;j < holestart;j++) {
					int k;
					auto fix = [&](int index)->int {
						int tmp = index >= holestart ? (index + holecount * M) : index;
						return tmp < N ? (tmp >= 0 ? tmp : 0) : (N - 1);
					};
					for (k = 1;k < M;k++) {
						if (arr[fix(j + k - 1)] >= arr[fix(j + k)]) break;
					}
					if (k == M) {
						holecount++;
						holestart = j;
						break;
					}
				}
				if (j == holestart) break;
			}
			for (int j = index;j < holestart;j++) {
				cout << arr[j] << ' ';
			}
			index = holestart + M * holecount;
			i = index;
			count = 0;
			prev = -2147483648;
		}
		else prev = arr[i];
	}
	for (int i = index;i < N;i++) {
		cout << arr[i] << ' ';
	}
	return 0;
}



//linked list版本，效率更高

//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//typedef struct node {
//	struct node* next;
//	struct node* prev;
//	int value;
//} Node;
//
//Node* create_node(int value, Node* prev)
//{
//	Node* node = (Node*)malloc(sizeof(Node));
//	node->next = NULL;
//	node->value = value;
//	node->prev = prev;
//	return node;
//}
//int main() {
//	int N, M;
//	Node* head, * now;
//	int size = 0, index = 0;
//	head = create_node(0, NULL);
//	now = head;
//	scanf("%d%d%d", &N, &M,&(now->value));
//	//Node** backup = (Node**)malloc(N * sizeof(Node*));
//
//	//backup[0] = head;
//	size = N;
//	for (int i = 1;i < N;i++) {
//		now->next = create_node(0, now);
//		now = now->next;
//		scanf("%d", &(now->value));
//		//backup[i] = now;
//	}
//	now = head;
//	while ((index + M) <= size) {
//		Node* scan = now->next;
//		int i, prev = now->value;
//		for (i = 1;i < M;i++) {
//			if (prev >= scan->value) break;
//			prev = scan->value;
//			scan = scan->next;
//		}
//		if (i == M) {
//			if (now == head) {
//				head = now = scan;
//				head->prev = NULL;
//				index = 0;
//			}
//			else {
//				now->prev->next = scan;
//				if (scan) scan->prev = now->prev;
//				index -= (M - 1);
//				if (index < 0) index = 0;
//				for (int i = 1;i < M && now->prev;i++) now = now->prev;
//			}
//			size -= M;
//		}
//		else {
//			index += i;
//			for(int j=0;j<i;j++) now = now->next;
//		}
//	}
//	while (head) {
//		printf("%d ", head->value);
//		head = head->next;
//	}
//	//for (int i = 0;i < N;++i)	free(backup[i]);
//	//free(backup);
//	return 0;
//}

//c++ array版本，效率低
//#include <iostream>
//using namespace std;
//template <class T>
//class vec {
//public:
//	T& operator[](int index) {
//		return arr[index];
//	}
//	vec(int isize) {
//		arr = new T[isize];
//		size = isize;
//		capacity = isize;
//		head = arr;
//	}
//	~vec() {
//		delete[] head;
//	}
//	void erase(int index, int count) {
//		if (index+index+count < size) {
//			for (int i = index - 1;i >= 0;--i) {
//				arr[i + count] = arr[i];
//			}
//			arr += count;
//		}
//		else {
//			for (int i = index + count;i < size;++i) {
//				arr[i - count] = arr[i];
//			}
//		}
//		size -= count;
//	}
//	T* arr = nullptr;
//	T* head = nullptr;
//	int size = 0;
//	int capacity = 0;
//};
//int main() {
//	int N, M, index = 0;
//	cin >> N >> M;
//	vec<int> sequences(N);
//	for (int i = 0;i < N;i++) {
//		cin >> sequences.arr[i];
//	}
//	while ((index + M) <= sequences.size) {
//		int i;
//		for (i = 1;i < M;i++) {
//			if (sequences[index + i - 1] >= sequences[index + i]) break;
//		}
//		if (i == M) {
//			sequences.erase(index, M);
//			index -= (M-1);
//			index = index < 0 ? 0 : index;
//		}
//		else index+=i;
//	}
//	for (int k = 0;k < sequences.size;k++) {
//		cout << sequences[k] << ' ';
//	}
//
//
//	return 0;
//}
