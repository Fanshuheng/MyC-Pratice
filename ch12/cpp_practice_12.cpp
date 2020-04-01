//
// Created by CH on 2020/3/30.
//
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <sstream>
#include "StrBlob.h"

using namespace std;

/*单词查找程序：
 * (1)stl的综合使用（map、set、vector、string、stringstream）
 * (2)有共享数据时，使用share_ptr
 * */
class QueryResult{
public:
    QueryResult() = delete;
    QueryResult(std::string w,
                std::shared_ptr<std::set<int>> ln,
                std::shared_ptr<std::vector<std::string>> lines): word(w), lineNum(ln), file(lines){}
private:
    std::string word;
    std::shared_ptr<std::set<int>> lineNum;
    std::shared_ptr<std::vector<std::string>> file;
};

class TextQuery{
public:
    TextQuery() = delete;
    TextQuery(istream& in){
        std::vector<string>::iterator iter = lines.begin();
        while (getline(in, *iter)){
            stringstream line2word(*iter++);
            string word;
            while(line2word >> word){
                auto& lineNum = wordAndLineNum[word];
                int currentLineNum = iter - lines.begin();
                if(!lineNum){
                    lineNum.reset(new std::set<int>({currentLineNum}));
                }else{
                    lineNum->insert(currentLineNum);
                }
            }
        }
    }
    QueryResult query(const std::string& word){
        auto& lineNum = wordAndLineNum[word];
        return QueryResult(word, lineNum, make_shared<std::vector<std::string>>(lines));
    }
private:
    std::map<std::string, std::shared_ptr<std::set<int>>> wordAndLineNum;
    std::vector<std::string> lines;
};


//12.6: 练习使用shared_ptr
shared_ptr<vector<int>> getInt(istream& in){
    istream_iterator<int> in_iterator(in), eof;
    vector<int> vec(in_iterator, eof);
    return make_shared<vector<int>>(vec);
}

//12.6: 练习使用shared_ptr
void printInt(shared_ptr<vector<int>> intPtr){
    for(const auto& e : *intPtr){
        cout << e << " ";
    }
    cout <<endl;
}

int main(){
    /////*12.1.1 shared_ptr类*/

    //智能本身可以表示是否为空指针,非空指针不为0
    //使用智能指针的安全的方法:make_shared<xxx>()(返回shared_ptr类型)；可配合auto使用
    shared_ptr<string> p1, p2;
    p1 = make_shared<string>("123");
    cout << "P1 is empty?:" << p1 << ",P2 is empty?:" << p2 <<endl;
    auto p3 = make_shared<string>("321");

    //shared_ptr的拷贝和赋值（shared_ptr的拷贝或赋值操作会记录有多少个其他的shared_ptr指向这个相同内容）
    auto p4 = make_shared<int>(42);//引用计数为1
    auto q(p4);//引用计数为2

    //12.1: (1)花括号的使用（变量作用域标识符）；（2）理解shared_ptr的指针特性
    StrBlob b1;//此时b1不指向任何东西
    {
        StrBlob b2 = {"a", "b", "c"};//此时b2计数为1，指向{"a", "b", "c"}
        b1 = b2;//此时b1与b2共同指向{"a", "b", "c"},b1、b2计数均为1
        b2.push_back("about");//此时b1与b2共同指向{"a", "b", "c", "about"},b1、b2计数均为1
    }

    //12.6:练习shared_ptr的使用，两个函数在main前面
    printInt(getInt(cin));

    ////智能指针和异常
    //传统指针：程序出现异常在delete前出现异常并未能捕获时，指针无法被释放；智能指针：发生这种情况时仍会检查引用计数并决定是否释放、
    //资源管理：可以在给智能指针初始化时传入一个删除器，以便对资源进行释放管理；详细看书P416

    /////*unique_ptr*/
    //初始化
    unique_ptr<string> p_unique1(new string("abc"));
//    unique_ptr<string> p_unique2(p_unique1);//报错：不支持拷贝(例外：return)

    //所有权转移：reset、release
    unique_ptr<string> p_unique2;
    p_unique2.reset(p_unique1.release());

    //删除器（偷懒、不在这里写了）

    /////*weak_ptr*/
    //weak_ptr是为了解决shared_ptr环形引用而引入的，网上博客写得都不错，这里贴上两篇：
    //1.https://blog.csdn.net/VonSdite/article/details/81556647
    //2.https://blog.csdn.net/LLZK_/article/details/52431404    双向链表的例子
    //weak_ptr的详细内容见StrBlobPtr类



}