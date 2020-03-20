#include <iostream>
#include <stdexcept>
using namespace std;

istream& f(istream& in){
    int value;
    while( in >> value, !in.eof() ){//逗号表达式，为最后一个表达式的值
        if(in.bad()){//流已崩溃
            throw  runtime_error("IO流错误");
        }
        if(in.fail()){//IO操作失败(failbit或badbit为1)
            cerr << "数据错误，请重试" << endl;
            in.clear();//使所有bit重置
            in.ignore(100, '\n');
            continue;
        }
        cout << value << endl;
    }
    in.clear();
    return in;
}


int main() {
    std::cout << "请输入一些值" << std::endl;
    f(cin);
    return 0;
}
