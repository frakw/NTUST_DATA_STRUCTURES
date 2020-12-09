#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator> 
using namespace std;

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare�O����j�p��funciton object�A�Y�S���ǤJ�N�ιw�]��
void partition(iterator begin, iterator end, iterator& loc, compare comp = compare()) {//��piviot���諸��m(���䳣�p��A�k�䳣�j��)
	iterator left = begin, right = end;//�_�l�I�B���I
	loc = begin;//piviot�]���_�l�I
	while (true) {
		while (comp(*loc,*right) && (loc != right)) {//�q���I(right)��������A����J���ۤv�p���A�N���U
			--right;//������
		}
		if (loc == right) {//�p�G�ۤv�O�̤p���A�N��piviot����m�w�g�O���T���A�����禡
			return;
		}
		else {//�p�G���O�̤p���A�N��piviot����m����s����m�A���٤��O���T��m�A�~��
			swap(*loc, *right);//�洫
			loc = right;//piviot����s����m
		}
		while (!comp(*loc, *left) && (loc != left)) {//�q�_�I(left)���k����A����J���ۤv�j���A�N���U
			++left;//���k��
		}
		if (loc == left) {//�p�G�ۤv�O�̤j���A�N��piviot����m�w�g�O���T���A�����禡
			return;
		}
		else{//�p�G���O�̤j���A�N��piviot����m����s����m�A���٤��O���T��m�A�~��
			swap(*loc, *left);//�洫
			loc = left;//piviot����s����m
		}
	}
}

template<typename iterator, typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare�O����j�p��funciton object�A�Y�S���ǤJ�N�ιw�]��
void _quick_sort(iterator begin, iterator end, compare comp = compare()) {//quick sort�D�t��k
	iterator loc;//piviot
	partition(begin, end, loc, comp);//��piviot(begin)�A���諸��m(���䳣�p��A�k�䳣�j��)�A�ç�spiviot��m��loc
	if (begin != loc) _quick_sort(begin, loc - 1, comp);//���j�I�s�A�����F�קKiterator(loc - 1)����begin���e�A�n�����b
	if (end != loc) _quick_sort(loc + 1, end, comp);//���j�I�s�A�����F�קKiterator(loc + 1)����end����A�n�����b
}

template<typename iterator,typename compare = std::less<typename std::iterator_traits<iterator>::value_type> >
//compare�O����j�p��funciton object�A�Y�S���ǤJ�N�ιw�]��
void quick_sort(iterator begin, iterator end,compare comp = compare()) {
	//�]��iterator��end�O����̫�@��element���U�Ӧ�m�A�ҥH�n����end���^�̫�@��element�A�~���|�s���H�W
	if (distance(begin, end) <= 1) return;//���b�A�p�Gbegin end�g�A�ˡA�N����
	_quick_sort(begin, end - 1, comp);//��end���^�̫�@��element�A�I�s�u����quick sort
}


int main() {
	vector<string> sequence;
	string tmp;
	while (cin >> tmp) {//Ū���r��
		sequence.push_back(tmp);//�[��sequence
	}
	quick_sort(sequence.begin(), sequence.end());//quick sort
	cout << sequence[0];//�Ĥ@�ӿ�X�e�����[�ť�
	for (int i = 1;i < sequence.size();i++) {
		cout << ' ' << sequence[i];//�᭱����X�e�����n�[�ť�
	}
	return 0;
}
