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
#include <sstream>
using namespace std;

//读取一个文件，逐行读取（全是数字），每一行各自相加的结果保存至另一文件
int main(int argc, char** argv){
//	if(argc != 3){
//		cerr << "请输入文件名" << endl;
//		return -1;
//	}
//	ifstream in(argv[1]);
//	if(!in){
//		cerr << "输入文件读取错误" << endl;
//		return -1;
//	}
//
//	ofstream out(argv[2], ofstream::app);
//	if(!out){
//		cerr << "输出文件读取错误" << endl;
//		return -1;
//	}

    ifstream in("/home/ch/code/cpp_primer_prartice/ch8/8.1_8.3/data");
    ofstream out("/home/ch/code/cpp_primer_prartice/ch8/8.1_8.3/result", ofstream::app);
	string line, word;
	int sum = 0, num = 0;

	stringstream line2word(line);
	while(getline(in, line)){
		line2word.str(line);
		while(line2word >> num) sum+=num;
        out << sum << endl;
        sum = 0;
        num = 0;
        line2word.clear();
    }
    out.close();
	in.close();
	return 0;
}