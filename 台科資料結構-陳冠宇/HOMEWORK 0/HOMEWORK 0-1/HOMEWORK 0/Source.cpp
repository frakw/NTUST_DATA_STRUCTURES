#include <iostream>
#include <string>
using namespace std;
void symmetric_numbers(int N, int index, string front, string end);
string table[5][2] = {
    {"0" , "0"},
    {"1" , "1"},
    {"6" , "9"},
    {"8" , "8"},
    {"9" , "6"},
};
int main() {
    int N;
    while (cin >> N) {
        symmetric_numbers(N,0,"","");
        cout << endl;
    }
    return 0;
}

void symmetric_numbers(int N,int index,string front,string end) {

    if (index == (int)(N / 2)) {
        if (N % 2) {
            cout << front << '0' << end << ' ';
            cout << front << '1' << end << ' ';
            cout << front << '8' << end << ' ';
        }
        else {
            cout << front << end << ' ';
        }
    }
    else if (!index) {//index == 0
        for (int i = 1;i < 5;i++) {
            symmetric_numbers(N, index + 1, front + table[i][0], table[i][1] + end);
        }
    }
    else {
        for (int i = 0;i < 5;i++) {
            symmetric_numbers(N, index + 1, front + table[i][0], table[i][1] + end);
        }
    }

}