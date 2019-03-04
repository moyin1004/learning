/// @file    1.二维数组中的查找.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-01 21:32:49
 
#include <iostream>
#include <vector>
using namespace std;
 
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() <= 0) return false;

        for (size_t i = 0; i < array.size();) {
            for (int j = array[0].size() - 1; j >= 0;) {
                if (array[i][j] == target) return true;
                else if (array[i][j] > target) {
                    --j;
                }
                else if (array[i][j] < target) {
                    ++i;
                }
            }
        }
        return false;
    }
};

int main() {
    int target;
    vector<vector<int> > array;
    cin >> target;
    vector<int> temp = {1, 2, 8, 9};
    array.push_back(temp);
    vector<int> temp1 = {2, 4, 9, 12};
    array.push_back(temp1);
    vector<int> temp2 = {4, 7, 10, 13};
    array.push_back(temp2);
    vector<int> temp3 = {6, 8, 11, 15};
    array.push_back(temp3);
    Solution s;
    if (s.Find(target, array)) cout << "true" << endl;
    else cout << "false" << endl;
}
