#include "algorithm.h"
#include "stack.h"
#include <stack>

// static int tran_op(char op) {
//     if (op == '+' || op == '-') return 1;
//     if (op == '*' || op == '/') return 2;
//     return 0;
// }
// static int op_priority(char lhs, char rhs) {
//     return tran_op(lhs) - tran_op(rhs);
// }
// string nifix2postfix() {
//     string str = "(15/(7-(1+1))*3)-(2+(1+1))";
//     // cin >> str;
//     int size = str.size();
//     string postfix;
//     char c;

//     Stack S;
//     InitStack(S);
//     for (int i = 0; i < size; ++i) {
//         if (isdigit(str[i])) {
//             postfix = postfix + str[i];
//             continue;
//         }
//         if (!postfix.empty() && postfix[postfix.size()-1] != ' ') postfix += " ";
//         while (GetTop(S, c) && ((op_priority(str[i], c) <= 0 && str[i] != '(') || str[i] == ')')) {
//             if (c != ')' && c != '(') postfix = postfix + c + ' ';
//             Pop(S, c);
//             if (c == '(') break;
//         }
//         if (str[i] != ')') {
//             Push(S, str[i]);
//         }
//     }
//     while (Pop(S, c)) {
//         postfix = postfix + c + ' ';
//     }
//     DestoryStack(S);
//     return postfix;
// }

// string nifix2prefix() {
//     string str = "(15/(7-(1+1))*3)-(2+(1+1))";
//     // cin >> str;
//     int size = str.size();
//     string prefix;
//     char c;

//     Stack S;
//     InitStack(S);
//     for (int i = size-1; i >= 0; --i) {
//         if (isdigit(str[i])) {
//             prefix = prefix + str[i];
//             continue;
//         }
//         if (!prefix.empty() && prefix[prefix.size()-1] != ' ') prefix += " ";
//         while (GetTop(S, c) && ((op_priority(str[i], c) < 0 && str[i] != ')') || str[i] == '(')) {
//             if (c != ')' && c != '(') prefix = prefix + c + ' ';
//             Pop(S, c);
//             if (c == ')') break;
//         }
//         if (str[i] != '(') {
//             Push(S, str[i]);
//         }
//     }
//     while (Pop(S, c)) {
//         prefix = prefix + c + ' ';
//     }
//     DestoryStack(S);
//     reverse(prefix.begin(), prefix.end());
//     return prefix;
// }

// int cul(char op, int a, int b) {
//     if (op == '+') return a+b;
//     if (op == '-') return a-b;
//     if (op == '*') return a*b;
//     if (op == '/') return a/b;
//     assert(0);
//     return 0;
// }
// int postfix_cul(string postfix) {
//     int size = postfix.size();
//     char c;
//     int S[10];
//     int top = 0;
//     string data;
//     for (int i = 0; i < size; ++i) {
//         if (postfix[i] == ' ' && !data.empty()) {
//             S[top++] = atoi(data.c_str());
//             data.clear();
//         }
//         else if (isdigit(postfix[i])) {
//             data = data + postfix[i];
//         }
//         else if (postfix[i] == '+' || postfix[i] == '-' ||
//             postfix[i] == '*' || postfix[i] == '/') {
                
//             int num = cul(postfix[i], S[--top], S[--top]);
//             S[top++] = num;
//         }
//     }
//     return S[top-1];
// }

// // 括号匹配
// bool bracket_matching() {
//     string str;
//     bool ret = true;
//     char r = 0;
//     cin >> str;
//     int size = str.size();
//     Stack S;
//     InitStack(S);
//     for (int i = 0; i < size; ++i) {
//         char c = str[i];
//         if (c == '{' || c == '[' || c == '(') {
//             Push(S, c);
//         }
//         else if (!Pop(S, r) ||
//                 (c == '}' && r != '{') ||
//                 (c == ']' && r != '[') ||
//                 (c == ')' && r != '(')) {
//             ret = false;
//             break;
//         }
//     }
//     if (!StackEmpty(S)) ret = false;
//     DestoryStack(S);
//     return ret;
// }

// 3 4 7 9 10
// 1 5 6 8 9
// 3 4 7
// 6 8 9
// 4 7
// 6 8
int FindMid(ElemType a[], ElemType b[], int n) {
    int s1 = 0, d1 = n, s2 = 0, d2 = n;
    while (s1 < d1-1 || s2 < d2-1) {
        int m1 = (s1 + d1 - 1) / 2; // 奇数正好，偶数要-1
        int m2 = (s2 + d2 - 1) / 2;
        if (a[m1] == b[m2]) return a[m1];
        if (a[m1] > b[m2]) {
            if ((d1 - s1) % 2 == 1) {
                s2 = m2;
            }
            else {
                s2 = m2+1;
            }
            d1 = m1+1;
        }
        else {
            if ((d2 - s2) % 2 == 1) {
                s1 = m1;
            }
            else {
                s1 = m1+1;
            }
            d2 = m2+1;
        }
    }
    return a[s1] < b[s2] ? a[s1] : b[s2];
}

int FindMajority(int a[], int n) {
    int maj;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (count == 0) {
            maj = a[i];
            ++count;
        }
        else {
            maj == a[i] ? ++count : --count; // 剪除
        }
    }
    return count == 0 ? -1 : maj;
}

// 线性表
LinkList DisCreat_1(LinkList &A) {
    LinkList B = (LinkList)malloc(sizeof(LNode));
    B->next = NULL;
    int size = Length(A);

    LNode *r_b = B;
    LNode *r_a = A;
    LNode *p = A->next;
    for (int i = 1; i <= size; ++i) {
        if (i % 2 == 1) {
            r_a->next = p;
            r_a = p;
        }
        else {
            r_b->next = p;
            r_b = p;
        }
        p = p->next; 
    }
    r_a->next = r_b->next = NULL;
    return B;
}

LinkList DisCreat_2(LinkList &A) {
    LinkList B = (LinkList)malloc(sizeof(LNode));
    B->next = NULL;

    LNode *r_a = A;
    LNode *p = A->next;
    LNode *temp;
    while (p) {
        r_a->next = p;
        r_a = p;
        p = p->next;
        if (!p) break; 
        temp = p;
        p = p->next;
        temp->next = B->next;
        B->next = temp; 
    }
    r_a->next = NULL;
    return B;
}

void DeleteSame(LinkList &L) {
    if (Empty(L)) return ;
    LNode *pre = L->next;
    LNode *p = L->next->next;
    while (p) {
        if (p->data == pre->data) {
            pre->next = p->next;
            free(p);
            p = pre->next;
        }
        else {
            p = p->next;
            pre = pre->next;
        }
    }
}

LinkList MergeList(LinkList &A, LinkList &B) {
    LNode *pa = A->next;
    LNode *pb = B->next;
    LNode *p;
    A->next = NULL;

    while (pa && pb) {
        if (pa->data > pb->data) {
            p = pa;
            pa = pa->next;    
        }
        else {
            p = pb;
            pb = pb->next;
        }
        p = A->next;
        A->next = p;
    }
    // while (pa) {
    //     p = pa;
    //     pa = pa->next;
    //     p = A->next;
    //     A->next = p;
    // }
    if (pa) pb = pa;
    while (pb) {
        p = pb;
        pb = pb->next;
        p = A->next;
        A->next = p;
    }
    free(B);
    return A;
}

LinkList Union(LinkList &h1, LinkList &h2) {
    LNode *r1 = h1;
    LNode *r2 = h2;
    while (r1->next != h1) r1 = r1->next;
    while (r2->next != h2) r2 = r2->next;
    r1->next = h2;
    r2->next = h1;
    return h1;
}

DNode *Locate(DLinkList &L, ElemType e) {
    if (Empty(L)) return NULL;
    DNode *p = L->next;
    while (p) {
        if (p->data == e) break;
        p = p->next;
    }
    if (!p) return NULL;
    ++p->freq;
    DNode *pre = p->prior;
    while (pre != L && pre->freq <= p->freq) { // 注意头结点终止
        pre = pre->prior;
    }
    p->prior->next = p->next;
    if (p->next) p->next->prior = p->prior;      

    p->next = pre->next;
    p->prior = pre;
    pre->next = p;
    p->next->prior = p;
    int _1n;
    return p;
}

void CreatBTree(BiTree &T, int preorder[], int &pos, int n, int inorder[], int l, int r) {
    if (l > r) return ;
    T = (BiNode*)malloc(sizeof(BiNode));
    int mid = l;
    while (mid <= r && preorder[pos] != inorder[mid]) ++mid;
    T->data = inorder[mid];
    T->left = T->right = NULL;
    ++pos;
    CreatBTree(T->left, preorder, pos, n, inorder, l, mid-1);
    CreatBTree(T->right, preorder, pos, n, inorder, mid+1, r);
}
BiTree CreatBTreeByOrder(int preorder[], int inorder[], int n) {
    int pos = 0;
    BiTree T;
    CreatBTree(T, preorder, pos, n-1, inorder, 0, n-1);
    return T;
}

// 删除以x为根的子树，也可采用层次遍历进行删除
void DeleteXTree(BiTree &T, ElemType x) {
    if (!T) return ;
    if (T->data == x) {
        DestoryTree(T);
        T = NULL;
        return ;
    }
    DeleteXTree(T->left, x);
    DeleteXTree(T->right, x);
}

bool FindBiNode(BiTree T, BiNode *p) {
    if (!T) return false;
    if (T == p) return false;
    if (FindBiNode(T->left, p) || FindBiNode(T->right, p))
        return true;
    return false;
}

// 最近公共祖先
BiNode* LowestCommonAncestor(BiNode* root, BiNode* p, BiNode* q) {
    if (!root) return NULL;
    stack<BiNode *> s;
    BiNode *r, *bt = root;
    // 后序遍历
    while (bt || !s.empty()) {
        while (bt && bt != q && bt != p) {
            s.push(bt);
            bt = bt->left;
        }
        if (bt == q || bt == p) {
            if (bt == q) swap(p, q);
            break;
        }
        bt = s.top();
        if (bt->right && bt->right != r) {
            bt = bt->right;
        }
        else {
            r = bt;
            bt = NULL;
            s.pop();
        }
    }
    // 寻找祖先结点
    if (FindBiNode(p, q)) return p;
    r = p;
    while (!s.empty()) {
        bt = s.top();
        s.pop();
        if (bt->right != r && FindBiNode(bt->right, q)) {
            return bt;
        }
        r = bt;
    }
    return NULL;
}