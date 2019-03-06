/// @file    Noncopyable.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 17:34:40
 
#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__
    
namespace wd
{

class Noncopyable {
protected:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

} //end of namespace wd

#endif
