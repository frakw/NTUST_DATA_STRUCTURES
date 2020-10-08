/*#include <iostream>
using namespace std;
template <class T>
class vec {
public:
	T& operator[](int index) {
		return arr[index];
	}
	vec(int isize) {
		arr = new T[isize];
		size = isize;
		capacity = isize;
		head = arr;
	}
	~vec() {
		delete[] head;
	}
	void erase(int index, int count) {
		if (index+index+count < size) {
			for (int i = index - 1;i >= 0;--i) {
				arr[i + count] = arr[i];
			}
			arr += count;
		}
		else {
			for (int i = index + count;i < size;++i) {
				arr[i - count] = arr[i];
			}
		}
		size -= count;
	}
	T* arr = nullptr;
	T* head = nullptr;
	int size = 0;
	int capacity = 0;
};
int main() {
	int N, M, index = 0;
	cin >> N >> M;
	vec<int> sequences(N);
	for (int i = 0;i < N;i++) {
		cin >> sequences.arr[i];
	}
	while ((index + M) <= sequences.size) {
		int i;
		for (i = 1;i < M;i++) {
			if (sequences[index + i - 1] >= sequences[index + i]) break;
		}
		if (i == M) {
			sequences.erase(index, M);
			index -= (M-1);
			index = index < 0 ? 0 : index;
		}
		else index++;
	}
	for (int k = 0;k < sequences.size;k++) {
		cout << sequences[k] << ' ';
	}
	cout << endl;

	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	struct node* next;
	struct node* prev;
	int value;
} Node;

typedef struct list {
	Node* head;
} List;

Node* create_node(int value,Node* prev)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->value = value;
	node->prev = prev;
	return node;
}
int main() {
	int N, M,first;
	List list;
	Node* now;
	int size = 0,index = 0;
	scanf("%d%d%d", &N, &M,&first);
	list.head = create_node(first,NULL);
	now = list.head;
	size = N;
	for (int i = 1;i < N;i++) {
		int tmp;
		scanf("%d", &tmp);
		now->next = create_node(tmp,now);
		now = now->next;
	}
	now = list.head;
	while ((index + M) <= size && M!=1) {
		Node* scan = now->next;
		int i,prev = now->value;
		for (i = 1;i < M;i++) {
			if (prev >= scan->value) break;
			prev = scan->value;
			scan = scan->next;
		}
		if (i == M) {
			if (now == list.head) {
				list.head = scan;
				now = scan;
				list.head->prev = NULL;
			}
			else {
				now = now->prev;
				now->next = scan;
				if(scan) scan->prev = now;
				index -= (M - 1);
				index = index < 0 ? 0 : index;
				for (int i = 0;i < (M - 1);i++) {
					now = now->prev ? now->prev : now;
				}
			}
			size -= M;
		}
		else {
			index++;
			now = now->next;
		}
	}
	now = list.head;
	while(now) {
		printf("%d ", now->value);
		now = now->next;
	}
	return 0;
}