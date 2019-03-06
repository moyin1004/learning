/// @file    RssReader.h
/// @data    2019-01-17 16:25:05
 
#ifndef __RSSREADER_H__
#define __RSSREADER_H__
    
#include <string>
#include <vector>
using std::string;
using std::vector;

struct RssItem {
    string title = "null";
    string link = "null";
    string description = "null";
    string content = "null";
};

class RssReader {
public:
    RssReader(size_t);
    void parseRss(const char *filename);//解析
    void dump(const string &filename);//输出
private:
    vector<RssItem> _rss;
};

#endif
