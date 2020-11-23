#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template<typename T>
class BST_node {//BST�`�I��class
public:
	BST_node() {}
	BST_node(T _data):data(_data) {}
	T data;
	bool avenger = false;
	BST_node<T>* father = nullptr;//����
	BST_node<T>* left = nullptr;//���䪺�p��
	BST_node<T>* right = nullptr;//�k�䪺�p��
	bool operator>(const BST_node& i) { return data > i.data; }
	bool operator>(const T& i) { return data > i; }
	bool operator>=(const BST_node& i) { return data >= i.data; }
	bool operator>=(const T& i) { return data >= i; }
	bool operator<(const BST_node& i) { return data < i.data; }
	bool operator<(const T& i) { return data < i; }
	bool operator<=(const BST_node& i) { return data <= i.data; }
	bool operator<=(const T& i) { return data <= i; }
	void del() {//���j�R���Ҧ��l�]�`�I�A�̫�R���ۤv
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
class BST {//BST��class
public:
	BST() {}
	~BST() {//����O����
		root->del();
	}
	void insert(T new_data) {//�o�ӬO�q�ڵ��I�X�o��insert�A�t�������@�ӥi�q���N����insert�����jfunction
		if (root == nullptr) {//�p�G�ƻ򳣨S��
			root = new BST_node<T>(new_data);//�t�m�O����ý��
		}
		else {
			if (*root > new_data) {//�s��Ƹ��p�A������
				insert(&root->left, new_data,root);//�I�s�u�������jinsert	
			}
			else {//�s��Ƹ��j�A���k��
				insert(&root->right, new_data,root);//�I�s�u�������jinsert
			}
		}
	}
	void erase(T data) {//�I�ssearch�A�����Ы�A�I�serase������function
		erase(search(data));
	}

	void cut_half() {//Thanos Finger Snap ���̱�����b�������u��A�N�����u�H�Unode�����R��
		int H = height();//��(���X�h)
		int* layer_count = new int[H] {};//�ʺA�t�m�}�C�A�x�s�C�h��node��
		traversal(root, layer_count, 0);//���j�p��C�h��node�ơA���G�s��layer_count
		int min_diff = 2147483647;//�����u�W�ƶq�P�u�U�ƶq�t�A�@�}�l���]�ܤj�A�קK�Q�W�L
		int cut_layer = 0;//�x�s�̨Ϊ������u(�h��)
		for (int i = 0;i < H;i++) {//�]�L�C�������u�A��̦n��
			int up = 0, down = 0;//���O�s�����u�W�ƶq�P�u�U�ƶq
			for (int j = 0;j < H;j++) {//���L�C�h�A��ƶq�[��up��down
				(j <= i ? up : down) += layer_count[j];//�ƶq�[�`  <= i �ݩ�W�b�h�A�Ϥ��U�b�h
			}
			if (abs(up - down) < min_diff) {//�Y�ƶq�t�p�󤧫e�Ұ����쪺�̤p�t
				min_diff = abs(up - down);//��s�̤p�ƶq�t
				cut_layer = i;//��s�̨Τ����u
			}
		}
		BST_node<T>** forest = new BST_node<T> * [layer_count[cut_layer + 1]]{};//�t�m�˪L�O����A�@��(�����u+1)�h���`�I��
		int forest_index = 0;//�Τ@���ܼƤ~��call by reference�A�s�{�b�ؤF�X�ʾ�
		cut_layer_and_create_forest(root, forest, forest_index, cut_layer + 1, 0);//���������u�U�`�I�æs��˪L���A���j�禡
		in_order_output();//������A��X����
		cout << endl;
		for (int i = 0;i < layer_count[cut_layer + 1];i++) {//�]�L�˪L�̪��C�ʾ�
			pre_order_output(forest[i]);//��X�e��
			forest[i]->del();//�R������
		}
		delete[] layer_count;//����C�h��node�ư}�C
		delete[] forest;//����˪L
	}
	//now�s�{�b���j����Ӹ`�I�Aforest�s�����᪺��Aforest_index�s�{�b�O�ĴX�ʾ�Atarget_layer��(�̨Τ����u+1)�h�Anow_layer��now�Ҧb�h��(root��0�h)
	void cut_layer_and_create_forest(BST_node<T>* now, BST_node<T>** forest,int& forest_index,int target_layer, int now_layer) {
		if (now == nullptr) return;//���b
		if (now_layer == target_layer) {//���j�쥿�T�h��
			forest[forest_index] = now;//�����᪺��s�J�˪L
			forest_index++;//�U�@�ʾ�A�]���Ocall by reference�A�ҥH�P�h�Ū����j�]��Q����
			if (now->father->left == now) {//�p�G�ۤv�O���������p��
				now->father->left = nullptr;//�����������г]���šA����
			}
			else{//�p�G�ۤv�O�������k�p��
				now->father->right = nullptr;//�������k���г]���šA����
			}
		}
		else {
			cut_layer_and_create_forest(now->left, forest, forest_index, target_layer, now_layer + 1);//�q����}�l���A�ҥH�����j����
			cut_layer_and_create_forest(now->right, forest, forest_index, target_layer, now_layer + 1);//���j�k��
		}
	}
	//�H�U�禡�O���F²�Ƥ����A�u����@��function�����bprivate��
	BST_node<T>* search(T data) { return search(root, data);}
	BST_node<T>* largest() { return largest(root);}
	BST_node<T>* smallest() {return smallest(root);}
	void pre_order_output() { pre_order_output(root);}
	void in_order_output() { in_order_output(root); }
	void post_order_output() { post_order_output(root);}
	int height() { return height(root);}
private:
	BST_node<T>* root = nullptr;//�ڸ`�I������
	//�ϥΫ��Ъ����Ф~��b�U�����j���t�m�O����ós���W�@��node
	void insert(BST_node<T>** now,T new_data, BST_node<T>* father) {
		if (*now == nullptr) {//�p�G�ƻ򳣨S��
			*now = new BST_node<T>(new_data);//�t�m�O����ý��
			(*now)->father = father;
		}
		else {
			if (**now > new_data) {//�s��Ƹ��p�A������
				insert(&(*now)->left, new_data,*now);//���j
			}
			else {//�s��Ƹ��j�A���k��
				insert(&(*now)->right, new_data,*now);//���j
			}
		}
	}
	void erase(BST_node<T>* target) {//�ǤJ�`�I���СA�R���Ӹ`�I
		if (target == nullptr) return;//���b
		int child_num = (target->left != nullptr) + (target->right != nullptr);//�p��p�ļƶq�Anullptr�N��S�p�ġA�^��0�A�Ϥ��^��1�A�]���o2�ӧP�_���ۥ[�N�O�p�ļƶq
		switch (child_num)
		{
		case 0: case 1: {//0�ө�1�Ӥp��
			BST_node<T>* replacement = target->left != nullptr ? target->left : target->right;//���N�`�I���СA�Y2�䬰�šA�h���šA�Y���䬰�šA�N��k�䦳�p�ġA�Y�k�䬰�šA�N���䦳�p��
			if (target->father == nullptr) {//�p�G�O�ڵ��I�A�R����]root�����N�`�I����
				delete target;
				root = replacement;
				return;
			}
			if (target->father->left == target) {//�p�G�ۤv�O���������p��
				target->father->left = replacement;//���������г]�����N�`�I����
			}
			else {//�p�G�ۤv�O�������k�p��
				target->father->right = replacement;//�����k���г]�����N�`�I����
			}
			if (replacement != nullptr) replacement->father = target->father;//�p�G���N�`�I���Ф����šA�N�p�Ī������]���ۤv������
			delete target;//�R���ؼ�
		}break;
		case 2: {//���k�����p��
			BST_node<T>* replacement = largest(target->left);//�䥪�l�𤤳̤j
			target->data = replacement->data;//�Υ��l�𤤳̤j�ȴ��N�쥻����
			erase(replacement);//�R�����l�𤤳̤j�Ȫ�node
		}break;
		default:break;
		}
	}
	BST_node<T>* search(BST_node<T>* now, T data) {//�j�M�`�I
		if (now == nullptr) return nullptr;
		if (*now > data) return search(now->left, data);//�n�䪺��Ƥp��ثe�`�I����ơA������
		else if (*now < data) return search(now->right, data);//�n�䪺��Ƥj��ثe�`�I����ơA���k��
		else return now;//�J�D�j��]�D�p��A���N�O����
	}
	BST_node<T>* largest(BST_node<T>* now) {//�^��now�H�U�̤j�Ȫ��`�I�A�@�����k���Y�i
		if (now == nullptr) return nullptr;
		else if (now->right == nullptr) return now;
		return largest(now->right);
	}
	BST_node<T>* smallest(BST_node<T>* now) {//�^��now�H�U�̤p�Ȫ��`�I�A�@���������Y�i
		if (now == nullptr) return nullptr;
		else if (now->left == nullptr) return now;
		return smallest(now->left);
	}
	int height(BST_node<T>* now) {//�^��now�����סAleaf node�����׬�1
		if (now == nullptr) return 0;
		int LH = height(now->left);
		int RH = height(now->right);
		return (LH > RH ? LH : RH) + 1;//���k�l�𰪫׿�j���å[�W�ۤv(1)
	}
	void traversal(BST_node<T>* now, int* layer_count, int layer) {//�p��C�hnode��
		if (now == nullptr) return;//���b
		layer_count[layer]++;//�Ӽhnode�ƥ[1
		traversal(now->left, layer_count, layer + 1);//�������j�U�h�A�U�@�h��layer+1
		traversal(now->right, layer_count, layer + 1);//���k���j�U�h�A�U�@�h��layer+1
	}
	void pre_order_output(BST_node<T>* now) {//�e�ǿ�X�A��X�Ӹ`�I�A�M���~�򻼰j
		if (now == nullptr) return;
		static bool first_out = true;//static���C�����j���i�H�άۦP���ܼ�
		cout << (first_out ? "" : " ") << now->data;//�Ĥ@����X���Υ[�ťաA�᭱���n
		first_out = false;//��X���N���O�Ĥ@���F
		pre_order_output(now->left);//���j���l��
		pre_order_output(now->right);//���j�k�l��
	}
	void in_order_output(BST_node<T>* now) {//���ǿ�X�A�����j���l��A�M���X�Ӹ`�I�A���j�k�l��
		if (now == nullptr) return;
		in_order_output(now->left);//���j���l��
		static bool first_out = true;//static���C�����j���i�H�άۦP���ܼ�
		cout << (first_out ? "" : " ") << now->data;//�Ĥ@����X���Υ[�ťաA�᭱���n
		first_out = false;//��X���N���O�Ĥ@���F
		in_order_output(now->right);//���j�k�l��
	}
	void post_order_output(BST_node<T>* now) {//��ǿ�X�A���j���l��P�k�l��A�M���X�Ӹ`�I
		if (now == nullptr) return;
		post_order_output(now->left);//���j���l��
		post_order_output(now->right);//���j�k�l��
		static bool first_out = true;//static���C�����j���i�H�άۦP���ܼ�
		cout << (first_out ? "" : " ") << now->data;//�Ĥ@����X���Υ[�ťաA�᭱���n
		first_out = false;//��X���N���O�Ĥ@���F
	}
};

int main() {
	BST<int> tree;
	string line;//�s�@��
	int data;//�Ȧs�Ʀr
	getline(cin, line);
	stringstream s(line);
	while (s >> data) {//��stringstreamŪ�Ʀr
		tree.insert(data);//���J�Ҧ��Ʀr
	}
	tree.post_order_output();//��X���
	cout << endl;
	getline(cin, line);
	s.clear();
	s.str(line);
	while (s >> data) {//��stringstreamŪ�Ʀr
		tree.erase(data);//�R��Avengers
	}
	tree.cut_half();//�R���@�bnode���X����(�W�b��)�B�e��(�U�b��)
	return 0;
}