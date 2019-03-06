#include <iostream>

using std::cout;
using std::endl;

void test1() {
	double num1 = 1.111;
	int num2 = static_cast<int>(num1);
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	int *p = static_cast<int*>(malloc(sizeof(int)));
	*p = 100;
	cout << "*P = " << *p << endl;
}

void test2() {
	int* p = new int[10](); //自动初始化0
	for(size_t i = 0; i < 10; i++) {
		cout << p[i] << endl;
	}
	delete []p;
}

int main()
{
	test1();
	test2();
	return 0;
}

