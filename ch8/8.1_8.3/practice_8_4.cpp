/*
 *  1.文件打开、读取、关闭
 *  2.isstringstream使用：
 *      isstringstream line2word("abc efg");
 *       cout<<line2word;//"abc"
 *       cout<<line2word;//"efg"
 * */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ifstream in("/home/ch/code/cpp_primer_prartice/ch8/8.1_8.3/data");//用ifstream打开文件
    if(!in){
        cerr << "打开失败" << endl;
        return -1;
    }

    string line;
    vector<string> words;
    while(getline(in, line)){//单行读取
//    while(in >> line){//单个读取
        words.push_back(line);
    }
    in.close();

    for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++){//整行输出
        cout << *iter << endl;
    }

//    for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++){//单个输出
//        istringstream line2Word(*iter);
//        string word;
//        while(line2Word >> word) cout << word << " ";
//        cout << endl;
//    }
}