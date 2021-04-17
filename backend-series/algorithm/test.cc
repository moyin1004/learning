#include "RBTree.h"
#include <iostream>
#include <map>

using namespace std;

void rbtree_test() {
    RBTree<int, int> tree;
    tree.insert(make_pair<int, int>(10, 100));
    tree.insert(make_pair<int, int>(11, 10));
    tree.insert(make_pair<int, int>(15, 10));
    tree.insert(make_pair<int, int>(13, 10));
    tree.insert(make_pair<int, int>(5, 10));
    tree.insert(make_pair<int, int>(6, 10));
    tree.insert(make_pair<int, int>(1, 111));
    tree.inOrder();
    cout << "size=" << tree.size() << endl;

    RBTree<int, int>::iterator it = tree.begin();
    cout << it->first << " " << it->second << endl;
    it = tree.find(10);
    if (it != tree.end()) cout << it->second << endl;

    cout << tree[1] << endl;
    tree[1] = 1111;
    cout << tree[1] << endl;

    
    if (tree.empty()) cout << "empty" << endl;

    cout << "is erase: " << tree.erase(3) << endl;
    cout << "is erase: " << tree.erase(10) << endl;
    cout << "is erase: " << tree.erase(5) << endl;
    cout << "is erase: " << tree.erase(1) << endl;
    cout << "is erase: " << tree.erase(15) << endl;
    tree.inOrder();
    tree.clear();
}

int main() {
    rbtree_test();
    return 0;
}