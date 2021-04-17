/// @file    RBTree.h
/// @author  moyin(moyin1004@163.com)
/// @data    2021-03-19 16:08:26

#ifndef __RBTREE__
#define __RBTREE__

// 参考 https://mp.weixin.qq.com/s/8-1UIEcTE0OYYQFLMj5Mxg

#include <utility>
#include <stack>
#include <iostream>
using std::pair;
using std::stack;
using std::cout;
using std::make_pair;

enum Color {
    RED,
    BLACK
};

template <typename Key, typename Value>
class RBTree {
    typedef pair<Key, Value> Data;
    struct RBNode {
        Data data;
        RBNode *left;
        RBNode *right;
        RBNode *parent;
        Color color;
        const Key &key = data.first;
        const Value &value = data.second;
    };

public:
    typedef pair<Key, Value>* iterator;

    RBTree();
    ~RBTree();
    void inOrder() const;

    Value &operator[](const Key &key);

    void insert(const Data &data);
    int erase(const Key &key);
    void clear();

    iterator find(const Key &key) const;
    iterator begin();
    iterator end();

    bool empty() const { return _len == 0; }
    size_t size() const { return _len; }

private:
    RBNode *findPos(const Key &key) const;
    RBNode *insert(RBNode *, const Data &data);
    // 创建结点，默认红色
    RBNode *creatNode(const Data &data, Color color = Color::RED);
    // 红黑树平衡
    void leftRotate(RBNode *);
    void rightRotate(RBNode *);
    void insertFixup(RBNode *);
    void deleteFixup(RBNode *, RBNode *);
    // 销毁
    void destroy(RBNode *);
    // 子树中最大值与最小值查找
    RBNode *treeMin(RBNode *) const;
    RBNode *treeMax(RBNode *) const;

    RBNode *_tree;
    std::size_t _len;
};

template <typename Key, typename Value>
void RBTree<Key, Value>::inOrder() const {
    stack<RBNode*> s;
    RBNode *p = _tree;
    while (p || !s.empty()) {
        if (p) {
            s.push(p);
            p = p->left;
        } else {
            cout << s.top()->key << "-" << s.top()->color << " ";
            p = s.top()->right;
            s.pop();
        }
    }
    cout << std::endl;
}

template <typename Key, typename Value>
RBTree<Key, Value>::RBTree()
: _tree(nullptr),
  _len(0)
{}

template <typename Key, typename Value>
RBTree<Key, Value>::~RBTree() {
    if (empty()) return ;
    destroy(_tree);
    _tree = nullptr;
    _len = 0;
}

template <typename Key, typename Value>
Value &RBTree<Key, Value>::operator[](const Key &key) {
    RBNode *pos = findPos(key);
    if (pos->key == key) return pos->data.second;
    
    RBNode *new_node = insert(pos, make_pair(key, Value()));
    return new_node->data.second;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::iterator
RBTree<Key, Value>::find(const Key &key) const {
    RBNode *pos = findPos(key);
    if (pos->key == key) return &pos->data;
    return iterator();
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::iterator
RBTree<Key, Value>::begin() {
    if (empty()) return iterator();
    RBNode *node = treeMin(_tree);
    return &node->data;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::iterator
RBTree<Key, Value>::end(){
    return iterator();
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clear() {
    if (empty()) return ;
    destroy(_tree);
    _tree = nullptr;
    _len = 0;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::insert(const Data &data) {
    if (!_tree) {
        _tree = creatNode(data, Color::BLACK);
        return ;
    }

    RBNode *tmp = findPos(data.first);
    RBNode *new_node = insert(tmp, data);
}

template <typename Key, typename Value>
int RBTree<Key, Value>::erase(const Key &key) {
    if (empty()) return 0;
    RBNode *z = findPos(key);
    if (z->key != key) return 0;
    if (z == _tree) {
        delete _tree;
        _tree = nullptr;
        return 1;
    }

    // y为结点z的直接后继
    RBNode *x = nullptr;
    RBNode *y = nullptr;  // y为要删除结点
    if (!z->left || !z->right) {
        y = z;
    } else {
        y = treeMin(z->left);
    }
    // 保留y的子结点
    x = y->left ? y->left : y->right;
    if (x) x->parent = y->parent;
    if (!y->parent) {
        _tree = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    if (y != z) {
        z->data.first = y->key;
        z->data.second = y->value;
    }
    if (y->color == Color::BLACK) {
        deleteFixup(x, y->parent);
    }

    delete y;
    return 1;
}

/**
 * 私有成员
 */
template <typename Key, typename Value>
typename RBTree<Key, Value>::RBNode*
RBTree<Key, Value>::insert(RBNode *tmp, const Data &data) {
    const Key &key = data.first;
    RBNode *new_node = nullptr;
    if (key < tmp->key) {
        new_node = creatNode(data);
        tmp->left = new_node;
        new_node->parent = tmp;
    } else if (key > tmp->key) {
        new_node = creatNode(data);
        tmp->right = new_node;
        new_node->parent = tmp;
    } else {
        tmp->data = data;
    }
    insertFixup(new_node);
    return new_node;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::RBNode*
RBTree<Key, Value>::findPos(const Key &key) const {
    RBNode *node = _tree;
    RBNode *tmp = _tree;
    while (node) {
        tmp = node;
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            tmp = node;
            break;
        }
    }
    return tmp;
}


template <typename Key, typename Value>
typename RBTree<Key, Value>::RBNode*
RBTree<Key, Value>::creatNode(const Data &data, Color color) {
    RBNode *new_node = new RBNode;
    new_node->data = data;
    new_node->left = new_node->right = new_node->parent = nullptr;
    new_node->color = color;
    ++_len;
    return new_node;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::leftRotate(RBNode *x) {
    if (!x) return ;
    RBNode *y = x->right;

    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (!x->parent) {
        _tree = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::rightRotate(RBNode *y) {
    if (!y) return ;
    RBNode *x = y->left;

    y->left = x->right;
    if (x->right) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (!y->parent) {
        _tree = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::insertFixup(RBNode *z) {
    if (!z) return ;
    auto fixupred = [&](RBNode *parent, RBNode *uncle) {
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        parent->parent->color = Color::RED;
    };

    while (z->parent && z->parent->color == Color::RED) {
        RBNode *grandp = z->parent->parent;
        if (grandp->left == z->parent) {
            RBNode *y = grandp->right;

            // 叔叔是红色的情况
            if (y && y->color == Color::RED) {
                fixupred(z->parent, y);
                z = grandp;
                continue;
            }
            // 叔叔是黑色的情况
            if (z == z->parent->right) {
                z = z->parent;
                leftRotate(z);
            }
            z->parent->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            rightRotate(z->parent->parent);
        } else {
            RBNode *y = grandp->left;

            // 叔叔是红色的情况
            if (y && y->color == Color::RED) {
                fixupred(z->parent, y);
                z = grandp;
                continue;
            }
            // 叔叔是黑色的情况
            if (z == z->parent->left) {
                z = z->parent;
                rightRotate(z);
            }
            z->parent->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            leftRotate(z->parent->parent);
        }
    }
    if (z && z == _tree) z->color = Color::BLACK;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::deleteFixup(RBNode *x, RBNode *parent) {
    while ((!x || x->color == Color::BLACK) && x != _tree) {
        if (x == parent->left) {
            RBNode *w= parent->right;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                parent->color = Color::RED;

                leftRotate(parent);
                w = parent->right;
            }
            // 兄弟的两个子节点都是黑色的
            if ((!w->left || w->left->color == Color::BLACK) &&
                (!w->right || w->right->color == Color::BLACK)) {
                w->color = Color::RED;
                x = parent;
            } else {
                // 兄弟的左孩子为红色
                if (!w->right || w->right->color == Color::BLACK) {
                    w->left->color = Color::BLACK;
                    w->color = Color::RED;
                    rightRotate(w);
                    w = parent->right;
                }

                w->color = parent->color;
                parent->color = Color::BLACK;
                w->right->color = Color::BLACK;
                leftRotate(parent);

                x = _tree;
            }
        } else {
            RBNode *w = parent->left;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                parent->color = Color::RED;
                rightRotate(parent);
                w = parent->left;
            }

            if ((!w->left || w->left->color == Color::BLACK) &&
                (!w->right || w->right->color == Color::BLACK)) {
                w->color = Color::RED;
                x = parent;
            } else {
                if (!w || w->left->color == Color::BLACK) {
                    w->right->color = Color::BLACK;
                    w->color = Color::RED;
                    leftRotate(w);
                    w = parent->left;
                }

                w->color = parent->color;
                parent->color = Color::BLACK;
                w->left->color = Color::BLACK;
                rightRotate(parent);

                x = _tree;
            }
        }
    } // end of while
    if (x) x->color = Color::BLACK;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::destroy(RBNode *node) {
    if (!node) return ;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::RBNode*
RBTree<Key, Value>::treeMin(RBNode *tree) const {
    while (tree && tree->left) {
        tree = tree->left;
    }
    return tree;
}

#endif