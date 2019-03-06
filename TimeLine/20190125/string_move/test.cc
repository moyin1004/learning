// @file    main.cc
/// @data    2019-01-08 11:11:14
 
#include "string.h"

#include <iostream>
 
using std::cout;
using std::endl;
using std::cin;
 
void test1() {
    String s1;
    String s2 = "hello";
    String s3 = s2 + "world";
    String s4 = "my" + s3;
    s1 += s3;
    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl
         << "s3 = " << s3 << endl
         << "s4 = " << s4 << endl;

    s1 = "";
    s2 = s1;
    s3 = s2;
    cout << "置空 s1 s2 s3: " << endl;
    cout << "s1 =" << s1 << ";" << endl
         << "s2 =" << s2 << ";" << endl
         << "s3 =" << s3 << ";" << endl;
    cout << "cin>>s1>>s2: " << endl;
    cin >> s1 >> s2;
    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl;
}

void test2() {
    String s1 = "hello";
    String s2 = "world";
    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl;
    s1 += s2;
    cout << "after s1 + s2:" << endl;
    cout << "s1 = " << s1 << " , s1.size = " << s1.size() << endl
         << "s2 = " << s2 << endl
         << "s1[5] = " << s1[5] << endl;

    cout << "条件语句：" << endl;
    cout << "s1 == s2 : " << (s1 == s2) << endl;
    cout << "s1 != s2 : " << (s1 != s2) << endl;
    cout << "s1 > s2 : " << (s1 > s2) << endl;
    cout << "s1 < s2 : " << (s1 < s2) << endl;
    cout << "s1 >= s2 : " << (s1 >= s2) << endl;
    cout << "s1 <= s2 : " << (s1 <= s2) << endl;
}

void test3() {
    String s1("hello");
    String s2(std::move(s1));
    String s3 = "world";
    cout << "s1 = " << s1 << endl; //s1无值
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << endl;
    s2 = std::move(s3);
    cout << "s1 = " << s1 << endl; //s1无值
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl; //s3无值

}

int main() {
    //test1();
    //test2();
    test3();
    return 0;
}
