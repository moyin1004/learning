#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

#ifdef __cplusplus
extern "C" {
#endif
	int add(int a, int b){
		return a + b;
	}
#ifdef __cplusplus
}
#endif

inline double add(double a, double b){
	return a + b;
}

inline int add(int x, int y, int z, int t = 6){
	return x + y + z + t;
}

int main()
{
	int a = add(3, 4);
	double b = add(1.1, 1.1);
	int c = add(3, 4, 5);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	return 0;
}

