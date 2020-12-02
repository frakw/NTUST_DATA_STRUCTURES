#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<typename element,typename order>
class heap_node {
public:
	heap_node() {}
	heap_node(element i, order p, heap_node<element, order>* f) : data(i), priority(p),father(f) {}
	template<typename, typename> friend class heap;
private:
	element data;
	order priority;
	heap_node<element, order>* father = nullptr;
	heap_node<element, order>* left = nullptr;
	heap_node<element, order>* right = nullptr;
};
enum class heap_type : bool {
	MIN,
	MAX
};
template<typename element, typename order>
class heap {
public:
	heap(){}
	heap(heap_type mm):min_max(mm){}
	void insert(element in,order pr) {
		insert(&root, root, in, pr, 0);
		++number_of_node;
	}
	void erase() {
		heap_node<element, order>* last = find_last(root,0);
		if (last == root) {
			delete root;
			root = nullptr;
			return;
		}
		swap(root->priority, last->priority);
		swap(root->data, last->data);
		if (last->father->left == last) {
			last->father->left = nullptr;
		}
		else {
			last->father->right = nullptr;
		}
		delete last;
		fall(root);
	}
	void erase_output() {
		while (number_of_node != 0) {
			cout << root->data;
			erase();
			--number_of_node;
		}
	}

private:
	heap_type min_max = heap_type::MIN;
	heap_node<element, order>* root = nullptr;
	int number_of_node = 0;
	void insert(heap_node<element, order>** now, heap_node<element, order>* father, element in, order pr,int index) {
		if (index == number_of_node) {
			*now = new heap_node<element, order>(in, pr, father);
			rise(*now);
			return;
		}
		if (*now != nullptr) {
			insert(&(*now)->left, *now, in, pr, index * 2 + 1);
			insert(&(*now)->right, *now, in, pr, index * 2 + 2);
		}
	}
	void rise(heap_node<element, order>* now) {
		if (now == nullptr) return;
		if (now->father == nullptr) return;
		if (
			(	(min_max == heap_type::MIN) && (now->father->priority > now->priority)	) ||
			(	(min_max == heap_type::MAX) && (now->father->priority < now->priority)	) ){

			swap(now->father->priority, now->priority);
			swap(now->father->data, now->data);
			rise(now->father);
		}
	}
	void fall(heap_node<element, order>* now) {
		if (now == nullptr) return;
		heap_node<element, order>* compare;
		if (now->left == nullptr || now->right == nullptr) {
			compare = now->left != nullptr ? now->left : now->right;
		}
		else {
			if (min_max == heap_type::MIN) compare = now->left->priority < now->right->priority ? now->left : now->right;
			else compare = now->left->priority > now->right->priority ? now->left : now->right;
		}

		if (compare == nullptr) return;
		if (
			((min_max == heap_type::MIN) && (compare->priority < now->priority)) ||
			((min_max == heap_type::MAX) && (compare->priority > now->priority)) ){

			swap(compare->priority, now->priority);
			swap(compare->data, now->data);
			fall(compare);
		}
	}
	heap_node<element, order>* find_last(heap_node<element, order>* now,int index) {
		if (now == nullptr) return  nullptr;
		if (index == number_of_node - 1) {
			return now;
		}
		heap_node<element, order>* L_result = find_last(now->left, index * 2 + 1);
		heap_node<element, order>* R_result = find_last(now->right, index * 2 + 2);
		if (L_result) return L_result;
		else if (R_result) return R_result;
		else return nullptr;
	}
};
int main() {
	string line;
	heap<char,int> all(heap_type::MIN);
	getline(cin, line);
	stringstream ss(line);
	char data,split;
	int pr;
	while (!ss.eof()) {
		ss >> data >> pr >> split;
		all.insert(data, pr);
	}
	all.erase_output();
	return 0;
}