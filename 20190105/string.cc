#include <cstring>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	char str1[] = "hello";
	char str2[] = "world";

	string s1 = str1;
	cout << "s1 = " << s1 << endl;
	string s2 = s1 + str2;
	string s3 = s2 + "wangdao";
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;

	size_t len2 = s1.size();
	size_t len3 = s2.length();

	for(size_t i = 0; i < len3; i++) {
		cout << s3[i] << ' ';
	}
    cout << endl;
	int pos = s3.find('w');
	cout << pos << endl;
	string s4 = s3.substr(pos);
	cout << "s4 = " << s4 << endl;
	int pos2 = s3.find("wa");
	cout << s3.substr(pos2) << endl;

	const char* p = s3.c_str();  //返回值为常量，要有const
	for(size_t i = 0; i < strlen(p); i++) {
		cout << p[i];
	}
	cout << endl;


	return 0;
}
