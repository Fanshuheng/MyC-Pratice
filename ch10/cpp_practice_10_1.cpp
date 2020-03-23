#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
using namespace std;

bool check_size(const string &s, string::size_type sz){
    return s.size() >= sz;
}

ostream& print(ostream& os, const string& s, char c){
    return os << s << c;
}

bool isShorter(const string& s1, const string& s2){
    return s1.size() < s2.size();
}

void elimDups(vector<string>& words){
    //按字典排序
    sort(words.begin(), words.end());
    //重排容器，分为重复部分和不重复部分，重复部分在不重复部分之后，unique返回指向不重复部分的第一个元素
//    auto end_unique = unique(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    //删除重复部分
    words.erase(end_unique, words.end());
}

void biggies(vector<string>& words, string::size_type sz){
    elimDups(words);//去除重复元素

    //stable_sort：lambda的最简用法
    stable_sort(words.begin(), words.end(), [](const string& a, const string& b){//以单词长度排序，保留同长度单词顺序
        return a.size() < b.size();
    });

    //find_if:这里主要说明lambda捕获参数的方法(或bind的使用)
//    auto wc = find_if(words.begin(), words.end(), [sz](const string& a){//找出满足条件的第一个单词
//        return a.size() > sz;
//    });
    auto wc = find_if(words.begin(), words.end(), bind(check_size, placeholders::_1, sz));

    auto count = words.end() - wc;
    cout << count << " " << "word of length" << sz << "or longer" << endl;

    //for_each:lambda可以直接使用所在函数外的名字(这里是cout)
    for_each(wc, words.end(), [](const string &s){cout << s << " ";});//打印每个单词
    cout << endl;

}

int main(){
    ////10.1概述
    //find：接受顺序容器的迭代器
    vector<int> vector1{1,2,3,4,5,6,7,8,9,0};
    auto val1 = 3;
    auto result1 = find(vector1.begin(), vector1.end(), val1);
    cout << result1 - vector1.begin() << endl;

    //find:接受数组指针
    char s[] = {'1', '2', '3', '4', '5'};
    cout << *find(s, s + sizeof(s) / sizeof(char), '1') << endl;

    //10.1 cout:返回给定元素出现次数
    vector<int> vector2{1,2,2,2,5,6,7,8,9,0};
    auto val2 = 2;
    auto result2 = count(vector2.begin(), vector2.end(), val2);
    cout << result2 << endl;

    ////10.2读写、对比、重排算法
    //accumulate(代表只读类算法): 将元素累加起来（元素要支持+操作）
    vector<string> vector3{"123", "456", "7890"};
    auto sum = accumulate(vector3.begin(), vector3.end(), string(""));
    cout << sum << endl;

    //equal(代表对比类算法): 两个序列是否相等（前提：长度相同）
    cout << equal(vector1.begin(), vector1.end(), vector2.begin()) << endl;

    //10.3
    vector<int> vector4{1,2,3,4,5,6,7,8,9,0};
    cout << accumulate(vector4.begin(), vector4.end(), 0) << endl;

    //10.4 小数点后的数会被截断，第三个参数的类型决定了运算及返回的类型
    vector<double> vector5{1.1,2,3,4,5,6,7,8,9,0};
    cout << accumulate(vector5.begin(), vector5.end(), 0) << endl;

    //fill(代表写类算法):
    vector<int> vector6{1,1,1,1,1,1,1,1,1,1};
    fill(vector6.begin(), vector6.end(), 10);
    for(const auto& e:vector6)
        cout << e <<" ";
    cout << endl;
    //fill_n(代表 写_n 算法,写_n 算法是不被检查的,当参数大于容器长度时,函数行为未定义):
    fill_n(vector6.begin(), 9, 5);//写9个5
    for(const auto& e:vector6)
        cout << e <<" ";
    cout << endl;

    //back_inserter（<iterator>）:*back_inserter(...)会调用元素的push_back
    vector<int> vector7;
    auto iter = back_inserter(vector7);
    fill_n(iter, 10, 0);//插10个0
    for(const auto& e:vector7)
        cout << e <<" ";
    cout << endl;

    //10.13
    vector<string> words_vector{"asdqwsd", "1","12335y4rthdf", "123","pacoigqd","123rwfsdb"};
    auto i = partition(words_vector.begin(), words_vector.end(), [](const string& s1){return s1.size() > 5;});
    cout << i - words_vector.begin() << endl;

    ////10.3 定制操作
    //elimDups(包括sort(调用<操作符)和unique):
    vector<string> words{"z", "b", "r", "a", "z"};
    elimDups(words);//按字典序排序，去除重复元素
    stable_sort(words.begin(), words.end(),
            [](const string& a, const string& b){
                return a.size() < b.size();
    });//按长度排序，保持相同长度的顺序
    for(const auto& e:words)
        cout << e <<" ";
    cout << endl;

    //10.14
    int v1 = 0, v2 = 1;
    auto lambda_sum1 = [](const int& a, const int & b){return a + b;};
    cout << lambda_sum1(v1, v2) << endl;

    //10.15
    int v3 = 1;
    auto lambda_sum2 = [v3](const int& a){return v3 + a;};
    cout << lambda_sum2(100) << endl;

    ////10.14 lambda细讲
    //lambda普通捕获
    size_t v4 = 42;
    auto f = [v4](){return v4;};
    cout << f() << endl;

    //lambda引用捕获
    //不恰当的用法(捕获引用或指针);恰当用法（捕获流）
    size_t v5 = 1;
    auto f1 = [&v5](){v5+=1;return v5;};//简易不要捕获指针和引用
    cout << v5 << " " << f1()  << " " << v5 << endl;//输出2 2 1（从右往左访问v5）

    //lambda隐式捕获（隐式捕获就是不用在[]里指出捕获参数；可以在[]里指明捕获类型=或&，指定隐式捕获的类型后，显示捕获参数列表的方式一定与隐式的不同。）
    int value1 = 1, value2 = 2;
    auto f3 = [=](){return value1+value2;};
    cout << f3() << endl;

    //如果lambda要改变捕获变量的值可加mutable
    int value3 = 0;
    auto f4 = [value3]()mutable{return ++value3;};
    cout << f4() << endl;//输出1

    //指定lambda返回类型：置尾返回类型
    double value4 = 1.1;
    auto f5 = [&value3]()->int
            {return ++value3;};
    cout << f5() << endl;//输出1

    //transform
    vector<int> vector8{-1,1,-2,2};
    transform(vector8.begin(), vector8.end(), vector8.begin(), [](int i){
        if(i < 0)return -i; else return i;
    });
    for_each(vector8.begin(),vector8.end(),[](int i){cout << i <<" ";});
    cout << endl;

    //10.20
    // count_if:传入一个谓词，数有多少元素符合要求
    cout << count_if(vector8.begin(), vector8.end(), [](int i){return i > 1;}) << endl;

    ////10.3 参数绑定：引入bind（让双参数的函数变成单函数，以适应泛型算法的要求;头文件functional）
    //check_size的例子（check_size的定义在上面）
    auto check6 = bind(check_size, placeholders::_1, 6);
    string check6string = "1234567890";
    cout << check6(check6string) << endl;

    //bind重排参数：
    auto f6 = [](int a, int b, int c){cout << a << " "<< b << " " << c << endl;};
    int a = 1, b = 2, c = 3;
    auto g = bind(f6, placeholders::_2, a, placeholders::_1);//g(_1, _2)->f6(_2, a, _1)
    g(c,b);//2 1 3

    //这一块不知道为什么报错，跳过
//    //bind绑定引用参数：以os为例（上面重排参数的例子里，bind是拷贝参数的；os不能被拷贝，只能引用）
//    string string1{"123456789"};
//    for_each(string1.begin(), string1.end(), bind(print, ref(cout), placeholders::_1, ' '));

    ////10.4 插入迭代器
    // back_inserter:调用元素的push_back;
    // front_inserter:调用push_front
    // inserter:给定迭代器it，插到it代表的位置之前，然后重新指向it
    list<int> list1;
    auto it1 = back_inserter(list1);
    auto it2 = front_inserter(list1);
    *it1 = 9;
    *it2 = 8;
    *it1 = 10;
    *it2 = 7;
    auto it3 = inserter(list1, list1.begin());
    *it3 = 6;//如果it是普通迭代器，则相当于：
    //it = c.insert(it, 6);
    //it++;
    for_each(list1.begin(), list1.end(), [](int i){cout << i << " ";});
    cout << endl;

    //unique_copy:将不重复的元素拷贝到第三个容器
    list<int> vector9{1,1,2,2,3,3,4,4,5,6,6,5};
    list<int> vector10,vector11,vector12;
    //unique_copy(vector9.begin(), vector9.end(), vector10.begin()); //段错误：Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
    unique_copy(vector9.begin(), vector9.end(), back_inserter(vector10));
    unique_copy(vector9.begin(), vector9.end(), front_inserter(vector11));
    unique_copy(vector9.begin(), vector9.end(), inserter(vector12, vector12.begin()));
    for_each(vector10.begin(), vector10.end(), [](int i){cout << i << " ";});//1 2 3 4 5 6 5
    cout << endl;
    for_each(vector11.begin(), vector11.end(), [](int i){cout << i << " ";});//5 6 5 4 3 2 1
    cout << endl;
    for_each(vector12.begin(), vector12.end(), [](int i){cout << i << " ";});//1 2 3 4 5 6 5
    cout << endl;

    //流迭代器
//    //istream_iterator
//    istream_iterator<int> int_it(cin);//在键盘输入
//    istream_iterator<int> int_eof;//默认初始化的流迭代器可以当做尾后迭代器来用
//    //for_each(int_it, int_eof, [](int i){cout << i << " ";});//打印出所输入的东西
//    cout << endl;
//    vector<int> vector13(int_it, int_eof);
//    for_each(vector13.begin(), vector13.end(), [](int i){cout << i << " ";});

    //ostream_iterator
    ostream_iterator<int> out_it(cout, "/");//每输出一个元素都用/隔开
    vector<int> vector14{6,3,9,1,90,4,2,5};
    for(auto e:vector14){
        *out_it++ = e;
    }
    cout << endl;
    //上面的for可以用copy代替
    copy(vector14.begin(), vector14.end(), out_it);
    cout << endl;

    //10.29
    ifstream in("/home/ch/code/cpp_primer_prartice/ch10/data");
    istream_iterator<string> in_iter(in), eof_iter;
    ostream_iterator<string> out_iter(cout, "/");
    vector<string> vector15(in_iter, eof_iter);
    for_each(vector15.begin(), vector15.end(), [&](const string& a){*out_iter++ = a;});

//    //10.30
//    istream_iterator<int> in_iter1(cin), eof;
//    vector<int> vector16(in_iter1, eof);
//    sort(vector16.begin(), vector16.end());
//    for_each(vector16.begin(), vector16.end(), [](int i){cout << i;});
//    cout << endl;

    //10.33
    ifstream in1("/home/ch/code/cpp_primer_prartice/ch10/shu");
    istream_iterator<int> in_iter2(in1), in_eof1;

    ofstream out1("/home/ch/code/cpp_primer_prartice/ch10/jishu", ofstream::app);
    ofstream out2("/home/ch/code/cpp_primer_prartice/ch10/oushu", ofstream::app);
    ostream_iterator<int> out_iter1(out1, " "), out_iter2(out2, " ");
    vector<int> vector17(in_iter2, in_eof1);
    for_each(vector17.begin(), vector17.end(), [&](int i){
        if(i%2) *out_iter1++ = i;
        else *out_iter2++ = i;
    });
    cout << endl;
    out1.close();
    out2.close();

    ////10.4 反向迭代器
    //逆序打印vector
    vector<int> vector18{1,2,3,4,5,6,7,8,9,0};
    for_each(vector18.rbegin(), vector18.rend(), [](int i){cout << i << " ";});
    cout << endl;

    //由大到小顺序排序
    sort(vector18.rbegin(), vector18.rend());
    for_each(vector18.begin(), vector18.end(), [](int i){cout << i << " ";});
    cout << endl;

    //找最后一个单词
    string string1 = "first,second,last";
    auto rcomma = find(string1.crbegin(), string1.crend(), ',');//这里rcomma是一个逆向迭代器
    cout << string(rcomma.base(), string1.cend())<<endl;//base成员函数可以将逆向迭代器变回正向迭代器
}