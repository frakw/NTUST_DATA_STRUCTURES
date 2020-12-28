#include <fstream>
#include <string>
#include <set>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <iterator>
#include <chrono>
using namespace std;
void generate_string_subset(set<string>& result,const string target, unordered_map<string, bool>& dictionary,int recursive_layer);
//unsigned short BKDRHash(const char* str);

int main() {
	auto start = std::chrono::steady_clock::now();
	unordered_map<string, bool>  dictionary;
	ifstream dictionary_file;
	string word;
	dictionary_file.open("dictionary.txt");
	while (!dictionary_file.eof())
	{
		getline(dictionary_file, word);
		dictionary[word] = true;
	}
	ifstream input_file;
	input_file.open("input_500.txt");
	ofstream output_csv;
	output_csv.open("answer.csv");
	output_csv << "word,answer\n";
	while (!input_file.eof())
	{
		getline(input_file, word);
		output_csv << word << ',';
		if (dictionary.find(word) != dictionary.end()) {
			output_csv << "OK\n";
			continue;
		}

		set<string> result;
		generate_string_subset(result, word, dictionary, 0);
		if (result.size()) {
			output_csv << *result.begin();
			for (auto i = next(result.begin());i != result.end();i++) {
				output_csv <<' '<< *i;
			}
		}
		else {
			output_csv << "NONE";
		}
		output_csv << '\n';
	}
	
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "time: " << elapsed.count() / 1000 << " seconds " << elapsed.count() % 1000 << " milliseconds";
	return 0;
}

void generate_string_subset(set<string>& result,const string target, unordered_map<string, bool>& dictionary, int recursive_layer) {
	if (recursive_layer == 2) return;
	for (int i = 0;i <= target.length();i++) {//insert
		string insert;
		for (int j = 0, index = 0;j < target.length() + 1; j++) {
			if (j != i) {
				insert.push_back(target[index++]);
			}
			else {
				insert.push_back(' ');
			}
			
		}		
		for (char c = 'a';c <= 'z';c++) {
			insert[i] = c;
			if (dictionary.find(insert) != dictionary.end()) {
				result.insert(insert);
			}
			generate_string_subset(result, insert, dictionary, recursive_layer + 1);
		}
	}
	
	for (int i = 0;i < target.length();i++) {
		string delete_s;
		for (int j = 0;j < target.length(); j++) {
			if (j != i) {
				delete_s.push_back(target[j]);
			}
		}

		if (dictionary.find(delete_s) != dictionary.end()) {
			result.insert(delete_s);
		}

		generate_string_subset(result, delete_s, dictionary, recursive_layer + 1);
	}

	for (int i = 0;i < target.length();i++) {
		string substitute = target;
		for (char c = 'a';c <= 'z';c++) {
			substitute[i] = c;

			if (dictionary.find(substitute) != dictionary.end()) {
				result.insert(substitute);
			}

			generate_string_subset(result, substitute, dictionary, recursive_layer + 1);
		}
	}

	for (int i = 0;i < target.length()-1;i++) {
		string transpose = target;
		swap(transpose[i], transpose[i + 1]);

		if (dictionary.find(transpose) != dictionary.end()) {
			result.insert(transpose);
		}

		generate_string_subset(result, transpose, dictionary, recursive_layer + 1);
	}
}

//
//// BKDR Hash Function
//unsigned short BKDRHash(const char* str)
//{
//	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
//	unsigned int hash = 0;
//
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
//
//	return (hash & numeric_limits<unsigned short>::max());
//}
