#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<typename element,typename order>//element是heap內的資料型別(int)，order是優先權的資料型別(char)
class heap_node {//heap node的class
public:
	heap_node() {}
	heap_node(element i, order p, heap_node<element, order>* f) : data(i), priority(p),father(f) {}
	template<typename, typename> friend class heap;
private:
	element data;//資料
	order priority;//優先權
	heap_node<element, order>* father = nullptr;//父節點指標
	heap_node<element, order>* left = nullptr;//右邊小孩指標
	heap_node<element, order>* right = nullptr;//左邊小孩指標
};
enum class heap_type : bool {//heap的類型
	MIN,
	MAX
};
template<typename element, typename order>//element是heap內的資料型別(int)，order是優先權的資料型別(char)
class heap {//heap的class
public:
	heap(){}
	heap(heap_type mm):min_max(mm){}
	void insert(element in,order pr) {//插入新資料
		insert(&root, root, in, pr, 0);//呼叫真正的insert function
		++number_of_node;//節點數+1
	}
	void erase() {//刪除資料(root node)
		heap_node<element, order>* last = find_last(root,0);//找到complete binary tree最後一個node
		if (last == root) {//如果是root node，刪除就好
			delete root;
			root = nullptr;
			return;
		}
		root->priority = last->priority;//把root node的資料替代為complete binary tree最後一個node的資料
		root->data = last->data;//把root node的優先權替代為complete binary tree最後一個node的優先權
		if (last->father->left == last) {//如果最後一個node是父節點的左小孩
			last->father->left = nullptr;//父節點的左小孩設為空
		}
		else {//如果最後一個node是父節點的右小孩
			last->father->right = nullptr;//父節點的右小孩設為空
		}
		delete last;//刪除最後一個node
		fall(root);//新root node的值可能並不符合heap的規則，所以要把該值往下遞迴交換到正確位置
	}
	void erase_output() {
	//heap的輸出是把root node印出，然後erase，替代成新的root node，繼續印出root node，直到沒有節點為止
		while (number_of_node != 0) {
			cout << root->data;//輸出root node的值
			erase();//erase root node
			--number_of_node;//節點數-1
		}
	}

private:
	const heap_type min_max = heap_type::MIN;//heap類型
	heap_node<element, order>* root = nullptr;//root node
	int number_of_node = 0;//節點數
	void insert(heap_node<element, order>** now, heap_node<element, order>* father, element in, order pr,int index) {
		//now是現在節點的指標的指標，配置記憶體時才可以正確連接到，index用於確認是否為目標節點
		if (index == number_of_node) {//若現在節點的index與節點數相等，代表目前正位於新節點的位置
			*now = new heap_node<element, order>(in, pr, father);//配置新節點
			rise(*now);//新node的值可能並不符合heap的規則，所以要把該值往上遞迴交換到正確位置
			return;
		}
		if (*now != nullptr) {//不是leaf node的小孩指標且不為目標節點，就遞迴下去
			insert(&(*now)->left, *now, in, pr, index * 2 + 1);//左小孩的index為自己*2+1
			insert(&(*now)->right, *now, in, pr, index * 2 + 2);//右小孩的index為自己*2+2
		}
	}
	void rise(heap_node<element, order>* now) {//把現在節點的值往上遞迴交換到正確位置
		if (now == nullptr) return;//走到leaf node的小孩指標就停止
		if (now->father == nullptr) return;//最多走到root node就停
		if (//比較該節點與父節點的優先權決定是否需要交換節點，MIN與MAX類型的比較都涵蓋了
			(	(min_max == heap_type::MIN) && (now->father->priority > now->priority)	) ||
			(	(min_max == heap_type::MAX) && (now->father->priority < now->priority)	) ){

			swap(now->father->priority, now->priority);//交換優先權
			swap(now->father->data, now->data);//交換資料
			rise(now->father);//該值還是有可能不符合heap的規則，所以繼續遞迴往上走
		}
	}
	void fall(heap_node<element, order>* now) {//把現在節點的值往下遞迴交換到正確位置
		if (now == nullptr) return;//走到leaf node的小孩指標就停止
		heap_node<element, order>* compare;
		//往下走不像往上走只有一條路，而是可能有2條路，所以用指標存放可能會走的路
		if (now->left == nullptr || now->right == nullptr) {//若有小孩指標為null
			compare = now->left != nullptr ? now->left : now->right;//走不是null的那邊(2個都null就為null)
		}
		else {//若2個小孩都存在，往根據heap類型的方向走
			if (min_max == heap_type::MIN) compare = now->left->priority < now->right->priority ? now->left : now->right;
			//MIN類型，往優先權小的方向走
			else compare = now->left->priority > now->right->priority ? now->left : now->right;
			//MAX類型，往優先權大的方向走
		}

		if (compare == nullptr) return;//2個小孩都不存在(null)，直接結束
		if (//比較該節點與選擇子節點的優先權決定是否需要交換節點，MIN與MAX類型的比較都涵蓋了
			((min_max == heap_type::MIN) && (compare->priority < now->priority)) ||
			((min_max == heap_type::MAX) && (compare->priority > now->priority)) ){

			swap(compare->priority, now->priority);//交換優先權
			swap(compare->data, now->data);//交換資料
			fall(compare);//該值還是有可能不符合heap的規則，所以繼續遞迴往下走
		}
	}
	heap_node<element, order>* find_last(heap_node<element, order>* now,int index) {//找到complete binary tree最後一個node
		if (now == nullptr) return  nullptr;//走到leaf node的小孩指標就回傳null，表示這一分支遞迴沒有解
		if (index == number_of_node - 1) {//若該節點index與節點數-1相等，代表該節點就是complete binary tree最後一個node
			return now;//回傳
		}
		heap_node<element, order>* L_result = find_last(now->left, index * 2 + 1);//往左遞迴，左小孩的index為自己*2+1，結果暫存到L_result
		heap_node<element, order>* R_result = find_last(now->right, index * 2 + 2);//往右遞迴，右小孩的index為自己*2+2，結果暫存到R_result
		if (L_result) return L_result;//若左邊結果有解，回傳
		else if (R_result) return R_result;//若右邊結果有解，回傳
		else return nullptr;//都沒有解，回傳此分支無解
	}
};
int main() {
	string line;
	heap<char,int> all(heap_type::MIN);//創建heap，設類型為MIN
	char data,split;//暫存字元
	int pr;//暫存整數
	while (!cin.eof()) {
		cin >> data>> pr >> split;//輸入資料
		all.insert(data, pr);//插入到heap
	}
	all.erase_output();//輸出整個heap
	return 0;
}