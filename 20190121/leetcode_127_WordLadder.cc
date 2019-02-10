/// @file    leetcode_127_WordLadder.cc
/// @data    2019-01-23 09:29:21

/*
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;

        unordered_set<string> dict (wordList.begin(), wordList.end());
        if(!dict.count(endWord)) return 0;

        unordered_map<string, int> m;
        m[beginWord] = 1;
        queue<string> q;
        q.push(beginWord);

        while(!q.empty())  //广度优先搜索
        {
            string word = q.front();
            q.pop();
            //扫描所有与newword差一个字母的单词入队
            for(int i = 0; i < word.size(); i++) 
            {
                string newWord = word;
                char c = word[i];
                for(char ch = 'a'; ch <= 'z'; ch++)
                {
                    if(c == ch) continue;

                    newWord[i] = ch;
                    if(!dict.count(newWord)) continue;

                    if(newWord == endWord)
                        return m[word] + 1;
                    if(!m.count(newWord)){
                        m[newWord] = m[word] + 1; //记录从beginword到此单词的最短路径长度
                        q.push(newWord);
                    }
                }
            }
        } //end of while

        return 0;
    }
};
*/
