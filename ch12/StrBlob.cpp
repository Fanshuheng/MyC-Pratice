//
// Created by CH on 2020/4/1.
//

#include "StrBlob.h"
void StrBlob::check(StrBlob::size_type i, const std::string &msg) const {
    if(i >= data->size()){
        throw std::out_of_range(msg);
    }
}

std::string& StrBlob::front(){
    check(0, "front on empty StrBlob.");
    return data->front();
}

std::string& StrBlob::back() {
    check( 0, "back on empty StrBlob." );
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop back on empty StrBlob." );
    data->pop_back();
}

const std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob.");
    return data->front();
}

const std::string& StrBlob::back() const {
    check( 0, "back on empty StrBlob." );
    return data->back();
}