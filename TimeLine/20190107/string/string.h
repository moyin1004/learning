/// @file    string.h
/// @data    2019-01-07 23:28:27
 
#ifndef __STRING_H__
#define __STRING_H__
    
class String {
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();

	void print() const;

private:
	char *_pstr;
};

#endif
