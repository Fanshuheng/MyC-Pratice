#include <iostream>
#include <Sales_data.h>
using namespace std;
int main() {
    std::cout << "请输入交易记录（ISBN、销售量、原价）" << std::endl;
    Sales_data total;
    if( total.read(cin) ) {//输入交易记录
        Sales_data trans;
        while (trans.read(cin)){//读入剩余数据
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
    return 0;
}