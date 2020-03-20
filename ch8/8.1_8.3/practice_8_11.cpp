/*
 *  1.istringstream使用(分行去除空格):
 *    while(getline(cin, line)){
 *    	istringstream line2word(line);
 *    	while(line2word >> word)words.push_back(word);
 *    }
 *
 *    如果不在循环内定义istringstream，则：
 *    istringstream line2word；
 *    while(getline(cin, line)){
 *    	line2word.str(line);
 *    	while(line2word >> word)words.push_back(word);
 *    }
*/
#include <iostream>
#include <fstream>
#include <Sales_data.h>
using namespace std;
struct PersonInfo{
	string name;
	vector<string> phones;
};

int main(int argc, char** argv){
	if(argc != 2){
		cerr<< "文件名！" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if(!in){
		cerr << "读取失败" << endl;
		return -1;
	}

	string line, word;
	vector<PersonInfo> people;

	while(getline(in, line)){
		PersonInfo info;
		istringstream line2word(line);
		line2word >> info.name;
		while(line2word >> word) info.phones.push_back(word);
		people.push_back(info);
	}
}