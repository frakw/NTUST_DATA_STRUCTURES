#include <iostream>
using namespace std;
template <class T>
class vec {
public:
	T& operator[](int index) {
		return arr ? arr1[index] : arr0[index];
	}
	vec(int isize) {
		arr0 = new T[isize];
		arr1 = new T[isize];
		size = isize;
		capacity = isize;
	}
	~vec() {
		delete[] arr0;
		delete[] arr1;
	}
	void erase(int index, int num) {
		T* src, * dst;
		src = arr ? arr1 : arr0;
		dst = arr ? arr0 : arr1;
		for (int srci = 0, dsti = 0;srci < size;srci++, dsti++) {
			if (srci == index) {
				srci += num;
			}
			dst[dsti] = src[srci];
		}
		arr = !arr;
		size -= num;
	}
	//private:
	T* arr0 = nullptr;
	T* arr1 = nullptr;
	bool arr = false;//arr0=>false arr1=>true
	int size = 0;
	int capacity = 0;
};
int main() {
	int N, M;
	cin >> N >> M;
	vec<int> sequences(N);
	for (int i = 0;i < N;i++) {
		cin >> sequences.arr0[i];
	}
	int index = 0;
	while ((index + M) <= sequences.size) {
		int i;
		for (i = 1;i < M;i++) {
			if (sequences[index + i - 1] >= sequences[index + i]) break;
		}
		if (i == M) {
			sequences.erase(index, M);
			index = 0;
		}
		else index++;
	}
	for (int k = 0;k < sequences.size;k++) {
		cout << sequences[k] << ' ';
	}
	cout << endl;

	return 0;
}