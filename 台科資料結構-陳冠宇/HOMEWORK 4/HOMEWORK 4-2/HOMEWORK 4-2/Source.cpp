#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

template<typename N,typename P>
class Edge {
public:
	Edge(N n1,N n2,P p):node1(n1),node2(n2),probability(p){}
	N node1, node2;
	P probability;
};

int which_set(vector<set<string> >& all_set,string target) {//return index of set
	for (int i = 0;i < all_set.size();i++) {
		for (auto j : all_set[i]) {
			if (target == j) {
				return i;
			}
		}
	}
	return -1;
}

int main() {
	int edge_num;
	string node1, node2;
	float probability,result =  1.0f;
	vector<Edge<string, float> > all_edge;
	vector<Edge<string, float> > MST;
	set<string> all_node;
	cin >> edge_num;
	for (int i = 0;i < edge_num;i++) {
		cin >> node1 >> node2 >> probability;
		all_edge.push_back(Edge<string, float>(node1,node2,probability));
		all_node.insert(node1);
		all_node.insert(node2);
	}
	vector<set<string> > all_set;
	for (auto i : all_node) {
		set<string> tmp;
		tmp.insert(i);
		all_set.push_back(tmp);
	}

	sort(all_edge.begin(), all_edge.end(), [](const Edge<string, float>& a, const Edge<string, float>& b) {return a.probability > b.probability;});
	for (auto i : all_edge) {
		int node1_set_index = which_set(all_set, i.node1);
		int node2_set_index = which_set(all_set, i.node2);
		if (node1_set_index != node2_set_index) {
			all_set[node1_set_index].insert(all_set[node2_set_index].begin(), all_set[node2_set_index].end());//merge two set
			all_set.erase(all_set.begin() + node2_set_index);
			result *= i.probability;
		}
	}
	if (result < 0.05) cout << 0;
	else cout << fixed << setprecision(4) << result;
	return 0;
}