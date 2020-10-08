//linked list版本，效率更高
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	struct node* next;
	struct node* prev;
	int value;
} Node;

Node* create_node(int value, Node* prev)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->value = value;
	node->prev = prev;
	return node;
}
int main() {
	int N, M, first;
	Node* head, * now;
	int size = 0, index = 0;
	scanf("%d%d%d", &N, &M, &first);
	Node** backup = (Node**)malloc(N * sizeof(Node*));
	head = create_node(first, NULL);
	now = head;
	backup[0] = head;
	size = N;
	for (int i = 1;i < N;i++) {
		int tmp;
		scanf("%d", &tmp);
		now->next = create_node(tmp, now);
		now = now->next;
		backup[i] = now;
	}
	now = head;
	while ((index + M) <= size) {
		Node* scan = now->next;
		int i, prev = now->value;
		for (i = 1;i < M;i++) {
			if (prev >= scan->value) break;
			prev = scan->value;
			scan = scan->next;
		}
		if (i == M) {
			if (now == head) {
				head = now = scan;
				head->prev = NULL;
				index = 0;
			}
			else {
				now->prev->next = scan;
				if (scan) scan->prev = now->prev;
				index -= (M - 1);
				if (index < 0) index = 0;
				for (int i = 1;i < M && now->prev;i++) now = now->prev;
			}
			size -= M;
		}
		else {
			index++;
			now = now->next;
		}
	}
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
	for (int i = 0;i < N;++i)	free(backup[i]);
	free(backup);
	return 0;
}

//c++ array版本，效率低
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
