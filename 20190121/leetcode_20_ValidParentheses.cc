/// @file    leetcode_20_ValidParentheses.cc
/// @data    2019-01-22 12:47:19

/*
class Solution {
    public:
        bool isValid(string s) {
            for (auto &elem : s) {
                if (elem == '{' || elem == '(' || elem == '[') {
                    bracket.push(elem);
                }
                else if (!bracket.empty()) {
                    if (bracket.top() == '{' && elem != '}') return false;
                    else if (bracket.top() == '[' && elem != ']') return false;
                    else if (bracket.top() == '(' && elem != ')') return false;
                    bracket.pop();
                }
                else return false;  //防止一个单独的左括号
            }
            if (!bracket.empty()) return false;
            return true;
        }
    private:
        std::stack<char> bracket;
};
*/
