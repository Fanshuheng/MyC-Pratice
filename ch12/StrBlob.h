//
// Created by CH on 2020/4/1.
//

#ifndef CH12_STRBLOB_H
#define CH12_STRBLOB_H
#include <iostream>
#include <vector>
#include <memory>
#include <exception>
/*编写这个类的目的：
 * (1)掌握智能指针的使用；
 * (2)掌握多对象共享数据的方法*/
/*细节：
 * (1)接受初始化列表的构造函数：StrBlob(std::initializer_list<std::string> il);
 * (2)
 * */
class StrBlob {

public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    //构造函数
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {};
    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {};
    //访问状态
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    //添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    //元素访问
    std::string &front();
    const std::string &front() const;//注：如果仅在返回类型上加上const则编译不通过，必须将this指针也声明为const才能通过;const在声明和实现都要加
    std::string &back();
    const std::string &back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    //检查data[i]，如不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};


#endif //CH12_STRBLOB_H
