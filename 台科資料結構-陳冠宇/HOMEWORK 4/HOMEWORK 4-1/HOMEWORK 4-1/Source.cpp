#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

template<typename N,typename W>
class Node {
public:
	void init(N n,W w) { 
		name = n; 
		weight_from_start = w;
	}
	bool not_init() { return !name.size(); }
	void add_link(Node<N, W>* link,W weight) { link_to.push_back(make_pair(link,weight)); }
	N name = "";
	vector<pair<Node<N,W>*,W> > link_to;
	W weight_from_start;
	bool already_output = false;
	Node<N, W>* parent = nullptr;
};

template<typename N, typename W>
Node<N, W>* find_node_ptr(Node<N, W>* all, N name,int total) {
	for (int i = 0;i < total;i++) {
		if (all[i].name == name) {
			return &all[i];
		}
	}
	return nullptr;
}

template<typename N, typename W>
Node<N, W>* init_new_node(Node<N, W>* all, N name, int total) {
	for (int i = 0;i < total;i++) {
		if (all[i].not_init()) {
			all[i].init(name,0);
			return &all[i];
		}
	}
}

template<typename N, typename W>
void print_path(Node<N, W>* now) {
	if (now->parent == nullptr) {
		cout << now->name;
		return;
	}
	print_path(now->parent);
	cout << ' ' << now->name;
}

int main() {
	int node_num, edge_num;
	string start_node, end_node;
	Node<string,int>* all_node;
	cin >> node_num >> edge_num >> start_node >> end_node;
	all_node = new Node<string, int>[node_num];
	for (int i = 0;i < edge_num;i++) {
		string from,to;
		int w;
		cin >> from >> to >> w;

		bool flag = false;
		for (int j = 0;j < node_num;j++) {
			if (all_node[j].name == from) {
				flag = true;
				Node<string, int>* to_ptr = find_node_ptr(all_node, to, node_num);
				if (!to_ptr) to_ptr = init_new_node(all_node, to, node_num);

				all_node[j].add_link(to_ptr,w);
				break;
			}
		}
		if (!flag) {
			Node<string, int>* from_ptr = init_new_node(all_node, from, node_num);

			Node<string, int>* to_ptr = find_node_ptr(all_node, to, node_num);
			if (!to_ptr) to_ptr = init_new_node(all_node, to, node_num);

			from_ptr->add_link(to_ptr, w);
		}
	}
	Node<string, int>* start_ptr = find_node_ptr(all_node, start_node, node_num);
	Node<string, int>* end_ptr = find_node_ptr(all_node, end_node, node_num);
	Node<string, int>* now_ptr = start_ptr;
	vector<Node<string, int>*> next_posible;
	start_ptr->already_output = true;
	while (true) {
		for (auto i : now_ptr->link_to) {
			if (i.first->already_output) continue;
			if (find(next_posible.begin(), next_posible.end(), i.first)!= next_posible.end()) {
				if (i.first->weight_from_start > (now_ptr->weight_from_start + i.second)) {
					i.first->weight_from_start = (now_ptr->weight_from_start + i.second);
					i.first->parent = now_ptr;
				}
			}
			else {
				next_posible.push_back(i.first);
				i.first->weight_from_start = now_ptr->weight_from_start + i.second;
				i.first->parent = now_ptr;
			}
		}
		if (!next_posible.size()) break;
		Node<string, int>* output;
		int min_weight = std::numeric_limits<int>::max();
		for (auto i : next_posible) {
			if (i->weight_from_start < min_weight) {
				output = i;
				min_weight = i->weight_from_start;
			}
		}
		next_posible.erase(find(next_posible.begin(), next_posible.end(), output));
		output->already_output = true;
		now_ptr = output;
		
	}
	print_path(end_ptr);
	cout << endl << end_ptr->weight_from_start;
	return 0;
}

/*
5 7 3 5
1 4 8
4 2 1
1 3 2
3 4 5
3 2 7
2 5 6
5 3 5
*/