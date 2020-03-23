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
#include <algorithm>
#include <iterator>
#include <Sales_data.h>
using namespace std;

istream_iterator in_iter(cin);
istream_iterator eof_iter;

int main(int argc, char* argv[]) {

	if(argc != 3){
		cerr << "请输入文件名" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if(!in){
		cerr << "输入文件读取错误" << endl;
		return -1;
	}

	ofstream out(argv[2], ofstream::app);
    ostream_iterator out_iter(out, "/");
	if(!out){
		cerr << "输出文件读取错误" << endl;
		return -1;
	}

	std::cout << "请输入交易记录（ISBN、销售量、原价）" << std::endl;
	Sales_data total;
	if( total.read(in) ) {//输入交易记录
		Sales_data trans;
		while (trans.read(in)){//读入剩余数据
			if(total.isbn() == trans.isbn()){
				total = add(total, trans);
			}else{
				print(out, total);
				*out_iter++ << endl;
				total = trans;
			}
		}
		print(out, total);
		cout << endl;
	}else{
		cerr << "No data" << endl;
		return -1;
	}
	in.close();
	out.close();
	return 0;
}