/// @file    RssReader.cc
/// @data    2019-01-17 16:30:06

#include "tinyxml2.h"
#include "RssReader.h"
#include <iostream>
#include <regex>
#include <fstream>
using std::cout;
using std::endl;
using std::regex;
using std::ofstream;

string filtration(const string &str) {
    // <(\\S*?)[^>]*>.*?|<.*?/>:   //匹配html标记
    // ^\\s*|\\s*$   //匹配行首行尾的空白字符
    // &nbsp|;       //匹配 &nbsp 和 ;
    string s1 = "<(\\S*?)[^>]*>.*?|<.*?/>:|^\\s*|\\s*$|&nbsp|;";
    string pstr = str;
    regex r(s1);
    pstr = regex_replace(pstr, r, string(""));
    return pstr;
}

RssReader::RssReader(size_t capacity) {
    _rss.reserve(capacity);
}

void RssReader::parseRss(const char *filename) {
    using namespace tinyxml2;
    XMLDocument xml;
    xml.LoadFile(filename);
    if(xml.Error() != 0) {
        cout << "load file error" <<endl;
    }

    XMLElement *root = xml.RootElement();
    XMLElement *channel = root->FirstChildElement("channel");
    XMLElement *item = channel->FirstChildElement("item");
    cout << "rssfile" << endl;

    RssItem prss;
    string t;
    if (item == nullptr) cout << "null" << endl;
    while (item) {
        XMLElement *item_child = item->FirstChildElement();
        while(item_child) {
            if (strcmp(item_child->Name(), "title") == 0)
                prss.title = item_child->GetText();
            else if (strcmp(item_child->Name(), "link") == 0)
                prss.link = item_child->GetText();
            else if (strcmp(item_child->Name(), "description") == 0)
                prss.description = filtration(item_child->GetText());
            else if (strcmp(item_child->Name(), "content") == 0)
                prss.content  = item_child->GetText();
            item_child = item_child->NextSiblingElement();
        }
        item = item->NextSiblingElement();
        _rss.push_back(prss);
        prss.title = prss.link = prss.description = prss.content = "null";
    }
}

void RssReader::dump(const string &filename) {
    ofstream ofs(filename);
    int id = 0;
    for (vector<RssItem>::iterator it = _rss.begin(); it != _rss.end(); it++) {
        ofs << "<doc>" << endl
            << "  <docid>" << ++id << "<docid>" << endl
            << "  <title>" << it->title << "<title>" << endl
            << "  <link>" << it->link << "<link>" << endl
            << "  <description>" << it->description << endl << "  <description>" << endl
            << "  <content>" << it->content << "<content>" << endl
            << "<doc>" << endl << endl;
    }
}
