#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
int main(){
    vector<int> vector1{1,2,3,4,5,6,7,8,9,0};
    auto val = 3;
    auto result = find(vector1.begin(), vector1.end(), val);
    cout << result - vector1.begin();
}