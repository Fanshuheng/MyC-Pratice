//
// Created by CH on 2020/4/1.
//

#ifndef CH12_STRBLOBPTR_H
#define CH12_STRBLOBPTR_H


#include <cstddef>
#include <memory>
#include <vector>
#include "StrBlob.h"

class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz){}//将shared_ptr绑定到weak_ptr：wptr(a.data)
    std::string& deref() const;
    StrBlobPtr& incr();
private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    std::size_t curr;
    std::weak_ptr<std::vector<std::string>> wptr;
};
#endif //CH12_STRBLOBPTR_H
