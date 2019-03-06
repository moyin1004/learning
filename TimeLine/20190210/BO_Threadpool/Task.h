/// @file    Task.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 20:00:40
 
#ifndef __TASK_H__
#define __TASK_H__
    
namespace wd {

class Task {
public:
    virtual
    void process() = 0;

    virtual
    ~Task() {}
};

} //end of namespace wd

#endif
