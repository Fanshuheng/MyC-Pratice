/*
 * 4.用其他容器初始化string：
    vector<char> vector1 = {'a', 'b', 'c'};
    string str(vector1.data(), vector1.size());
 * */

#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

int main() {
    vector<char> vector1 = {'a', 'b', 'c'};
    string str(vector1.data(), vector1.size());
    cout << str;
}