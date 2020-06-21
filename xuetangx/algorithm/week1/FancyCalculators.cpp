#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const string calB[] = {")", "!", "@", "#", "$", "%", "^", "&", "*", "("};
const string calC[] = {"p", "q", "w", "e", "r", "t", "y", "u", "i", "o"};
const string calD[] = {";", "a", "s", "d", "f", "g", "h", "j", "k", "l"};
const string calE[] = {"/", "z", "x", "c", "v", "b", "n", "m", ",", "."};
const string express[] = {"...", "..|", "|..", "|.|", ".-."};
const int calF[10][5] = {{4, 3, 0, 3, 4},
                         {0, 1, 0, 1, 0},
                         {4, 1, 4, 2, 4},
                         {4, 1, 4, 1, 4},
                         {0, 3, 4, 1, 0},
                         {4, 2, 4, 1, 4},
                         {4, 2, 4, 3, 4},
                         {4, 1, 0, 1, 0},
                         {4, 3, 4, 3, 4},
                         {4, 3, 4, 1, 4}};
bool F = false; // if have F

string TranNum(int num, char dst) {
    switch (dst) {
    case 'a': {
        string res;
        res += (char)(num + '0');
        return res;
        break;
    }
    case 'b': return calB[num]; break;
    case 'c': return calC[num]; break;
    case 'd': return calD[num]; break;
    case 'e': return calE[num]; break;
    case 'f': {
        F = true;
        return express[calF[num][4]];
    }
    }
}

void PrintF(string &data) {
    int count = data.size();
    for (int k = 0; k < 4; ++k) {  // cout 4 lines of F
        for (int i = 0; i < count; i += 2) {
            if (data[i+1] == 'f') {
                int num = data[i] - '0';
                cout << express[calF[num][k]];
                continue;
            }
            cout << ".";
        }
        cout << endl;
    }
}

int main() {
    int T = 0;
    cin >> T;
    string res;
    for (int i = 0; i < T; ++i) {
        res.clear();
        string data;
        int num = 0;
        cin >> data;
        int count = data.size();
        for (int j = 0; j < count; j += 2) {
            int num = data[j] - '0';
            res += TranNum(num, data[j+1]);
        }
        if (F) {
            PrintF(data);
        }
        cout << res << endl;
    }
    return 0;
}
