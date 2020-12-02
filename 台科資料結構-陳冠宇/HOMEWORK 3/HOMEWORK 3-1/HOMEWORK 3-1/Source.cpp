#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <typeinfo>  
using namespace std;

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
void partition(iterator begin, iterator end, iterator& loc, compare comp = compare()) {
	iterator left = begin, right = end;
	loc = begin;
	while (true) {
		while (comp(*loc,*right) && (loc != right)) {
			--right;
		}
		if (loc == right) {
			return;
		}
		else {
			swap(*loc, *right);
			loc = right;
		}
		while (!comp(*loc, *left) && (loc != left)) {
			++left;
		}
		if (loc == left) {
			return;
		}
		else{
			swap(*loc, *left);
			loc = left;
		}
	}
}

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
void _quick_sort(iterator begin, iterator end, compare comp = compare()) {
	iterator loc;
	partition(begin, end, loc, comp);
	if (begin != loc) _quick_sort(begin, loc - 1, comp);//iterator special
	if (end != loc) _quick_sort(loc + 1, end, comp);//iterator special
}

template<typename iterator,typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
void quick_sort(iterator begin, iterator end,compare comp = compare()) {
	if (distance(begin, end) <= 1) return;
	_quick_sort(begin, end - 1, comp);//iterator special
}


int main() {
	vector<string> sequence;
	string tmp;
	while (cin >> tmp) {
		sequence.push_back(tmp);
	}
	quick_sort(sequence.begin(), sequence.end());
	cout << sequence[0];
	for (int i = 1;i < sequence.size();i++) {
		cout << ' ' << sequence[i];
	}
	return 0;
}
