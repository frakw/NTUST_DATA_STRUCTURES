#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

template<typename N,typename W>
//N 為名稱資料型別 W為權重資料型別
class Node {
public:
	void init(N n,W w) {//初始化節點
		name = n;//初始化節點名稱
		weight_from_start = w;//初始化節點權重
	}
	bool not_init() { return !name.size(); }//如果還沒初始化，名字size == 0
	void add_link(Node<N, W>* link,W weight) { link_to.push_back(make_pair(link,weight)); }//加入新的link，相當於指向目標節點的指標與該條邊的權重
	N name = "";//節點名稱
	vector<pair<Node<N,W>*,W> > link_to;//所有的link，以vector儲存
	W weight_from_start;//該節點權重，Dijkstra Algorithm中紀錄從起始節點到該節點的權重(最小權重)
	bool have_been_here = false;//Dijkstra Algorithm中紀錄該節點是否已經走過了
	Node<N, W>* parent = nullptr;//父節點，Dijkstra Algorithm中紀錄從哪個節點走來該節點(最小權重)
};

template<typename N, typename W>
Node<N, W>* find_node_ptr(Node<N, W>* all, N name,int total) {//從所有節點中找到此名稱的節點，並回傳其指標，如果找不到就回傳null
	for (int i = 0;i < total;i++) {
		if (all[i].name == name) {
			return &all[i];
		}
	}
	return nullptr;
}

template<typename N, typename W>
Node<N, W>* init_new_node(Node<N, W>* all, N name, int total) {//從所有節點陣列中初始化新的節點
	for (int i = 0;i < total;i++) {
		if (all[i].not_init()) {//找到第一個還沒初始化的節點
			all[i].init(name,0);//初始化該節點
			return &all[i];//回傳該節點指標，方便後續link的處理
		}
	}
}

template<typename N, typename W>
void print_path(Node<N, W>* now) {//印出從起始點到終點的遞迴函式，從終點開始往父節點遞迴直到起始點，
	if (now->parent == nullptr) {//起始節點的父節點為null
		cout << now->name;//起始點前面不加空格
		return;//遞迴到起始點後結束，開始回收(輸出)之前的遞迴直到
	}
	print_path(now->parent);//遞迴呼叫
	cout << ' ' << now->name;//除了起始點外前面要加空格，這樣最後一個輸出後面就沒有空格了
}

int main() {
	int node_num, edge_num;//暫存輸入，節點數、邊數
	string start_node, end_node;//暫存輸入，起始節點名稱、最終點名稱
	cin >> node_num >> edge_num >> start_node >> end_node;//輸入第一行
	Node<string, int>* all_node = new Node<string, int>[node_num];//用陣列儲存所有節點，所以先配置一塊記憶體
	for (int i = 0;i < edge_num;i++) {//輸入每個邊的資訊
		string from,to;//暫存輸入，起點、終點名稱
		int w;//暫存輸入，該條邊權重
		cin >> from >> to >> w;

		Node<string, int>* from_ptr = find_node_ptr(all_node, from, node_num);//找到起點的指標
		if (!from_ptr) from_ptr = init_new_node(all_node, from, node_num);//如果指標是null，代表起點還沒被初始化，所以初始化起點

		Node<string, int>* to_ptr = find_node_ptr(all_node, to, node_num);//找到終點的指標
		if (!to_ptr) to_ptr = init_new_node(all_node, to, node_num);//如果指標是null，代表終點還沒被初始化，所以初始化終點

		from_ptr->add_link(to_ptr, w);//在起點內加入這條邊
	}
	//所有節點初始化完畢，邊的資訊也存到每條邊的起點中了
	Node<string, int>* start_ptr = find_node_ptr(all_node, start_node, node_num);//起始節點指標
	Node<string, int>* end_ptr = find_node_ptr(all_node, end_node, node_num);//最終節點指標
	Node<string, int>* now_ptr = start_ptr;//當前指標，當前所在的節點指標
	vector<Node<string, int>*> next_posible;//下個可能前往節點的指標陣列
	while (true) {
		now_ptr->have_been_here = true;//設當前節點已走過，避免之後再走回來
		for (auto i : now_ptr->link_to) {//跑完當前節點連接出去的邊(方向向外)
			if (i.first->have_been_here) continue;//此節點已走過，跳過
			if (find(next_posible.begin(), next_posible.end(), i.first)!= next_posible.end()) {//如果該節點已經在可能列表當中，檢查是否需要更新
				if (i.first->weight_from_start > (now_ptr->weight_from_start + i.second)) {//如果新的這條路比之前走的路權重更低，代表需要更新成現在的路，以找到最短路徑
					i.first->weight_from_start = (now_ptr->weight_from_start + i.second);//更新成更小的權重
					i.first->parent = now_ptr;//更新成新的路線，也就是更新父節點
				}
			}
			else {//該節點已經在可能列表當中
				next_posible.push_back(i.first);//放進可能列表
				i.first->weight_from_start = now_ptr->weight_from_start + i.second;//賦予權重
				i.first->parent = now_ptr;//賦予路線(父節點)
			}
		}
		if (next_posible.empty()) break;//如果可能列表為空，代表沒有路可以走了，所有計算已完成，結束迴圈

		//從可能列表中尋找最小權重節點當作下一個節點
		int min_weight = std::numeric_limits<int>::max();//最小權重，先設為整數最大，以確保第一次迴圈能夠直接賦值
		for (auto i : next_posible) {
			if (i->weight_from_start < min_weight) {//找到更小的權重
				now_ptr = i;//更新下個迴圈的當前指標
				min_weight = i->weight_from_start;//更新最小權重
			}
		}
		next_posible.erase(find(next_posible.begin(), next_posible.end(), now_ptr));//下個節點找到後，就從可能列表中刪除		
	}
	print_path(end_ptr);//呼叫遞迴函式，印出路徑
	cout << endl << end_ptr->weight_from_start;//印出最終節點的權重，就是該路徑的total cost
	delete[] all_node;//釋放記憶體
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