//
// Created by CH on 2020/4/1.
//

#include "StrBlobPtr.h"

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ptr = wptr.lock();//被绑定的shared_ptr还有没有东西，有就返回这个shared_ptr
    if(!ptr){
        throw std::runtime_error("unbound StrBlobPtr")
    }
    if(i >= ptr->size()){
        throw std::runtime_error(msg);
    }
    return ptr;
}

std::string& StrBlobPtr::deref() const {
    auto p = check(curr, "deference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}