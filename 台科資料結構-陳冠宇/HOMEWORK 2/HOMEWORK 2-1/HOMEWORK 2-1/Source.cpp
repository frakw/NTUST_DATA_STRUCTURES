#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template<typename T>
class BST_node {//BST節點的class
public:
	BST_node() {}
	BST_node(T _data):data(_data) {}
	T data;
	bool avenger = false;
	BST_node<T>* father = nullptr;//爸爸
	BST_node<T>* left = nullptr;//左邊的小孩
	BST_node<T>* right = nullptr;//右邊的小孩
	bool operator>(const BST_node& i) { return data > i.data; }
	bool operator>(const T& i) { return data > i; }
	bool operator>=(const BST_node& i) { return data >= i.data; }
	bool operator>=(const T& i) { return data >= i; }
	bool operator<(const BST_node& i) { return data < i.data; }
	bool operator<(const T& i) { return data < i; }
	bool operator<=(const BST_node& i) { return data <= i.data; }
	bool operator<=(const T& i) { return data <= i; }
	void del() {//遞迴刪除所有子孫節點，最後刪除自己
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
class BST {//BST的class
public:
	BST() {}
	~BST() {//釋放記憶體
		root->del();
	}
	void insert(T new_data) {//這個是從根結點出發的insert，另有重載一個可從任意指標insert的遞迴function
		if (root == nullptr) {//如果甚麼都沒有
			root = new BST_node<T>(new_data);//配置記憶體並賦值
		}
		else {
			if (*root > new_data) {//新資料較小，往左走
				insert(&root->left, new_data,root);//呼叫真正的遞迴insert	
			}
			else {//新資料較大，往右走
				insert(&root->right, new_data,root);//呼叫真正的遞迴insert
			}
		}
	}
	void erase(T data) {//呼叫search，找到指標後，呼叫erase的重載function
		erase(search(data));
	}

	void cut_half() {//Thanos Finger Snap 找到最接近切半的水平線後，將水平線以下node全部刪除
		int H = height();//樹高(有幾層)
		int* layer_count = new int[H] {};//動態配置陣列，儲存每層的node數
		traversal(root, layer_count, 0);//遞迴計算每層的node數，結果存於layer_count
		int min_diff = 2147483647;//水平線上數量與線下數量差，一開始先設很大，避免被超過
		int cut_layer = 0;//儲存最佳的水平線(層數)
		for (int i = 0;i < H;i++) {//跑過每條水平線，找最好的
			int up = 0, down = 0;//分別存水平線上數量與線下數量
			for (int j = 0;j < H;j++) {//掃過每層，把數量加到up或down
				(j <= i ? up : down) += layer_count[j];//數量加總  <= i 屬於上半層，反之下半層
			}
			if (abs(up - down) < min_diff) {//若數量差小於之前所偵測到的最小差
				min_diff = abs(up - down);//更新最小數量差
				cut_layer = i;//更新最佳水平線
			}
		}
		BST_node<T>** forest = new BST_node<T> * [layer_count[cut_layer + 1]]{};//配置森林記憶體，共有(水平線+1)層之節點數
		int forest_index = 0;//用一個變數才能call by reference，存現在種了幾棵樹
		cut_layer_and_create_forest(root, forest, forest_index, cut_layer + 1, 0);//切除水平線下節點並存到森林中，遞迴函式
		in_order_output();//切完後，輸出中序
		cout << endl;
		for (int i = 0;i < layer_count[cut_layer + 1];i++) {//跑過森林裡的每棵樹
			pre_order_output(forest[i]);//輸出前序
			forest[i]->del();//刪除此樹
		}
		delete[] layer_count;//釋放每層的node數陣列
		delete[] forest;//釋放森林
	}
	//now存現在遞迴到哪個節點，forest存切除後的樹，forest_index存現在是第幾棵樹，target_layer為(最佳水平線+1)層，now_layer為now所在層數(root為0層)
	void cut_layer_and_create_forest(BST_node<T>* now, BST_node<T>** forest,int& forest_index,int target_layer, int now_layer) {
		if (now == nullptr) return;//防呆
		if (now_layer == target_layer) {//遞迴到正確層數
			forest[forest_index] = now;//切除後的樹存入森林
			forest_index++;//下一棵樹，因為是call by reference，所以同層級的遞迴也能被更改到
			if (now->father->left == now) {//如果自己是爸爸的左小孩
				now->father->left = nullptr;//爸爸的左指標設為空，切除
			}
			else{//如果自己是爸爸的右小孩
				now->father->right = nullptr;//爸爸的右指標設為空，切除
			}
		}
		else {
			cut_layer_and_create_forest(now->left, forest, forest_index, target_layer, now_layer + 1);//從左邊開始掃，所以先遞迴左邊
			cut_layer_and_create_forest(now->right, forest, forest_index, target_layer, now_layer + 1);//遞迴右邊
		}
	}
	//以下函式是為了簡化介面，真正實作的function重載在private裡
	BST_node<T>* search(T data) { return search(root, data);}
	BST_node<T>* largest() { return largest(root);}
	BST_node<T>* smallest() {return smallest(root);}
	void pre_order_output() { pre_order_output(root);}
	void in_order_output() { in_order_output(root); }
	void post_order_output() { post_order_output(root);}
	int height() { return height(root);}
private:
	BST_node<T>* root = nullptr;//根節點的指標
	//使用指標的指標才能在下次遞迴中配置記憶體並連接上一個node
	void insert(BST_node<T>** now,T new_data, BST_node<T>* father) {
		if (*now == nullptr) {//如果甚麼都沒有
			*now = new BST_node<T>(new_data);//配置記憶體並賦值
			(*now)->father = father;
		}
		else {
			if (**now > new_data) {//新資料較小，往左走
				insert(&(*now)->left, new_data,*now);//遞迴
			}
			else {//新資料較大，往右走
				insert(&(*now)->right, new_data,*now);//遞迴
			}
		}
	}
	void erase(BST_node<T>* target) {//傳入節點指標，刪除該節點
		if (target == nullptr) return;//防呆
		int child_num = (target->left != nullptr) + (target->right != nullptr);//計算小孩數量，nullptr代表沒小孩，回傳0，反之回傳1，因此這2個判斷式相加就是小孩數量
		switch (child_num)
		{
		case 0: case 1: {//0個或1個小孩
			BST_node<T>* replacement = target->left != nullptr ? target->left : target->right;//替代節點指標，若2邊為空，則為空，若左邊為空，代表右邊有小孩，若右邊為空，代表左邊有小孩
			if (target->father == nullptr) {//如果是根結點，刪除後設root為替代節點指標
				delete target;
				root = replacement;
				return;
			}
			if (target->father->left == target) {//如果自己是爸爸的左小孩
				target->father->left = replacement;//爸爸左指標設為替代節點指標
			}
			else {//如果自己是爸爸的右小孩
				target->father->right = replacement;//爸爸右指標設為替代節點指標
			}
			if (replacement != nullptr) replacement->father = target->father;//如果替代節點指標不為空，將小孩的爸爸設為自己的爸爸
			delete target;//刪除目標
		}break;
		case 2: {//左右都有小孩
			BST_node<T>* replacement = largest(target->left);//找左子樹中最大
			target->data = replacement->data;//用左子樹中最大值替代原本的值
			erase(replacement);//刪除左子樹中最大值的node
		}break;
		default:break;
		}
	}
	BST_node<T>* search(BST_node<T>* now, T data) {//搜尋節點
		if (now == nullptr) return nullptr;
		if (*now > data) return search(now->left, data);//要找的資料小於目前節點的資料，往左走
		else if (*now < data) return search(now->right, data);//要找的資料大於目前節點的資料，往右走
		else return now;//既非大於也非小於，那就是等於
	}
	BST_node<T>* largest(BST_node<T>* now) {//回傳now以下最大值的節點，一直往右走即可
		if (now == nullptr) return nullptr;
		else if (now->right == nullptr) return now;
		return largest(now->right);
	}
	BST_node<T>* smallest(BST_node<T>* now) {//回傳now以下最小值的節點，一直往左走即可
		if (now == nullptr) return nullptr;
		else if (now->left == nullptr) return now;
		return smallest(now->left);
	}
	int height(BST_node<T>* now) {//回傳now的高度，leaf node為高度為1
		if (now == nullptr) return 0;
		int LH = height(now->left);
		int RH = height(now->right);
		return (LH > RH ? LH : RH) + 1;//左右子樹高度選大的並加上自己(1)
	}
	void traversal(BST_node<T>* now, int* layer_count, int layer) {//計算每層node數
		if (now == nullptr) return;//防呆
		layer_count[layer]++;//該層node數加1
		traversal(now->left, layer_count, layer + 1);//往左遞迴下去，下一層為layer+1
		traversal(now->right, layer_count, layer + 1);//往右遞迴下去，下一層為layer+1
	}
	void pre_order_output(BST_node<T>* now) {//前序輸出，輸出該節點，然後繼續遞迴
		if (now == nullptr) return;
		static bool first_out = true;//static讓每次遞迴都可以用相同的變數
		cout << (first_out ? "" : " ") << now->data;//第一次輸出不用加空白，後面都要
		first_out = false;//輸出完就不是第一次了
		pre_order_output(now->left);//遞迴左子樹
		pre_order_output(now->right);//遞迴右子樹
	}
	void in_order_output(BST_node<T>* now) {//中序輸出，先遞迴左子樹，然後輸出該節點，遞迴右子樹
		if (now == nullptr) return;
		in_order_output(now->left);//遞迴左子樹
		static bool first_out = true;//static讓每次遞迴都可以用相同的變數
		cout << (first_out ? "" : " ") << now->data;//第一次輸出不用加空白，後面都要
		first_out = false;//輸出完就不是第一次了
		in_order_output(now->right);//遞迴右子樹
	}
	void post_order_output(BST_node<T>* now) {//後序輸出，遞迴左子樹與右子樹，然後輸出該節點
		if (now == nullptr) return;
		post_order_output(now->left);//遞迴左子樹
		post_order_output(now->right);//遞迴右子樹
		static bool first_out = true;//static讓每次遞迴都可以用相同的變數
		cout << (first_out ? "" : " ") << now->data;//第一次輸出不用加空白，後面都要
		first_out = false;//輸出完就不是第一次了
	}
};

int main() {
	BST<int> tree;
	string line;//存一行
	int data;//暫存數字
	getline(cin, line);
	stringstream s(line);
	while (s >> data) {//用stringstream讀數字
		tree.insert(data);//插入所有數字
	}
	tree.post_order_output();//輸出後序
	cout << endl;
	getline(cin, line);
	s.clear();
	s.str(line);
	while (s >> data) {//用stringstream讀數字
		tree.erase(data);//刪除Avengers
	}
	tree.cut_half();//刪除一半node後輸出中序(上半部)、前序(下半部)
	return 0;
}