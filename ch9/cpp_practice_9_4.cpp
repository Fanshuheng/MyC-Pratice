/*
 * 1.vector用法：
    vector<int>::iterator find(vector<int>::iterator iter1, vector<int>::iterator iter2, int num){
        for(;iter1 != iter2; iter1++){
            if(*iter1 == num)return iter1;
        }return iter2;
    }
    int main() {
        vector<int> nums{1,2,3,4,5,6,7,8,9};
        cout << *find(nums.begin(), nums.end(), 8);
        return 0;
    }
 * */

#include <iostream>
#include <vector>
using namespace std;

vector<int>::iterator find(vector<int>::iterator iter1, vector<int>::iterator iter2, int num){
    for(;iter1 != iter2; iter1++){
        if(*iter1 == num)return iter1;
    }return iter2;
}

int main() {
    vector<int> nums{1,2,3,4,5,6,7,8,9};
    cout << *find(nums.begin(), nums.end(), 8);
    return 0;
}