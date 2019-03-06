///@file    memory.cc
///@data    2019-01-07 19:40:46
 
#include <cstdio>
#include <iostream> 
 
using std::cout; 
using std::endl; 

int a; //全局/静态区
char* p1;

int main() { 
	int b = 10;//栈区
	const char * s = "123456";//文字常量区
	p1 = new char[5]();
	char* p2 = new char[10](); //堆区
	static int c = 0;

	cout << "栈区&b = " << &b << endl;
	cout << "栈区&p2 = " << &p2 << endl;
	printf("堆区p1 = %p\n", p1);
	printf("堆区p2 = %p\n", p2);
	cout << "全局区&a = " << &a << endl;
	cout << "全局区&p1 = " << &p1 << endl;
	cout << "静态&c = " << &c << endl;
	printf("文字常量区s = %p\n", s);

	return 0;
}
