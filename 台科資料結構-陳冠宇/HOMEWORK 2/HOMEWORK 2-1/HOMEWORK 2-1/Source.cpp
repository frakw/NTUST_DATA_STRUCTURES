#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template<typename T>
class BST_node {
public:
	BST_node() {}
	BST_node(T _data):data(_data) {}
	T data;
	bool avenger = false;
	BST_node<T>* father = nullptr;
	BST_node<T>* left = nullptr;
	BST_node<T>* right = nullptr;
	bool operator>(const BST_node& i) { return data > i.data; }
	bool operator>(const T& i) { return data > i; }
	bool operator>=(const BST_node& i) { return data >= i.data; }
	bool operator>=(const T& i) { return data >= i; }
	bool operator<(const BST_node& i) { return data < i.data; }
	bool operator<(const T& i) { return data < i; }
	bool operator<=(const BST_node& i) { return data <= i.data; }
	bool operator<=(const T& i) { return data <= i; }
	void del() {
		if (left != nullptr) {
			left->del();
		}
		if (right != nullptr) {
			right->del();
		}
		delete this;
	}
};

template<typename T>
class BST {
public:
	BST() {}
	~BST() {
		root->del();
	}
	BST_node<T>* root = nullptr;
	BST_node<T>* insert(T new_data) {
		if (root == nullptr) {
			root = new BST_node<T>(new_data);
			return root;
		}
		else {
			if (*root > new_data) {
				return insert(&root->left, new_data,root);				
			}
			else {
				return insert(&root->right, new_data,root);
			}
		}
	}
	void erase(T data) {
		erase(search(data));
	}
	void erase(BST_node<T>* target) {
		if (target == nullptr) return;
		if (target->left == nullptr && target->right == nullptr) {
			if (target->father == nullptr) {//delete only one node(root)
				delete target;
				root = nullptr;
				return;
			}
			if (target->father->left == target) {
				target->father->left = nullptr;
			}
			else {
				target->father->right = nullptr;
			}
			delete target;
		}
		else if (target->left == nullptr) {//右邊有小孩
			if (target->father->left == target) {
				target->father->left = target->right;
			}
			else {
				target->father->right = target->right;
			}
			target->right->father = target->father;
			delete target;
		}
		else if (target->right == nullptr) {//左邊有小孩
			if (target->father->left == target) {
				target->father->left = target->left;
			}
			else {
				target->father->right = target->left;
			}
			target->left->father = target->father;
			delete target;
		}
		else {//左右都有小孩
			BST_node<T>* replacement = largest(target->left);
			if (replacement == nullptr) replacement = smallest(target->right);
			target->data = replacement->data;
			erase(replacement);
		}
	}
	void cut_half() {
		int H = height();
		int* layer_count = new int[H] {};
		traversal(root, layer_count, 0);//find all layer number of node
		int min_diff = 2147483647;
		int cut_layer = 0;
		for (int i = 0;i < H;i++) {
			int up = 0, down = 0;
			for (int j = 0;j < H;j++) {
				(j <= i ? up : down) += layer_count[j];
			}
			if (abs(up - down) < min_diff) {
				min_diff = abs(up - down);
				cut_layer = i;
			}
		}
		BST_node<T>** forest = new BST_node<T> * [layer_count[cut_layer + 1]]{};
		int forest_index = 0;
		cut_layer_and_create_forest(root, forest, forest_index, cut_layer + 1, 0);
		in_order_output();
		cout << endl;
		for (int i = 0;i < layer_count[cut_layer + 1];i++) {
			pre_order_output(forest[i]);
			forest[i]->del();
		}
		delete[] layer_count;
		delete[] forest;
	}
	void cut_layer_and_create_forest(BST_node<T>* now, BST_node<T>** forest,int& forest_index,int target_layer, int now_layer) {
		if (now == nullptr) return;
		if (now_layer == target_layer) {
			forest[forest_index] = now;
			if (now->father->left == now) {
				now->father->left = nullptr;
			}
			else{
				now->father->right = nullptr;
			}
			forest_index++;
		}
		else {
			cut_layer_and_create_forest(now->left, forest, forest_index, target_layer, now_layer + 1);
			cut_layer_and_create_forest(now->right, forest, forest_index, target_layer, now_layer + 1);
		}
	}
	BST_node<T>* search(T data) {
		if (root == nullptr) return nullptr;
		if (*root > data) return search(root->left, data);
		else if (*root < data) return search(root->right, data);
		else return root;
	}
	BST_node<T>* largest() {
		return largest(root);
	}
	BST_node<T>* smallest() {
		return smallest(root);
	}
	int number_of_node() {
		return number_of_node(root);
	}
	void pre_order_output() {
		pre_order_output(root);
	}
	void in_order_output() {
		in_order_output(root);
	}
	void post_order_output() {
		post_order_output(root);
	}
	int height() {
		return height(root);
	}
private:
	BST_node<T>* insert(BST_node<T>** now,T new_data, BST_node<T>* father) {
		if (*now == nullptr) {
			*now = new BST_node<T>(new_data);
			(*now)->father = father;
			return *now;
		}
		else {
			if (**now > new_data) {
				return insert(&(*now)->left, new_data,*now);
			}
			else {
				return insert(&(*now)->right, new_data,*now);
			}
		}
	}
	BST_node<T>* search(BST_node<T>* now, T data) {
		if (*now > data) return search(now->left, data);
		else if (*now < data) return search(now->right, data);
		else return now;
	}
	BST_node<T>* largest(BST_node<T>* now) {
		if (now == nullptr) return nullptr;
		else if (now->right == nullptr) return now;
		BST_node<T>* R = largest(now->right);
		return R != nullptr ? R : now;
	}
	BST_node<T>* smallest(BST_node<T>* now) {
		if (now == nullptr) return nullptr;
		else if (now->left == nullptr) return now;
		BST_node<T>* L = smallest(now->left);
		return L != nullptr ? L : now;
	}
	int number_of_node(BST_node<T>* now) {
		if (now == nullptr) return 0;
		return 1 + number_of_node(now->left) + number_of_node(now->right);
	}
	void pre_order_output(BST_node<T>* now) {
		if (now == nullptr) return;
		static bool first_out = true;
		cout << (first_out ? "" : " ") << now->data;
		first_out = false;
		pre_order_output(now->left);
		pre_order_output(now->right);
	}
	void in_order_output(BST_node<T>* now) {
		if (now == nullptr) return;
		in_order_output(now->left);
		static bool first_out = true;
		cout << (first_out ? "" : " ") << now->data;
		first_out = false;
		in_order_output(now->right);
	}
	void post_order_output(BST_node<T>* now) {
		if (now == nullptr) return;
		post_order_output(now->left);
		post_order_output(now->right);
		static bool first_out = true;
		cout << (first_out ? "" : " ") << now->data;
		first_out = false;
	}
	int height(BST_node<T>* now) {
		if (now == nullptr) return 0;
		int LH = height(now->left);
		int RH = height(now->right);
		if (LH > RH) return LH + 1;
		else return RH + 1;
	}
	void traversal(BST_node<T>* now,int* layer_count,int layer) {
		if (now == nullptr) return;
		layer_count[layer]++;
		traversal(now->left, layer_count, layer + 1);
		traversal(now->right, layer_count, layer + 1);
	}
};

int main() {
	BST<int> tree;
	string line;
	int data;
	getline(cin, line);
	stringstream s(line);
	while (s >> data) {
		tree.insert(data);
	}
	tree.post_order_output();
	cout << endl;
	getline(cin, line);
	s.clear();
	s.str(line);
	while (s >> data) {
		tree.erase(data);
	}
	tree.cut_half();
	return 0;
}