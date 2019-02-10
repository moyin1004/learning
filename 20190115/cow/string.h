/// @file    string.h
/// @data    2019-01-07 23:28:27

#ifndef __STRING_H__
#define __STRING_H__

#include <istream>
#include <ostream>

//class String;
//class Strcow { //优化
//public:
//    char *_pc = nullptr;
//    String *_str;
//    int pc_change = -1;
//
//    Strcow &operator=(const char c);
//    friend std::ostream &operator<<(std::ostream &os, const Strcow &c);
//};

class String {
public:
    //friend class Strcow;
    String();
    ~String();
    String(const char *);
    String(const String &);
    String &operator=(const String &);
    String &operator=(const char *);

    const char &operator[](std::size_t index) const;

    std::size_t size() const;
    const char* c_str() const;

    void release();
    void print() const;
    int refcount() const;

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    class CharProxy {
    public:
        CharProxy(String &, size_t);
        char &operator=(const char &c);
        operator char(); //转换CharProxy对象为char型 用于输出
    private:
        String &_self;
        size_t _idx;
    };
    char *_pstr;
    inline void initRefcount();
    inline void increaseRefcount();
    inline void decreaseRefcount();
public:
    CharProxy operator[](std::size_t index);
};

#endif
