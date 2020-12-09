#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator> 
using namespace std;

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare是比較大小的funciton object，若沒有傳入就用預設的
void partition(iterator begin, iterator end, iterator& loc, compare comp = compare()) {//把piviot放到對的位置(左邊都小於，右邊都大於)
	iterator left = begin, right = end;//起始點、終點
	loc = begin;//piviot設成起始點
	while (true) {
		while (comp(*loc,*right) && (loc != right)) {//從終點(right)往左比較，直到遇到比自己小的，就停下
			--right;//往左走
		}
		if (loc == right) {//如果自己是最小的，代表piviot的位置已經是正確的，結束函式
			return;
		}
		else {//如果不是最小的，就把piviot的位置換到新的位置，但還不是正確位置，繼續做
			swap(*loc, *right);//交換
			loc = right;//piviot指到新的位置
		}
		while (!comp(*loc, *left) && (loc != left)) {//從起點(left)往右比較，直到遇到比自己大的，就停下
			++left;//往右走
		}
		if (loc == left) {//如果自己是最大的，代表piviot的位置已經是正確的，結束函式
			return;
		}
		else{//如果不是最大的，就把piviot的位置換到新的位置，但還不是正確位置，繼續做
			swap(*loc, *left);//交換
			loc = left;//piviot指到新的位置
		}
	}
}

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare是比較大小的funciton object，若沒有傳入就用預設的
void _quick_sort(iterator begin, iterator end, compare comp = compare()) {//quick sort主演算法
	iterator loc;//piviot
	partition(begin, end, loc, comp);//把piviot(begin)，放到對的位置(左邊都小於，右邊都大於)，並更新piviot位置到loc
	if (begin != loc) _quick_sort(begin, loc - 1, comp);//遞迴呼叫，但為了避免iterator(loc - 1)指到begin之前，要做防呆
	if (end != loc) _quick_sort(loc + 1, end, comp);//遞迴呼叫，但為了避免iterator(loc + 1)指到end之後，要做防呆
}

template<typename iterator,typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare是比較大小的funciton object，若沒有傳入就用預設的
void quick_sort(iterator begin, iterator end,compare comp = compare()) {
	//因為iterator的end是指到最後一個element的下個位置，所以要先把end指回最後一個element，才不會存取違規
	if (distance(begin, end) <= 1) return;//防呆，如果begin end寫顛倒，就不做
	_quick_sort(begin, end - 1, comp);//把end指回最後一個element，呼叫真正的quick sort
}


int main() {
	vector<string> sequence;
	string tmp;
	while (cin >> tmp) {//讀取字串
		sequence.push_back(tmp);//加到sequence
	}
	quick_sort(sequence.begin(), sequence.end());//quick sort
	cout << sequence[0];//第一個輸出前面不加空白
	for (int i = 1;i < sequence.size();i++) {
		cout << ' ' << sequence[i];//後面的輸出前面都要加空白
	}
	return 0;
}
