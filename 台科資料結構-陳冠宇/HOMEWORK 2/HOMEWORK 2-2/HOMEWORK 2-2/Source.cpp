#include <iostream>
using namespace std;
template<typename T,unsigned int order>
class B_tree_node {//B樹節點
public:
	//constructor
	B_tree_node() {set_null();}//啥都沒
	B_tree_node(B_tree_node<T, order>* f) : father(f) {set_null();}//有給爸爸
	B_tree_node(T new_data) {//有給資料
		set_null();
		data[0] = new_data;
		data_num = 1;
	}
	B_tree_node(T new_data, B_tree_node<T, order>* f): father(f){//有給爸爸跟資料
		set_null();
		data[0] = new_data;
		data_num = 1;
	}

	B_tree_node<T, order>* father = nullptr;//爸爸指標，爆掉時找爸爸求救用
	B_tree_node<T, order>* child[order + 1];//放小孩指標，多一個位置用於放置爆掉時多出來的東西
	T data[order];//放資料，多一個位置用於放置爆掉時多出來的東西
	int data_num = 0;//資料數量   指標數 == 資料數量 + 1

	void set_null() { for (int i = 0;i <= order;i++)child[i] = nullptr; }//所有小孩設成空
	void leaf_insert(T new_data) {//B樹的insert都是從leaf node開始，爆掉了再往上長，所以這個funcition用於新資料的insert，是專屬於整棵樹的insert function
		if (child[0] != nullptr) {//不是leaf node，
			for (int i = 0;i < data_num;i++) {
				if (new_data < data[i]) {
					child[i]->leaf_insert(new_data);//遞迴下一個節點
					return;
				}
			}
			child[data_num]->leaf_insert(new_data);//上面都沒進入遞迴就會跑到這行，代表新資料大於node裡的所有資料，找最右邊的指標遞迴
		}
		else {//是leaf node
			insert(new_data,nullptr);//經過許多遞迴後成功找到leaf node，是專屬於node的insert function
		}
	}
	void insert(T new_data, B_tree_node<T, order>* split_node) {//第一個參數是新資料，第二個參數是當爆掉時node分割後的指標(右邊那側的分割)
		//特例: 新root node
		if (data_num == 0) {//如果資料數為0，代表這是原root node爆掉後產生的新root node
			data[0] = new_data;
			child[1] = split_node;//child[0]是分割後左侧(在下面的程式碼賦值)，child[1]是分割後右侧
			data_num = 1;
			return;
		}
		int i;
		for (i = 0;i < data_num;i++) {
			if (new_data < data[i]) {//找到自己的位置
				child[order] = child[order - 1];//因為要插入新資料，把舊資料往後移，指標多一個，所以額外處理最後一個指標
				for (int j = order - 2;j >= i;j--) {
					data[j + 1] = data[j];//把舊資料往後移
					child[j + 1] = child[j];//把舊指標往後移
				}
				data[i] = new_data;//插入
				child[i] = child[i + 1];//分割後的左側指標不變，但被上面的迴圈搬動了，所以搬回來
				child[i + 1] = split_node;//插入分割後的右側指標
				break;//找到位置就不用再繼續找了
			}
		}
		if (i == data_num) {//如果新資料大於所有舊資料，不用做任何搬動，放到最後就好
			data[i] = new_data;
			child[i + 1] = split_node;
		}
		data_num++;//資料數+1
		if (data_num == order) {//資料數 == order 代表node滿了，node爆掉
			if (father == nullptr) {//沒有爸爸(root node)，記憶體配置出一個爸爸
				father = new B_tree_node<T, order>;
				father->child[0] = this;//爆掉後自己就變成分割後的左侧，右側由爸爸產生並搬家
			}
			father->help_child(this);//爆掉後呼叫的function，產分割後的右侧並搬家
			data_num /= 2;//分割後的資料數是原資料數除以2
		}
	}
	void help_child(B_tree_node<T, order>* full) {//把小孩分割，並搬家，然後把小孩中間值insert到自己內部
		B_tree_node<T, order>* split = new B_tree_node<T, order>(this);//配置新的node，放置分割後的右側
		int index = 0;//用於搬家的變數，順便可得知新node資料數
		for (int i = full->data_num / 2 + 1;i < order;i++,index++) {//把小孩右側搬到新node
			split->data[index] = full->data[i];//搬資料
			split->child[index] = full->child[i];//搬指標
			if (split->child[index] != nullptr) {//小孩的小孩不為空
				split->child[index]->father = split;//小孩的小孩因為分割，所以要換新爸爸
			}
		}
		split->child[index] = full->child[order];//因為指標多一個，額外搬最後一個指標
		if (split->child[index] != nullptr) {
			split->child[index]->father = split;//小孩的小孩因為分割，所以要換新爸爸
		}
		split->data_num = index;//新node的資料數就是剛剛搬的數量
		insert(full->middle(), split);//把小孩的中間值塞到自己內部，如果自己也爆了，就再找爸爸求救
	}
	T& middle() {//回傳中間值
		return data[data_num / 2];
	}
	void output() {//輸出node資料，最後一筆不加空格
		for (int i = 0;i < data_num;i++) {
			cout << data[i] << ((i != data_num - 1) ? " " : "");
		}
	}
	B_tree_node<T, order>* find_root() {//因為root node爆掉後會換root node，所以用這個找到新的root node
		if (father == nullptr) return this;
		return father->find_root();
	}
	int height() {//該node的高度，leaf node高度為1，往上加1，因為B樹除了leaf node外都必定有至少一個小孩，且樹是平均高度的，所以直接用0號小孩地回即可
		if (child[0] == nullptr) return 1;
		return 1 + child[0]->height();
	}

};

template<typename T, unsigned int order>
class B_tree {//B樹
public:
	void insert(T new_data) {
		if (root == nullptr) root = new B_tree_node<T, order>(new_data);//如果甚麼都還沒有，就配置記憶體給root
		else {
			root->leaf_insert(new_data);//B樹是從leaf node插入的
			root = root->find_root();//root node可能會變，所以要更新
		}
	}
	void output() {//一層一層的輸出整個樹
		int H = root->height();//樹高
		for (int i = 0;i < H;i++) {
			output_layer(root, i, 0);//每一的層輸出，遞迴function
			cout << endl;
		}
	}
private:
	B_tree_node<T,order>* root = nullptr;
	void output_layer(B_tree_node<T, order>* now,int target_layer,int now_layer) {//輸出target_layer層的所有資料
		if (now == nullptr) return;//leaf node的小孩，在這裡終止遞迴
		if (target_layer != now_layer) {//不是想要的layer，就遞迴往下層走
			for (int i = 0;i < now->data_num + 1;i++) {//每一個小孩都遞迴出去
				output_layer(now->child[i], target_layer, now_layer + 1);
				cout << (i != now->data_num ? " / " : "");//node輸出後要用/區分，最後一個node輸出則不用
			}
		}
		else {//是想要輸出的層，輸出該node
			now->output();//呼叫node內部的輸出function
		}
	}
};
int main() {
	B_tree<int,3> tree;//2 3樹就是order為3的B樹
	int new_data;//暫存每個數字的變數
	while (cin >> new_data) {
		tree.insert(new_data);//插入
	}
	tree.output();//輸出整棵樹
	return 0;
}