#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<typename element,typename order>//element�Oheap������ƫ��O(int)�Aorder�O�u���v����ƫ��O(char)
class heap_node {//heap node��class
public:
	heap_node() {}
	heap_node(element i, order p, heap_node<element, order>* f) : data(i), priority(p),father(f) {}
	template<typename, typename> friend class heap;
private:
	element data;//���
	order priority;//�u���v
	heap_node<element, order>* father = nullptr;//���`�I����
	heap_node<element, order>* left = nullptr;//�k��p�ī���
	heap_node<element, order>* right = nullptr;//����p�ī���
};
enum class heap_type : bool {//heap������
	MIN,
	MAX
};
template<typename element, typename order>//element�Oheap������ƫ��O(int)�Aorder�O�u���v����ƫ��O(char)
class heap {//heap��class
public:
	heap(){}
	heap(heap_type mm):min_max(mm){}
	void insert(element in,order pr) {//���J�s���
		insert(&root, root, in, pr, 0);//�I�s�u����insert function
		++number_of_node;//�`�I��+1
	}
	void erase() {//�R�����(root node)
		heap_node<element, order>* last = find_last(root,0);//���complete binary tree�̫�@��node
		if (last == root) {//�p�G�Oroot node�A�R���N�n
			delete root;
			root = nullptr;
			return;
		}
		root->priority = last->priority;//��root node����ƴ��N��complete binary tree�̫�@��node�����
		root->data = last->data;//��root node���u���v���N��complete binary tree�̫�@��node���u���v
		if (last->father->left == last) {//�p�G�̫�@��node�O���`�I�����p��
			last->father->left = nullptr;//���`�I�����p�ĳ]����
		}
		else {//�p�G�̫�@��node�O���`�I���k�p��
			last->father->right = nullptr;//���`�I���k�p�ĳ]����
		}
		delete last;//�R���̫�@��node
		fall(root);//�sroot node���ȥi��ä��ŦXheap���W�h�A�ҥH�n��ӭȩ��U���j�洫�쥿�T��m
	}
	void erase_output() {
	//heap����X�O��root node�L�X�A�M��erase�A���N���s��root node�A�~��L�Xroot node�A����S���`�I����
		while (number_of_node != 0) {
			cout << root->data;//��Xroot node����
			erase();//erase root node
			--number_of_node;//�`�I��-1
		}
	}

private:
	const heap_type min_max = heap_type::MIN;//heap����
	heap_node<element, order>* root = nullptr;//root node
	int number_of_node = 0;//�`�I��
	void insert(heap_node<element, order>** now, heap_node<element, order>* father, element in, order pr,int index) {
		//now�O�{�b�`�I�����Ъ����СA�t�m�O����ɤ~�i�H���T�s����Aindex�Ω�T�{�O�_���ؼи`�I
		if (index == number_of_node) {//�Y�{�b�`�I��index�P�`�I�Ƭ۵��A�N��ثe�����s�`�I����m
			*now = new heap_node<element, order>(in, pr, father);//�t�m�s�`�I
			rise(*now);//�snode���ȥi��ä��ŦXheap���W�h�A�ҥH�n��ӭȩ��W���j�洫�쥿�T��m
			return;
		}
		if (*now != nullptr) {//���Oleaf node���p�ī��ХB�����ؼи`�I�A�N���j�U�h
			insert(&(*now)->left, *now, in, pr, index * 2 + 1);//���p�Ī�index���ۤv*2+1
			insert(&(*now)->right, *now, in, pr, index * 2 + 2);//�k�p�Ī�index���ۤv*2+2
		}
	}
	void rise(heap_node<element, order>* now) {//��{�b�`�I���ȩ��W���j�洫�쥿�T��m
		if (now == nullptr) return;//����leaf node���p�ī��дN����
		if (now->father == nullptr) return;//�̦h����root node�N��
		if (//����Ӹ`�I�P���`�I���u���v�M�w�O�_�ݭn�洫�`�I�AMIN�PMAX������������[�\�F
			(	(min_max == heap_type::MIN) && (now->father->priority > now->priority)	) ||
			(	(min_max == heap_type::MAX) && (now->father->priority < now->priority)	) ){

			swap(now->father->priority, now->priority);//�洫�u���v
			swap(now->father->data, now->data);//�洫���
			rise(now->father);//�ӭ��٬O���i�ण�ŦXheap���W�h�A�ҥH�~�򻼰j���W��
		}
	}
	void fall(heap_node<element, order>* now) {//��{�b�`�I���ȩ��U���j�洫�쥿�T��m
		if (now == nullptr) return;//����leaf node���p�ī��дN����
		heap_node<element, order>* compare;
		//���U���������W���u���@�����A�ӬO�i�঳2�����A�ҥH�Ϋ��Цs��i��|������
		if (now->left == nullptr || now->right == nullptr) {//�Y���p�ī��Ь�null
			compare = now->left != nullptr ? now->left : now->right;//�����Onull������(2�ӳ�null�N��null)
		}
		else {//�Y2�Ӥp�ĳ��s�b�A���ھ�heap��������V��
			if (min_max == heap_type::MIN) compare = now->left->priority < now->right->priority ? now->left : now->right;
			//MIN�����A���u���v�p����V��
			else compare = now->left->priority > now->right->priority ? now->left : now->right;
			//MAX�����A���u���v�j����V��
		}

		if (compare == nullptr) return;//2�Ӥp�ĳ����s�b(null)�A��������
		if (//����Ӹ`�I�P��ܤl�`�I���u���v�M�w�O�_�ݭn�洫�`�I�AMIN�PMAX������������[�\�F
			((min_max == heap_type::MIN) && (compare->priority < now->priority)) ||
			((min_max == heap_type::MAX) && (compare->priority > now->priority)) ){

			swap(compare->priority, now->priority);//�洫�u���v
			swap(compare->data, now->data);//�洫���
			fall(compare);//�ӭ��٬O���i�ण�ŦXheap���W�h�A�ҥH�~�򻼰j���U��
		}
	}
	heap_node<element, order>* find_last(heap_node<element, order>* now,int index) {//���complete binary tree�̫�@��node
		if (now == nullptr) return  nullptr;//����leaf node���p�ī��дN�^��null�A��ܳo�@���仼�j�S����
		if (index == number_of_node - 1) {//�Y�Ӹ`�Iindex�P�`�I��-1�۵��A�N��Ӹ`�I�N�Ocomplete binary tree�̫�@��node
			return now;//�^��
		}
		heap_node<element, order>* L_result = find_last(now->left, index * 2 + 1);//�������j�A���p�Ī�index���ۤv*2+1�A���G�Ȧs��L_result
		heap_node<element, order>* R_result = find_last(now->right, index * 2 + 2);//���k���j�A�k�p�Ī�index���ۤv*2+2�A���G�Ȧs��R_result
		if (L_result) return L_result;//�Y���䵲�G���ѡA�^��
		else if (R_result) return R_result;//�Y�k�䵲�G���ѡA�^��
		else return nullptr;//���S���ѡA�^�Ǧ�����L��
	}
};
int main() {
	string line;
	heap<char,int> all(heap_type::MIN);//�Ы�heap�A�]������MIN
	char data,split;//�Ȧs�r��
	int pr;//�Ȧs���
	while (!cin.eof()) {
		cin >> data>> pr >> split;//��J���
		all.insert(data, pr);//���J��heap
	}
	all.erase_output();//��X���heap
	return 0;
}