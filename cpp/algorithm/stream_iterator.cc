#include <iostream>
#include <iterator>
#include <set>
#include <fstream>

using namespace std;

int main() {
    string from, to;
    cin >> from >> to;
    ifstream is(from);
    ofstream os(to);
    set<string> b{istream_iterator<string>{is}, istream_iterator<string>{}};
    ranges::copy(b, ostream_iterator<string> {os, "\n"});

    cout << (!is.eof() || !os.fail()) << endl;
    return 0;
}