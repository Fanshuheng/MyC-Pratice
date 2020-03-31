//
// Created by CH on 2020/3/30.
//
#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

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

}