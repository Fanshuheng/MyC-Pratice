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
*/
#include <iostream>
#include <fstream>
#include <Sales_data.h>
using namespace std;
int main(int argc, char* argv[]) {

    if(argc != 3){
        cerr << "请输入文件名" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if(!in){
        cerr << "文件读取错误" << endl;
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
                print(cout, total);
                cout << endl;
                total = trans;
            }
        }
        print(cout, total);
        cout << endl;
    }else{
        cerr << "No data" << endl;
        return -1;
    }
    in.close();
    return 0;
}