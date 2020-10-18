#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define isdigit(x) (((unsigned int)x - '0') < 10u)
void print_num(int n){
    if (n > 9){
        int a = n / 10;
        n -= 10 * a;
        print_num(a);
    }
    putchar('0' + n);
}
int main(void) {
    int N = 0, M = 0, i, j;
    char c;
    while (c = getchar(),isdigit(c)) N = N * 10 + c - '0';
    while (c = getchar(),isdigit(c)) M = M * 10 + c - '0';
    int* arr = (int*)malloc(N * sizeof(int));
    for (i = 0; i < N; ++i) {
        while (c = getchar(), c == ' ');
        if (c != '-') {
            arr[i] = c - '0';
            while (c = getchar(),isdigit(c)) arr[i] = arr[i] * 10 + c - '0';
        }
        else {
            arr[i] = getchar() - '0';
            while (c = getchar(),isdigit(c)) arr[i] = arr[i] * 10 + c - '0';
            arr[i] = ~arr[i] + 1;
        }

        if (i < M - 1) continue;
        for (j = 1; j < M && arr[i - j + 1] > arr[i - j];++j);
        if (j == M) {
            N -= M;
            i -= M;
        }
    }
    for (i = 0; i < N;++i) {
        if (arr[i] < 0) {
            putchar('-');
            arr[i] = ~arr[i] + 1;
        }
        print_num(arr[i]);
        putchar(' '); 
    }
    free(arr);
    return 0;
}
//#include<iostream>
//struct Node {
//	Node* next;
//	Node* prev;
//	int value;
//};
//int main() {
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(0);
//	int N, M;
//	Node* head, * now, * mem_head;
//	int size = 0, index = 0;
//	std::cin >> N >> M;
//	head = new Node;
//	head->prev = nullptr;
//	now = mem_head = head;
//	std::cin >> head->value;
//	size = N;
//	int prev_input = head->value,count = 0;
//	for (int i = 1;i < N;++i) {
//		int tmp;
//		std::cin >> tmp;
//		if(prev_input >= tmp)
//		head[i - 1].next = head + i;
//		head[i].prev = head + i - 1;
//		std::cin >> head[i].value;
//	}
//	
//	now = head;
//	while ((index + M) <= size) {
//		Node* scan = now->next;
//		int i, prev = now->value;
//		for (i = 1;(i < M) && (prev < scan->value);++i) {
//			prev = scan->value;
//			scan = scan->next;
//		}
//		if (i == M) {
//			if (now == head) {
//				head = now = scan;
//				head->prev = nullptr;
//				index = 0;
//			}
//			else {
//				now->prev->next = scan;
//				if (scan) scan->prev = now->prev;
//				index -= (M - 1);
//				if (index < 0) index = 0;
//				for (int j = 1;j < M && now->prev;++j) now = now->prev;
//			}
//			size -= M;
//		}
//		else {
//			index += i;
//			now = scan;
//		}
//	}
//	while (head) {
//		std::cout << head->value << ' ';
//		head = head->next;
//	}
//	delete[] mem_head;
//	return 0;
//}

//#include<iostream>
//struct Node {
//	Node* next;
//	Node* prev;
//	int value;
//};
//int main() {
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(0);
//	int N, M;
//	Node* head, * now, * mem_head,*back_check;
//	int size = 0, index = 0;
//	std::cin >> N >> M;
//	head = new Node[N];
//	head->prev = nullptr;
//	back_check = now = mem_head = head;
//	std::cin >> head[0].value;
//	size = N;
//	for (int i = 1;i < N;++i) {
//		head[i - 1].next = head + i;
//		head[i].prev = head + i - 1;
//		std::cin >> head[i].value;
//	}
//	head[N - 1].next = nullptr;
//	now = head;
//	while ((index + M) <= size) {
//		Node* scan = now->next;
//		int i, prev = now->value;
//		for (i = 1;(i < M) && (prev < scan->value);++i) {
//			prev = scan->value;
//			scan = scan->next;
//		}
//		if (i == M) {
//			if (now == head) {
//				head = now = scan;
//				head->prev = nullptr;
//				index = 0;
//			}
//			else {
//				now->prev->next = scan;
//				if (scan) scan->prev = now->prev;
//				index -= (M - 1);
//				if (index < 0) index = 0;
//				for (int j = 1;j < M && now->prev;++j) now = now->prev;
//			}
//			size -= M;
//		}
//		else {
//			index += i;
//			now = scan;
//		}
//	}
//	while (head) {
//		std::cout << head->value << ' ';
//		head = head->next;
//	}
//	delete[] mem_head;
//	return 0;
//}
//linked list�����A�Ĳv��

//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//struct Node {
//	Node* next;
//	Node* prev;
//	int value;
//};
//int main() {
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(0);
//	int N, M;
//	Node* head, * now, * mem_head,*back_check;
//	int size = 0, index = 0;
//	std::cin >> N >> M;
//	head = new Node[N];
//	head->prev = nullptr;
//	back_check = now = mem_head = head;
//	std::cin >> head[0].value;
//	size = N;
//	for (int i = 1;i < N;++i) {
//		head[i - 1].next = head + i;
//		head[i].prev = head + i - 1;
//		std::cin >> head[i].value;
//	}
//	head[N - 1].next = nullptr;
//	now = head;
//	while ((index + M) <= size) {
//		Node* scan = now->next;
//		int i, prev = now->value;
//		for (i = 1;(i < M) && (prev < scan->value);++i) {
//			prev = scan->value;
//			scan = scan->next;
//		}
//		if (i == M) {
//			if (now == head) {
//				head = now = scan;
//				head->prev = nullptr;
//				index = 0;
//			}
//			else {
//				now->prev->next = scan;
//				if (scan) scan->prev = now->prev;
//				index -= (M - 1);
//				if (index < 0) index = 0;
//				for (int j = 1;j < M && now->prev;++j) now = now->prev;
//			}
//			size -= M;
//		}
//		else {
//			index += i;
//			now = scan;
//		}
//	}
//	while (head) {
//		std::cout << head->value << ' ';
//		head = head->next;
//	}
//	delete[] mem_head;
//	return 0;
//}

//c++ array�����A�Ĳv�C
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
