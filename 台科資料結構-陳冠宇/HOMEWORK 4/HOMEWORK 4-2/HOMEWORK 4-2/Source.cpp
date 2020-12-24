#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

template<typename N,typename P>
//N 為名稱資料型別 P為probability資料型別
class Edge {
public:
	Edge(N n1,N n2,P p):node1(n1),node2(n2),probability(p){}
	N node1, node2;//一條邊有2個端點
	P probability;//該條邊的probability
};

int which_set(vector<set<string> >& all_set,string target) {//回傳該節點在哪個set當中(vector的index)
	for (int i = 0;i < all_set.size();i++) {//跑過每個集合
		for (auto j : all_set[i]) {//跑過集合裡的每個元素
			if (target == j) {
				return i;//回傳index
			}
		}
	}
	return -1;
}

int main() {
	int edge_num;//邊數
	string node1, node2;//暫存輸入，2個端點的名稱
	float probability,result =  1.0f;//暫存輸入，邊的probability result儲存結果，預設為1之後才能把所有probability乘起來
	vector<Edge<string, float> > all_edge;//用vector儲存所有的邊
	set<string> all_node;//節點沒有實際的資料結構，用string來替代
	cin >> edge_num;//輸入邊數
	for (int i = 0;i < edge_num;i++) {//跑過每個邊
		cin >> node1 >> node2 >> probability;//輸入每個邊的資訊
		all_edge.push_back(Edge<string, float>(node1, node2, probability));//加到所有邊當中
		all_node.insert(node1);//節點名稱加入集合當中，因為是集合，所以沒有重複新增的問題
		all_node.insert(node2);//節點名稱加入集合當中，因為是集合，所以沒有重複新增的問題
	}
	//互相可以連通(非相鄰)的一群節點就是集合
	vector<set<string> > all_set;//用vector儲存所有的集合
	for (auto i : all_node) {//一開始，設每個節點都是一個集合
		set<string> tmp;//暫存集合
		tmp.insert(i);//新增該節點
		all_set.push_back(tmp);//放入所有節點中
	}

	sort(all_edge.begin(), all_edge.end(), [](const Edge<string, float>& a, const Edge<string, float>& b) {return a.probability > b.probability;});
	//對所有邊比較probability排序，依題目要求，由大而小
	for (auto i : all_edge) {//從大probability的邊跑到小probability的邊
		int node1_set_index = which_set(all_set, i.node1);//第一個端點所在的集合，用陣列(vector)的index表示
		int node2_set_index = which_set(all_set, i.node2);//第二個端點所在的集合，用陣列(vector)的index表示
		if (node1_set_index != node2_set_index) {//如果不在同一個集合裡，代表不會形成一個環，這條邊屬於MST的一員
			//由於這2個集合間有邊連接了，所以將2個集合合併為一個集合
			all_set[node1_set_index].insert(all_set[node2_set_index].begin(), all_set[node2_set_index].end());//把端點2所在的集合加到端點1所在的集合
			all_set.erase(all_set.begin() + node2_set_index);//刪除端點2所在的集合
			result *= i.probability;//結果乘上該條邊的probability
		}
	}
	if (result < 0.05) cout << 0;//依題目要求，結果小於0.05的，視為0
	else cout << fixed << setprecision(4) << result;//四捨五入到小數第四位輸出
	return 0;
}