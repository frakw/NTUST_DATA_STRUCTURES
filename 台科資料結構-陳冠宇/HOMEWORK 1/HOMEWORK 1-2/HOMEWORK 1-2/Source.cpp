#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_SIZE 71//stack�̤j�e�q�A���D�ةҭq
#define PUSH (size++)//push�s�F��istack�A�ñNsize+1
#define POP  (--size)//�qstack pop�X�̤W�����F��A�ñNsize-1
#define TOP  (size-1)//�^��stack�̤W�����F��
#define isdigit(x) ((x)>='0' && (x)<='9')//�P�_�O�_���Ʀr�r��
using namespace std;
int my_strlen(char* input);
bool check_brackets(char* input, int length);
bool check_operator(char* input, int length);
int priority(char op);

class out {
public:
	char output[150];//����u�]70�A�]���ܦh�ťխn�s
	int stack[MAX_SIZE];
	int size = 0;
	/*output����<<�A�o�̥��Nclass����output�}�C��@stack�ΡA�P����p��Ʀr�Ϊ�stack���P�C*/
	out& operator<<(char a) {
		output[PUSH] = a;
		return *this;
	}
	void print_result() {
		output[TOP] = '\0';//There is no space at the end of line.��̫�@��ť��л\��
		cout << output << endl;//��X��Ǫ�ܦ�
		int postfix_len = size;//�]��size�٭n�Qstack�B�ΡA�ҥH�s��t�@���ܼƸ�
		size = 0;//���e��size�Q���ӭp��index�ΡA�ҥH�n�k�s
		for (int i = 0;i < postfix_len;i++) {//�����Ʀr�t��k
			int index = i;
			int num = 0;
			int A, B;
			while (isdigit(output[index])) {//�J��Ʀr�N�⥦��X��
				num = num * 10 + output[index] - '0';
				index++;
			}
			if (index != i) {//�N��Ū��Ʀr
				stack[PUSH] = num;//push��stack
				i = index;//��i����Ʀr�������a��
			}
			//�Y�J��B��l�A���Xstack�W��2��A(�̤W) B(�ĤG�W)�A�öi��B <�B��l> A���B��
			switch (output[i])
			{
			case'+': {
				A = stack[POP];
				B = stack[POP];
				stack[PUSH] = B + A;
			}break;
			case'-': {
				A = stack[POP];
				B = stack[POP];
				stack[PUSH] = B - A;
			}break;
			case'*': {
				A = stack[POP];
				B = stack[POP];
				stack[PUSH] = B * A;
			}break;
			case'/': {
				A = stack[POP];
				B = stack[POP];
				stack[PUSH] = B / A;
			}break;
			case'%': {
				A = stack[POP];
				B = stack[POP];
				stack[PUSH] = B % A;
			}break;
			default:
				break;
			}
		}
		//��X�Ʀr�D�j�鵲����stack�̤W���N�O����
		cout << stack[TOP] <<endl;
	}
};
int main() {
	char input[MAX_SIZE];
	char stack[MAX_SIZE];
	while (cin >> input) {
		out output;//output�N���Ǫ����G�s�Joutput����stack�A�]������n��X���G�A�ҥH���ઽ���L�X
		int size = 0, len = my_strlen(input);
		/*�P�_�O�_invalid�A�ڨϥ�2��function�hcheck�A
		���O���ˬd�A���ǰt��bool check_brackets(char* input,int length)
		�P�ˬd�B��l���k����O�_���B�⤸��bool check_operator(char* input,int length)*/
		if (!check_brackets(input, len) || !check_operator(input, len)) {
			cout << "invalid" <<endl;
			continue;
		}
		/*
		�H�W2�Ө禡���^��true��A�N�}�l�t��k���B�J�A����J'('��stack���A�æbinput�̫�[�W')'�A�]���[�J�s�r���A�G++len�A'\0'����U�@��*/
		input[len] = ')'; input[len + 1] = '\0';++len;
		stack[PUSH] = '(';
		for (int i = 0;i < len;i++) {
			int index = i;//��index�]�Ʀr����~��P�_�O�_��Ū�J�Ʀr
			while (isdigit(input[index])) {//�Y���Ʀr��X��output�A���B�w����<<�Ÿ�
				output << input[index];
				index++;
			}
			if (index != i) {//�N��Ū�J�Ʀr�A�A��X�@�Ӫťնi�h�A�H�K����p��Ϲj�Ҧ��Ʀr
				output << ' ';
				i = index;
			}
			switch (input[i])
			{
				case'(': {
					stack[PUSH] = '(';//�J�쥪�A���Npush�istack
				}break;
				case')': {//�J��k�A���Npop�ÿ�X����J�쥪�A��
					char tmp;
					while (tmp = stack[POP], tmp != '(') output << tmp << ' ';
				}break;
				case'+':case'-':case'*':case'/':{
					//�B��l�z�Lpriority���stack�̤W�h���u���v�A�Y�j��hpop���A����J���ۤv�j���N����
					while (priority(input[i]) >= priority(stack[TOP])) output << stack[POP] << ' ';
					//�̫�N�ۤvpush�istack
					stack[PUSH] = input[i];
				}break;
				default:
					break;
			}
		}
		output.print_result();
	}
	return 0;
}

int my_strlen(char* input) {
	int index = 0;
	while (index != MAX_SIZE-1 && input[index] != '\0') index++;
	return index;
}

bool check_brackets(char* input,int length) {
	int count = 0;//�J�쥪�A��+1�A�k�A��-1
	for (int i = 0;i < length;i++) {
		switch (input[i]) {
			case'(': {
				count++;
			}break;
			case')': {
				if (!count) return false;
				//�Y�J��k�A����count��0�A�N��S�����������A���A�Ϋe�������A���A���w�Q�e�����k�A���ǰt���F
				count--;
			}break;
			default:break;
		}
	}
	if (count) return false;//�A���Y�ǰt���Tcount���O0�A�Y���O return false
	return true;
}
bool check_operator(char* input,int length) {
	if (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/' ||
		input[length - 1] == '+' || input[length - 1] == '-' || input[length - 1] == '*' || input[length - 1] == '/')return false;
	//�]���U����for�j��|�Ψ�index-1�A�ҥH����index==0���r���L�o��( �Ĥ@�Ӧr�����i������B��l )�Afor�j��N��q1�}�l�]�F�A
	for (int i = 1;i < (length-1);i++) {
		switch (input[i])
		{
			case'+':case'-':case'*':case'/': {//��switch case �ݰ_�Ӥ�����b
				if ((!isdigit(input[i - 1]) && input[i - 1] != ')') || (!isdigit(input[i + 1]) && input[i + 1] != '(')) return false;
				//�P�_�B��l����P�k��O�_�������A���μƦr�A�۷��P�_���k��O�_���B�⤸
			}break;
		
			default:
				break;
		}
	}
	return true;//�Y���T�N�|����]����o��
}

int priority(char op) {
	switch (op) {
	case '*': case '/': return 0;
	case '+': case '-': return 1;
	default:            return 2;
	}
}