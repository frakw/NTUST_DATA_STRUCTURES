#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

template<typename N,typename W>
//N ���W�ٸ�ƫ��O W���v����ƫ��O
class Node {
public:
	void init(N n,W w) {//��l�Ƹ`�I
		name = n;//��l�Ƹ`�I�W��
		weight_from_start = w;//��l�Ƹ`�I�v��
	}
	bool not_init() { return !name.size(); }//�p�G�٨S��l�ơA�W�rsize == 0
	void add_link(Node<N, W>* link,W weight) { link_to.push_back(make_pair(link,weight)); }//�[�J�s��link�A�۷����V�ؼи`�I�����лP�ӱ��䪺�v��
	N name = "";//�`�I�W��
	vector<pair<Node<N,W>*,W> > link_to;//�Ҧ���link�A�Hvector�x�s
	W weight_from_start;//�Ӹ`�I�v���ADijkstra Algorithm�������q�_�l�`�I��Ӹ`�I���v��(�̤p�v��)
	bool have_been_here = false;//Dijkstra Algorithm�������Ӹ`�I�O�_�w�g���L�F
	Node<N, W>* parent = nullptr;//���`�I�ADijkstra Algorithm�������q���Ӹ`�I���ӸӸ`�I(�̤p�v��)
};

template<typename N, typename W>
Node<N, W>* find_node_ptr(Node<N, W>* all, N name,int total) {//�q�Ҧ��`�I����즹�W�٪��`�I�A�æ^�Ǩ���СA�p�G�䤣��N�^��null
	for (int i = 0;i < total;i++) {
		if (all[i].name == name) {
			return &all[i];
		}
	}
	return nullptr;
}

template<typename N, typename W>
Node<N, W>* init_new_node(Node<N, W>* all, N name, int total) {//�q�Ҧ��`�I�}�C����l�Ʒs���`�I
	for (int i = 0;i < total;i++) {
		if (all[i].not_init()) {//���Ĥ@���٨S��l�ƪ��`�I
			all[i].init(name,0);//��l�ƸӸ`�I
			return &all[i];//�^�ǸӸ`�I���СA��K����link���B�z
		}
	}
}

template<typename N, typename W>
void print_path(Node<N, W>* now) {//�L�X�q�_�l�I����I�����j�禡�A�q���I�}�l�����`�I���j����_�l�I�A
	if (now->parent == nullptr) {//�_�l�`�I�����`�I��null
		cout << now->name;//�_�l�I�e�����[�Ů�
		return;//���j��_�l�I�ᵲ���A�}�l�^��(��X)���e�����j����
	}
	print_path(now->parent);//���j�I�s
	cout << ' ' << now->name;//���F�_�l�I�~�e���n�[�Ů�A�o�˳̫�@�ӿ�X�᭱�N�S���Ů�F
}

int main() {
	int node_num, edge_num;//�Ȧs��J�A�`�I�ơB���
	string start_node, end_node;//�Ȧs��J�A�_�l�`�I�W�١B�̲��I�W��
	cin >> node_num >> edge_num >> start_node >> end_node;//��J�Ĥ@��
	Node<string, int>* all_node = new Node<string, int>[node_num];//�ΰ}�C�x�s�Ҧ��`�I�A�ҥH���t�m�@���O����
	for (int i = 0;i < edge_num;i++) {//��J�C���䪺��T
		string from,to;//�Ȧs��J�A�_�I�B���I�W��
		int w;//�Ȧs��J�A�ӱ����v��
		cin >> from >> to >> w;

		Node<string, int>* from_ptr = find_node_ptr(all_node, from, node_num);//���_�I������
		if (!from_ptr) from_ptr = init_new_node(all_node, from, node_num);//�p�G���ЬOnull�A�N��_�I�٨S�Q��l�ơA�ҥH��l�ư_�I

		Node<string, int>* to_ptr = find_node_ptr(all_node, to, node_num);//�����I������
		if (!to_ptr) to_ptr = init_new_node(all_node, to, node_num);//�p�G���ЬOnull�A�N����I�٨S�Q��l�ơA�ҥH��l�Ʋ��I

		from_ptr->add_link(to_ptr, w);//�b�_�I���[�J�o����
	}
	//�Ҧ��`�I��l�Ƨ����A�䪺��T�]�s��C���䪺�_�I���F
	Node<string, int>* start_ptr = find_node_ptr(all_node, start_node, node_num);//�_�l�`�I����
	Node<string, int>* end_ptr = find_node_ptr(all_node, end_node, node_num);//�̲׸`�I����
	Node<string, int>* now_ptr = start_ptr;//��e���СA��e�Ҧb���`�I����
	vector<Node<string, int>*> next_posible;//�U�ӥi��e���`�I�����а}�C
	while (true) {
		now_ptr->have_been_here = true;//�]��e�`�I�w���L�A�קK����A���^��
		for (auto i : now_ptr->link_to) {//�]����e�`�I�s���X�h����(��V�V�~)
			if (i.first->have_been_here) continue;//���`�I�w���L�A���L
			if (find(next_posible.begin(), next_posible.end(), i.first)!= next_posible.end()) {//�p�G�Ӹ`�I�w�g�b�i��C����A�ˬd�O�_�ݭn��s
				if (i.first->weight_from_start > (now_ptr->weight_from_start + i.second)) {//�p�G�s���o�����񤧫e�������v����C�A�N��ݭn��s���{�b�����A�H���̵u���|
					i.first->weight_from_start = (now_ptr->weight_from_start + i.second);//��s����p���v��
					i.first->parent = now_ptr;//��s���s�����u�A�]�N�O��s���`�I
				}
			}
			else {//�Ӹ`�I�w�g�b�i��C���
				next_posible.push_back(i.first);//��i�i��C��
				i.first->weight_from_start = now_ptr->weight_from_start + i.second;//�ᤩ�v��
				i.first->parent = now_ptr;//�ᤩ���u(���`�I)
			}
		}
		if (next_posible.empty()) break;//�p�G�i��C���šA�N��S�����i�H���F�A�Ҧ��p��w�����A�����j��

		//�q�i��C���M��̤p�v���`�I��@�U�@�Ӹ`�I
		int min_weight = std::numeric_limits<int>::max();//�̤p�v���A���]����Ƴ̤j�A�H�T�O�Ĥ@���j�����������
		for (auto i : next_posible) {
			if (i->weight_from_start < min_weight) {//����p���v��
				now_ptr = i;//��s�U�Ӱj�骺��e����
				min_weight = i->weight_from_start;//��s�̤p�v��
			}
		}
		next_posible.erase(find(next_posible.begin(), next_posible.end(), now_ptr));//�U�Ӹ`�I����A�N�q�i��C���R��		
	}
	print_path(end_ptr);//�I�s���j�禡�A�L�X���|
	cout << endl << end_ptr->weight_from_start;//�L�X�̲׸`�I���v���A�N�O�Ӹ��|��total cost
	delete[] all_node;//����O����
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