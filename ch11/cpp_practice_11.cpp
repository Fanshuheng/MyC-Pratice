//
// Created by CH on 2020/3/25.
//
#include <map>
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <list>
#include <utility>
using namespace std;

//假的小于等于，用于11.2.2
bool fakeLessThan(const int& lhs, const int& rhs){
    return lhs >= rhs;
}

//以下三个函数用于11.3.6
void translate(const map<string, string> &rule_map, ifstream &input_file, ofstream &result_file){
    string line, word;
    stringstream line2word;
    while(getline(input_file, line)){
        line2word.str(line);
        while(line2word >> word){
            auto find_word_in_rule = rule_map.find(word);
            if (find_word_in_rule!=rule_map.end()){
                result_file << find_word_in_rule->second <<" ";
            }else{
                result_file << word << " ";
            }
        }
        line2word.clear();
        result_file << endl;
    }
}

map<string, string> get_rule_map(const string& path){
    ifstream in(path);
    stringstream rule_string;
    string word_before, word_after, line;
    map<string, string> ruleMap;
    while(getline(in, line)){
        rule_string.str(line);
        rule_string >> word_before >> word_after;
        rule_string.clear();
        ruleMap.insert(make_pair(word_before, word_after));//insert and make_pair
    }
    in.close();
    return ruleMap;
}


int main(){
    /////*11.1 使用关联容器*/
    //单词计数程序:map的使用
    map<string, int> string2IntMap;
    istream_iterator<string> inIterator(cin), eof_iterator;
    vector<string> stringVector(inIterator, eof_iterator);
    for(const auto&  element : stringVector){
        ++string2IntMap[element];
    }
    for(const auto& element : string2IntMap){
        cout << element.first << ":" << element.second << " " << endl;
    }

    //单词计数程序:set和map的使用
    map<string, int> string2IntMap0;
    set<string> excludeSet = {"hey", "hello", "oh"};
    istream_iterator<string> inIterator0(cin), eof_iterator0;
    vector<string> stringVector0(inIterator0, eof_iterator0);
    for(const auto&  element : stringVector0){
        if(excludeSet.find(element)==excludeSet.end()){
            ++string2IntMap0[element];
        }
    }
    for(const auto& element : string2IntMap0){
        cout << element.first << ":" << element.second << " " << endl;
    }

    ////11.4
    istream_iterator<string> inIterator2(cin), eofIterator2;//获取输入
    vector<string> stringVector2(inIterator2, eofIterator2);
    for_each(stringVector2.begin(), stringVector2.end(),[](string& s){
        for(auto iter = s.begin(); iter!=s.end();iter++){
            if( *iter >= 65 && *iter <= 90 ){
                *iter = *iter + 32;
            }
        }
    });
    map<string, int> stringMap2;
    for(const auto& e : stringVector2){
        ++stringMap2[e];
    }
    for(const auto& element : stringMap2){
        cout << element.first << ":" << element.second << " " << endl;
    }

    /////*11.2 关联容器概述*/
    ////11.2.1定义关联容器
    //map and set:map和set中不允许存在相同的元素（map：相同键值即相同元素）
    set<string> set1 = {"1", "2", "3"};
    map<string, string> map1 = { {"1", "hey"}, {"2", "hello"} };

    //multimap and multiset（multi版本允许出现重复）
    multimap<string, string> multimap1 = { {"1", "hello"}, {"1", "hello"} };
    map<string, string> map2 = { {"1", "hello"}, {"1", "hello"} };
    cout << "Size of multimap1:" << multimap1.size() << endl;
    cout << "Size of map2:" << map2.size() << endl;

    //11.2.2 自定义关键字比较函数（map和set要求关键字实现<比较操作，因为元素的排序会调用元素的<操作符）
    map<int, int, decltype(fakeLessThan)*> map3(fakeLessThan);
    map3 = { {1,2}, {3,4}, {0, 2}};
    for(const auto& e : map3){
        cout << "First:" << e.first << ":" << e.second << " ";//First:3:4 First:1:2 First:0:2
    }
    cout << endl;

    //11.9 定义一个map<string, list<int>>,记录读取的文件中每个单词出现的行数
    map<string, list<int>> map4;
    ifstream in("E:\\MyThing\\MyThings\\code\\cpp\\cpp_primer_practice\\MyC-Pratice\\ch11\\words.txt");
    string line, word;
    stringstream line2word;
    int i = 0;
    while(getline(in, line)){
        i++;
        line2word.str(line);
        while(line2word >> word)
            map4[word].push_back(i);
        line2word.clear();
    }
    for(const auto& e:map4){
        cout << "Word:" << e.first << "," << "line:" << " ";
        for(const auto& q:e.second){
            cout << q << " ";
        }
        cout << endl;
    }
    in.close();

    ////11.2.3 pair(#include<utility>):
    //11.12:读取有string和int的序列，存在一个vector<pair>中
    ifstream in2("E:\\MyThing\\MyThings\\code\\cpp\\cpp_primer_practice\\MyC-Pratice\\ch11\\string_int.txt");
    string line2, wordString1;
    int wordInt1;
    stringstream line2word2;
    vector<pair<string, int>> vectorPair1;
    while(getline(in2, line2)){
        line2word2.str(line2);
        line2word2 >> wordString1 >> wordInt1;
        line2word2.clear();
        vectorPair1.push_back(make_pair(wordString1, wordInt1));
    }
    for(const auto& e:vectorPair1){
        cout << "String:" << e.first <<" "<<"Int:" << e.second << endl;
    }
    in2.close();
    /////*11.3 关联容器操作*/

    ////成员类型:key_type, value_type

    ////11.3.1 关联容器迭代器(一般不对关联容器用泛型算法；只读型算法可以用)
    //一般用于遍历
    map<string, int> map5 = {{"one", 1}, {"two", 2}};
    for(auto iter = map5.cbegin(); iter != map5.cend(); iter++){
        cout << "String:" << iter->first <<" "<<"Int:" << iter->second << endl;
    }

    ////11.3.2 添加元素 （insert，迭代器范围(set)、初始化列表{}(set)、make_pair(map), {}pair(map)）
    //这里仅仅给一个例子
    map<string, int> map6;
    map6.insert({"one", 1});
    cout << "String:" << map6.begin()->first <<" "<<"Int:" << map6.begin()->second << endl;

    //insert的返回值:返回一个pair；如果插入成功则这个pair的second为true,无论成功与否，first一定为指向这个元素的迭代器;mutli版本的只返回一个指向新元素的迭代器
    map<string, int> string2IntMap3;
    istream_iterator<string> inIterator1(cin), eof_iterator1;
    vector<string> stringVector3(inIterator1, eof_iterator1);
    for(const auto&  element : stringVector3){
            auto retPair = string2IntMap3.insert(make_pair(element, 1));
            if(!retPair.second){
                ++(retPair.first->second);
            }
    }
    for(const auto& element : string2IntMap3){
        cout << element.first << ":" << element.second << " " << endl;
    }

    ////11.3.3 erase:erase有三个版本：迭代器范围版本，返回后一个迭代器；迭代器版本：删除指定迭代器指向的元素，返回这个元素后一个元素的迭代器；关键字版本：删除关键字对应的元素，返回删除的数量

    ////11.3.4 下标操作：只有map和unorder_map有(at(), [])；如无目标键值则自动插入一个
    map<string, int> map7 = {{"one", 1}};
    map7["two"] = 1;
//    map7.at("three") = 2;//报错：at只能对已有的键值用
    for(const auto& element : map7){
        cout << element.first << ":" << element.second << " " << endl;
    }

    ////11.3.5 访问元素：

    //find（适用于有序和无序容器）:给出第一个目标元素的迭代器
    set<int> set2 = {1,2,3,4,5};
    auto setIter1 = set2.find(1);
    cout << *setIter1 << endl;

    //count(适用于有序和无序容器)：给出目标元素的出现次数
    set<int> set3 = {1,2,3,4,5};
    auto setIter2 = set2.count(1);
    cout << setIter2 << endl;

    //multiple版本：multiple版本的相同键值元素是相邻存储的
    //相邻存储示例
    multimap<string, int> multimap2 = {{"one", 1}, {"two", 2}, {"one", 2}, {"one", 3}};
    for(auto i = multimap2.begin(); i!=multimap2.end(); i++){
        cout << i->first << ":" << i->second << " " ;//one:1 one:2 two:2
    }
    cout << endl;

    //循环查找同一键值的所有项(count和find版本)
    auto num1 = multimap2.count("one");
    auto iterMultimap = multimap2.find("one");
    while(num1--){
        cout << iterMultimap++->second << " ";
    }
    cout << endl;

    //循环查找同一键值的所有项(equal_range版本)
    auto pairMultimap = multimap2.equal_range("one");
    while (pairMultimap.first!=pairMultimap.second){
        cout << pairMultimap.first->second << " ";
        pairMultimap.first++;
    }
    cout << endl;

    ////11.3.6 单词转换的map
    ifstream in3("E:\\MyThing\\MyThings\\code\\cpp\\cpp_primer_practice\\MyC-Pratice\\ch11\\words.txt");
    ofstream out2("E:\\MyThing\\MyThings\\code\\cpp\\cpp_primer_practice\\MyC-Pratice\\ch11\\words_translate.txt", ofstream::app);
    translate(get_rule_map("E:\\MyThing\\MyThings\\code\\cpp\\cpp_primer_practice\\MyC-Pratice\\ch11\\rule.txt"),
              in3,
              out2);

    /////*11.4 无序容器*/
    //无序容器的使用与有序容器map、set基本相同；
    // 不同点：（1）无排序；（2）可重载==运算符
}
