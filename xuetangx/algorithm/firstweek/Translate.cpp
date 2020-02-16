#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const string TRAN[3][3] = {{"Today is %s.", "I want to %s.", "%d %s, please."},
                        {"Var day=%s;", "Var plan=\"%s\";", "Var item=\"%s\"; Var num=%d;"},
                        {"Oh, my god. that's incredible. You know what? I just found that today is %s!",
                         "My god! What should I do today? Let me see. Well, I have an excellent idea! Let us go to %s.",
                         "I want one %s%s."}};
const string addC = ", and one more";
const string WEEK[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

string MatchDigit(string &data, int start) {
    int size = data.size();
    string digit;
    for (int i = start; i < size; ++i) {
        if (isdigit(data[i])) {
            digit += data[i];
        }
    }
    return digit;
}

const string *Find(char person) {
    int num = 0;
    switch(person) {
    case 'A': {
        num = 0;
        break;
    }
    case 'B': {
        num = 1;
        break;
    }
    case 'C': {
        num = 2;
    }
    }
    return TRAN[num];
}

int MatchString(string &data, char from, string match[]) {
    match[0].clear();
    match[1].clear();
    const string *tran = Find(from);
    int size = data.size();
    //cout << size << endl;
    int i = 0;
    for (i = 0; i < 3; ++i) {
        int j = 0, k = 0;
        //cout << "tran= " << tran[i] << endl;
        while (j < size) {
            if (k < size && tran[i][k+1] == 's' && tran[i][k] == '%') {
                //cout << data[j] << endl;
                if ((k+2 == size && j+1 == size) || data[j] == tran[i][k + 2]) {
                    k += 2;
                    continue;
                }
                match[0] += data[j];
                ++j;
            }
            else if (k < size && tran[i][k+1] == 'd' && tran[i][k] == '%') {
                match[1] = MatchDigit(data, j);
                k += 2;
                j += match[1].size();
            }
            else if (data[j] != tran[i][k]){
                break;
            }
            else {
                ++j;
                ++k;
            }
            //cout << j << " " << k << " " << size << endl;
        }
        //cout << j << endl;
        if (j == size) {
            break;
        }
    }

    //cout << match[0] << endl << i << from << endl;
    if (i == 2 && from == 'C') { // about order, Special Treatment
        int num = 1, pos = 0;
        pos = match[0].find(addC, pos);
        int start = pos;
        while (pos != string::npos) {
            ++num;
            pos += addC.size();
            pos = match[0].find(addC, pos);
        }
        if (start != string::npos) {
            match[0] = match[0].substr(0, start);
        } else {
            match[0].pop_back();
        }
        match[1] = to_string(num);
    }
    if (i == 0 && from == 'C') {
        match[0] = match[0].substr(2);
    }
    if (i == 0 && from == 'B') {
        match[0] = WEEK[(int)(match[0][0] - '0') - 1];
    }
    return i;
}

void Print(string data[], char to, int pos) {
    const string *tran = Find(to);
    const char *format = tran[pos].c_str();
    if (pos == 2) {
        int num = strtoul(data[1].c_str(), NULL, 10);
        switch(to) {
        case 'A': {
            printf(format, num, data[0].c_str());
            break;
        }
        case 'B': {
            printf(format, data[0].c_str(), num);
            break;
        }
        case 'C': {
            string add;
            for (int i = 0; i < num - 1; ++i) {
                add += addC;
            }
            printf(format, data[0].c_str(), add.c_str());
        }
        }
        cout << endl;
        return ;
    }
    if (pos == 0 && to == 'C') {
        string pre;
        pre.append(2, data[0][0]);
        data[0] = pre + data[0];
    }
    else if (pos == 0 && to == 'B') {
        int i = 0;
        for (i = 0; i < 7; ++i) {
            if (data[0] == WEEK[i]) {
                break;
            }
        }
        data[0] = to_string(i + 1);
    }
    printf(format, data[0].c_str());
    cout << endl;
}

int main() {
    int T = 0;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        char from, to;
        string data;
        cin >> from >> to;
        getchar();
        getline(cin, data);
        string match[2];
        if (from == to) {
            cout << data << endl;
            continue;
        }
        int pos = MatchString(data, from, match);
        //cout << match[0] << "|||" << match[1] << endl << endl << endl;
        Print(match, to, pos);
    }
    return 0;
}
