#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_SIZE 71//stack最大容量，依題目所訂
#define PUSH (size++)//push新東西進stack，並將size+1
#define POP  (--size)//從stack pop出最上面的東西，並將size-1
#define TOP  (size-1)//回傳stack最上面的東西
#define isdigit(x) ((x)>='0' && (x)<='9')//判斷是否為數字字元
using namespace std;
int my_strlen(char* input);
bool check_brackets(char* input, int length);
bool check_operator(char* input, int length);
int priority(char op);

class out {
public:
	char output[150];//不能只設70，因為很多空白要存
	int stack[MAX_SIZE];
	int size = 0;
	/*output重載<<，這裡先將class內的output陣列當作stack用，與之後計算數字用的stack不同。*/
	out& operator<<(char a) {
		output[PUSH] = a;
		return *this;
	}
	void print_result() {
		output[TOP] = '\0';//There is no space at the end of line.把最後一格空白覆蓋掉
		cout << output << endl;//輸出後序表示式
		int postfix_len = size;//因為size還要被stack運用，所以存到另一個變數裡
		size = 0;//之前的size被拿來計算index用，所以要歸零
		for (int i = 0;i < postfix_len;i++) {//後序轉數字演算法
			int index = i;
			int num = 0;
			int A, B;
			while (isdigit(output[index])) {//遇到數字就把它算出來
				num = num * 10 + output[index] - '0';
				index++;
			}
			if (index != i) {//代表有讀到數字
				stack[PUSH] = num;//push到stack
				i = index;//把i指到數字結束的地方
			}
			//若遇到運算子，拿出stack上面2個A(最上) B(第二上)，並進行B <運算子> A的運算
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
		//輸出數字主迴圈結束後stack最上面就是答案
		cout << stack[TOP] <<endl;
	}
};
int main() {
	char input[MAX_SIZE];
	char stack[MAX_SIZE];
	while (cin >> input) {
		out output;//output將轉後序的結果存入output內的stack，因為之後要算出結果，所以不能直接印出
		int size = 0, len = my_strlen(input);
		/*判斷是否invalid，我使用2個function去check，
		分別為檢查括號匹配的bool check_brackets(char* input,int length)
		與檢查運算子左右兩邊是否有運算元的bool check_operator(char* input,int length)*/
		if (!check_brackets(input, len) || !check_operator(input, len)) {
			cout << "invalid" <<endl;
			continue;
		}
		/*
		以上2個函式都回傳true後，就開始演算法的步驟，先放入'('到stack內，並在input最後加上')'，因為加入新字元，故++len，'\0'推到下一格*/
		input[len] = ')'; input[len + 1] = '\0';++len;
		stack[PUSH] = '(';
		for (int i = 0;i < len;i++) {
			int index = i;//用index跑數字之後才能判斷是否有讀入數字
			while (isdigit(input[index])) {//若為數字輸出到output，此處已重載<<符號
				output << input[index];
				index++;
			}
			if (index != i) {//代表有讀入數字，再輸出一個空白進去，以便之後計算區隔所有數字
				output << ' ';
				i = index;
			}
			switch (input[i])
			{
				case'(': {
					stack[PUSH] = '(';//遇到左括號就push進stack
				}break;
				case')': {//遇到右括號就pop並輸出直到遇到左括號
					char tmp;
					while (tmp = stack[POP], tmp != '(') output << tmp << ' ';
				}break;
				case'+':case'-':case'*':case'/':{
					//運算子透過priority比較stack最上層的優先權，若大於則pop掉，直到遇到比自己大的就停止
					while (priority(input[i]) >= priority(stack[TOP])) output << stack[POP] << ' ';
					//最後將自己push進stack
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
	int count = 0;//遇到左括號+1，右括號-1
	for (int i = 0;i < length;i++) {
		switch (input[i]) {
			case'(': {
				count++;
			}break;
			case')': {
				if (!count) return false;
				//若遇到右括號時count為0，代表沒有對應的左括號，或前面的左括號，都已被前面的右括號匹配走了
				count--;
			}break;
			default:break;
		}
	}
	if (count) return false;//括號若匹配正確count應是0，若不是 return false
	return true;
}
bool check_operator(char* input,int length) {
	if (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/' ||
		input[length - 1] == '+' || input[length - 1] == '-' || input[length - 1] == '*' || input[length - 1] == '/')return false;
	//因為下面的for迴圈會用到index-1，所以先把index==0的字元過濾掉( 第一個字元不可為任何運算子 )，for迴圈就能從1開始跑了，
	for (int i = 1;i < (length-1);i++) {
		switch (input[i])
		{
			case'+':case'-':case'*':case'/': {//用switch case 看起來比較乾淨
				if ((!isdigit(input[i - 1]) && input[i - 1] != ')') || (!isdigit(input[i + 1]) && input[i + 1] != '(')) return false;
				//判斷運算子左邊與右邊是否為對應括號或數字，相當於判斷左右邊是否有運算元
			}break;
		
			default:
				break;
		}
	}
	return true;//若正確就會完整跑完到這裡
}

int priority(char op) {
	switch (op) {
	case '*': case '/': return 0;
	case '+': case '-': return 1;
	default:            return 2;
	}
}