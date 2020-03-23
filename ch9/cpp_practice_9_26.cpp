/*
 * 3.erase使用：
    erase传入一对迭代器:e1,e2,将删除[*e1, e2),区间内的所有元素，返回删除的最后一个元素的后一个迭代器
 * */

#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    int ia[] = {1,2,3,4,5,6,7,8,9,10};
    cout << sizeof(ia) / sizeof(int) << endl;
    vector<int> vector1;
    vector1.assign(ia, ia+ sizeof(ia)/ sizeof(int));
    auto it = vector1.begin();
    while(it != vector1.begin()){
        if(*it % 2)
            it = vector1.erase(it);
        else
            ++it;
    }
    for(const auto& element:vector1){
        cout << element << " ";
    }
}