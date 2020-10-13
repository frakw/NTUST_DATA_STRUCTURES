#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_SIZE 71
#define PUSH (size++)
#define POP  (--size)
#define TOP  (size-1)
#define isdigit(x) ((x)>='0' && (x)<='9')
using namespace std;
int my_strlen(char* input);
bool check_brackets(char* input, int length);
bool check_operator(char* input, int length);
int priority(char op);

class out {
public:
	char output[140];//不能只設70，因為很多空白要存
	int stack[MAX_SIZE];
	int size = 0;
	out& operator<<(char a) {
		output[PUSH] = a;
		return *this;
	}
	void print_result() {
		output[TOP] = '\0';//There is no space at the end of line.
		cout << output << endl;
		int postfix_len = size;
		size = 0;
		for (int i = 0;i < postfix_len;i++) {
			int index = i;
			int num = 0;
			int A, B;
			while (isdigit(output[index])) {
				num = num * 10 + output[index] - '0';
				index++;
			}
			if (index != i) {
				stack[PUSH] = num;
				i = index;
			}
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
		cout << stack[TOP] <<endl;
	}
};
int main() {
	char input[MAX_SIZE];
	char stack[MAX_SIZE];
	while (cin >> input) {
		out output;
		int size = 0, len = my_strlen(input);
		if (!check_brackets(input, len) || !check_operator(input, len)) {
			cout << "invalid" <<endl;
			continue;
		}
		input[len] = ')'; input[len + 1] = '\0';++len;
		stack[PUSH] = '(';
		for (int i = 0;i < len;i++) {
			int index = i;
			while (isdigit(input[index])) {
				output << input[index];
				index++;
			}
			if (index != i) {
				output << ' ';
				i = index;
			}
			switch (input[i])
			{
				case'(': {
					stack[PUSH] = '(';
				}break;
				case')': {
					char tmp;
					while (tmp = stack[POP], tmp != '(') output << tmp << ' ';
				}break;
				case'+':case'-':case'*':case'/': {
					while (priority(stack[TOP]) >= priority(input[i])) output << stack[POP] << ' ';
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
	int count = 0;
	for (int i = 0;i < length;i++) {
		switch (input[i]) {
			case'(': {
				count++;
			}break;
			case')': {
				if (!count) return false;
				count--;
			}break;
			default:break;
		}
	}
	if (count) return false;
	return true;
}
bool check_operator(char* input,int length) {
	if (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/' || input[length - 1] == '+' || input[length - 1] == '-' || input[length - 1] == '*' || input[length - 1] == '/')return false;
	for (int i = 1;i < (length-1);i++) {
		switch (input[i])
		{
			case'+':case'-':case'*':case'/': {
				if (!isdigit(input[i - 1]) && input[i - 1] != ')' && !isdigit(input[i + 1]) && input[i + 1] != '(') return false;
			}break;
		
			default:
				break;
		}
	}
	return true;
}

int priority(char op) {
	switch (op) {
	case '*': case '/': return 2;
	case '+': case '-': return 1;
	default:            return 0;
	}
}