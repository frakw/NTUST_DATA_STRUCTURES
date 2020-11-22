#include <iostream>
using namespace std;
template<typename T,unsigned int order>
class B_tree_node {
public:
	B_tree_node() {
		set_null();
	}
	B_tree_node(B_tree_node<T, order>* f) : father(f) {
		set_null();
	}
	B_tree_node(T new_data) {
		set_null();
		data[data_num] = new_data;
		data_num++;
	}
	B_tree_node(T new_data, B_tree_node<T, order>* f): father(f){
		set_null();
		data[data_num] = new_data;
		data_num++;
	}
	void set_null() { for (int i = 0;i < order;i++)child[i] = nullptr; }
	void leaf_insert(T new_data) {//insert to leaf node(b tree rule)
		if (child[0] != nullptr) {//not leaf node
			for (int i = 0;i < data_num;i++) {
				if (new_data < data[i]) {
					child[i]->leaf_insert(new_data);//recursive
					return;
				}
			}
			child[data_num]->leaf_insert(new_data);//if insert to last pointer
		}
		else {//leaf node
			insert(new_data,nullptr);
		}
	}
	void insert(T new_data, B_tree_node<T, order>* split_node) {//normal insert to node
		if (data_num == 0) {//new root node
			data[0] = new_data;
			child[1] = split_node;
			data_num = 1;
			return;
		}
		int i;
		for (i = 0;i < data_num;i++) {
			if (new_data < data[i]) {
				child[order] = child[order - 1];//last pointer
				for (int j = order - 2;j >= i;j--) {
					data[j + 1] = data[j];
					child[j + 1] = child[j];
				}
				data[i] = new_data;
				child[i] = child[i + 1];
				child[i + 1] = split_node;
				break;
			}
		}
		if (i == data_num) {
			data[i] = new_data;
			child[i + 1] = split_node;
		}
		data_num++;
		if (data_num == order) {//node is full
			if (father == nullptr) {//no father (root node)
				father = new B_tree_node<T, order>;
				father->child[0] = this;
			}
			father->help_child(this);
			data_num /= 2;
		}
	}
	void help_child(B_tree_node<T, order>* full) {
		B_tree_node<T, order>* split = new B_tree_node<T, order>(this);
		int index = 0;
		for (int i = full->data_num / 2 + 1;i < order;i++,index++) {
			split->data[index] = full->data[i];
			split->child[index] = full->child[i];
			if (split->child[index] != nullptr) {
				split->child[index]->father = split;
			}
		}
		split->child[index] = full->child[order];
		if (split->child[index] != nullptr) {
			split->child[index]->father = split;
		}
		split->data_num = index;
		insert(*(full->middle()), split);
	}
	T* middle() {
		if (data_num == 0) return nullptr;
		return data + (data_num / 2);
	}
	T* end() {
		if (data_num == 0) return nullptr;
		return data + data_num;
	}
	void output() {
		for (int i = 0;i < data_num;i++) {
			cout << data[i] << ((i != data_num - 1) ? " " : "");
			//cout << data[i] <<' ';
		}
	}
	B_tree_node<T, order>* find_root() {
		if (father == nullptr) return this;
		return father->find_root();
	}
	int height() {
		if (child[0] == nullptr) return 1;
		return 1 + child[0]->height();
	}
	B_tree_node<T, order>* child[order + 1];//true size == order, one for full insert	
	B_tree_node<T, order>* father = nullptr;
	T data[order];//true size == order - 1, one for full insert
	int data_num = 0;
};

template<typename T, unsigned int order>
class B_tree {
public:
	void insert(T new_data) {
		if (root == nullptr) root = new B_tree_node<T, order>(new_data);
		else {
			root->leaf_insert(new_data);
			root = root->find_root();
		}
	}
	void output() {
		output(root, 1, 1,root->height());
	}
private:
	B_tree_node<T,order>* root = nullptr;
	void output(B_tree_node<T, order>* now, int target_layer,int layer,int height) {
		if (now == nullptr || layer > target_layer || target_layer > height) return;
		static int pre_target = target_layer;
		if (pre_target != target_layer) {
			cout << endl;
		}
		pre_target = target_layer;
		if (target_layer == layer) {
			now->output();
			if (target_layer == 1) {//keep recursive
				output(root, target_layer + 1, 1, height);
			}
		}
		else {
			if (now->child[0] == nullptr) return;
			for (int i = 0;i < now->data_num + 1;i++) {
				output(now->child[i], target_layer, layer + 1, height);
				cout << (i != now->data_num ? "/ " : "");
			}
			output(root, target_layer + 1, 1, height);
		}
	}
};
int main() {
	B_tree<int,3> tree;
	int new_data;
	while (cin >> new_data) {
		tree.insert(new_data);
	}
	tree.output();
	cout << endl;
	return 0;
}