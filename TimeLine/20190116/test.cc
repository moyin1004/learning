/// @file    test.cc
/// @data    2019-01-17 17:31:28
 
#include "tinyxml2.h"
#include "RssReader.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
    RssReader rss(1000);
    rss.parseRss("rss/36kr.xml");
    rss.parseRss("rss/coolshell.xml");
    rss.parseRss("rss/douban.book.review.xml");
    rss.parseRss("rss/feed.xbeta.info.xml");
    rss.parseRss("rss/geekfan.xml");
    rss.parseRss("rss/geekpark.xml");
    rss.parseRss("rss/ifanr.xml");
    rss.parseRss("rss/iteye_news.xml");
    rss.parseRss("rss/jobbole.xml");
    rss.parseRss("rss/leiphone.xml");
    rss.parseRss("rss/phonekr.xml");
    rss.parseRss("rss/portablesoft.xml");
    rss.parseRss("rss/songshuhui.xml");
    rss.parseRss("rss/xbeta.info.xml");
    rss.parseRss("rss/xubeng.xml");
    rss.dump("pagelib,dat");
    return 0;
}
