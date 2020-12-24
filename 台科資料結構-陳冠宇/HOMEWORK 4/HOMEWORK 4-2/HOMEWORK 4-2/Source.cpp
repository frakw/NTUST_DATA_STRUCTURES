#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

template<typename N,typename P>
//N ���W�ٸ�ƫ��O P��probability��ƫ��O
class Edge {
public:
	Edge(N n1,N n2,P p):node1(n1),node2(n2),probability(p){}
	N node1, node2;//�@���䦳2�Ӻ��I
	P probability;//�ӱ��䪺probability
};

int which_set(vector<set<string> >& all_set,string target) {//�^�ǸӸ`�I�b����set��(vector��index)
	for (int i = 0;i < all_set.size();i++) {//�]�L�C�Ӷ��X
		for (auto j : all_set[i]) {//�]�L���X�̪��C�Ӥ���
			if (target == j) {
				return i;//�^��index
			}
		}
	}
	return -1;
}

int main() {
	int edge_num;//���
	string node1, node2;//�Ȧs��J�A2�Ӻ��I���W��
	float probability,result =  1.0f;//�Ȧs��J�A�䪺probability result�x�s���G�A�w�]��1����~���Ҧ�probability���_��
	vector<Edge<string, float> > all_edge;//��vector�x�s�Ҧ�����
	set<string> all_node;//�`�I�S����ڪ���Ƶ��c�A��string�Ӵ��N
	cin >> edge_num;//��J���
	for (int i = 0;i < edge_num;i++) {//�]�L�C����
		cin >> node1 >> node2 >> probability;//��J�C���䪺��T
		all_edge.push_back(Edge<string, float>(node1, node2, probability));//�[��Ҧ����
		all_node.insert(node1);//�`�I�W�٥[�J���X���A�]���O���X�A�ҥH�S�����Ʒs�W�����D
		all_node.insert(node2);//�`�I�W�٥[�J���X���A�]���O���X�A�ҥH�S�����Ʒs�W�����D
	}
	//���ۥi�H�s�q(�D�۾F)���@�s�`�I�N�O���X
	vector<set<string> > all_set;//��vector�x�s�Ҧ������X
	for (auto i : all_node) {//�@�}�l�A�]�C�Ӹ`�I���O�@�Ӷ��X
		set<string> tmp;//�Ȧs���X
		tmp.insert(i);//�s�W�Ӹ`�I
		all_set.push_back(tmp);//��J�Ҧ��`�I��
	}

	sort(all_edge.begin(), all_edge.end(), [](const Edge<string, float>& a, const Edge<string, float>& b) {return a.probability > b.probability;});
	//��Ҧ�����probability�ƧǡA���D�حn�D�A�Ѥj�Ӥp
	for (auto i : all_edge) {//�q�jprobability����]��pprobability����
		int node1_set_index = which_set(all_set, i.node1);//�Ĥ@�Ӻ��I�Ҧb�����X�A�ΰ}�C(vector)��index���
		int node2_set_index = which_set(all_set, i.node2);//�ĤG�Ӻ��I�Ҧb�����X�A�ΰ}�C(vector)��index���
		if (node1_set_index != node2_set_index) {//�p�G���b�P�@�Ӷ��X�̡A�N���|�Φ��@�����A�o�����ݩ�MST���@��
			//�ѩ�o2�Ӷ��X������s���F�A�ҥH�N2�Ӷ��X�X�֬��@�Ӷ��X
			all_set[node1_set_index].insert(all_set[node2_set_index].begin(), all_set[node2_set_index].end());//����I2�Ҧb�����X�[����I1�Ҧb�����X
			all_set.erase(all_set.begin() + node2_set_index);//�R�����I2�Ҧb�����X
			result *= i.probability;//���G���W�ӱ��䪺probability
		}
	}
	if (result < 0.05) cout << 0;//���D�حn�D�A���G�p��0.05���A����0
	else cout << fixed << setprecision(4) << result;//�|�ˤ��J��p�Ʋĥ|���X
	return 0;
}