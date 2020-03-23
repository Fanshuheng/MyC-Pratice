/*
 * 2.assign使用：
 * 当容器的元素类型相容时，assign可以用一种类型的容器，对另一种类型的容器进行初始化；另外，迭代器作为形参的构造函数也可完成这个任务
 *  list<char *> list1 = {"123", "456"};
    vector<string> vector1;
    vector1.assign(list1.begin(), list1.end());
    for(const auto& element: vector1){
        cout << element << " ";
    }
    cout << endl;
    for(const auto& element: vector2){
        cout << element << " ";
    }
 * */

#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    list<char *> list1 = {"123", "456"};
    vector<string> vector1, vector2(list1.begin(), list1.end());
    vector1.assign(list1.begin(), list1.end());
    for(const auto& element: vector1){
        cout << element << " ";
    }
    cout << endl;
    for(const auto& element: vector2){
        cout << element << " ";
    }
}