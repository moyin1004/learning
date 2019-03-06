#include <iostream>
using std::cout;
using std::endl;

int number = 40;

namespace ds
{
	void show();
}

namespace wd
{
	int number = 10;
	void display(int number)
	{
		cout << "wd::display" << endl;
		ds::show();
		cout << "number = " << number << endl;
		cout << "全局number = " << ::number << endl;
		cout << "wd::number = " << wd::number << endl;
	}

	namespace moyin
	{
		void display()
		{
			cout << "wd::moyin::display()" << endl;
		}
	}
}//end of namespace wd

namespace ds
{
	int number = 20;
	void show()
	{
		cout << "ds::show()" << endl;
		wd::moyin::display();
		cout << "ds::number = " << number << endl;
	}
}//end of namespace ds

void point_test()
{
	int a = 1;
	const int b = 2;
	//const int* c = &a;//指针常量认为所指向的内容为常量,所以*c不能改，a自己是变量，不影响a的修改
	const int* c = &b;
	int* const d = &a;//左边为常量指针，指针所指向的内容为变量，不能指向常量b
	const int* const e = &a;
	cout << "not change:" << endl;
	cout << "a = " << a << endl;
	cout << "常量b = " << b << endl;
	cout << "指针常量*c = b = " << *c << endl;
	cout << "常量指针*d = a " << *d <<endl;
	cout << "双常量*e = a = " << *e << endl;
	*d = 3;
	c = &b;
	cout << endl;
	cout << "*d = 3,c = &b change:" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "*c = b = " << *c << endl;
	cout << "*d = a =  " << *d << endl;
	cout << "*e = a = " << *e << endl;
	cout << "双常量e自认为所指向的内容为常量,所以*e不能改，但是a自己是变量，不影响a的修改" << endl;
}

int main()
{
	int number = 30;
	wd::display(number);
	cout << endl;
	point_test();
	return 0;
}
