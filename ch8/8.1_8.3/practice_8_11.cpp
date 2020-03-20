/*  1.文件读取 :
    if(argc != 2){
        cerr << "请输入文件名" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if(!in){
        cerr << "文件读取错误" << endl;
        return -1;
    }

    2.写文件：
	ofstream out(argv[2], ofstream::app);
	if(!out){
		cerr << "输出文件读取错误" << endl;
		return -1;
	}
 	out << endl
 	out.close();
*/
#include <iostream>
#include <fstream>
#include <Sales_data.h>
using namespace std;
struct PersonInfo{
	string name;
	vector<string> phones;
};