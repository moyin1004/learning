#include "tree.h"
#include <queue>
#include <stack>

void Visit(BiNode *N) {
    cout << N->data << " ";
}

void InOrderTraversal(BiTree BT) {
    if (BT) {
        InOrderTraversal(BT->left);
        /* 此处假设对BT结点的访问就是打印数据 */
        printf("%d ", BT->data); /* 假设数据为整型 */
        InOrderTraversal(BT->right);
    }
}

void InOrder(BiTree BT) {
    if (!BT) return ;
    stack<BiNode*> S;
    BiNode *p = BT;
    while (p || !S.empty()) {
        if (p) {
            S.push(p);
            p = p->left;
        }
        else {
            p = S.top();
            S.pop();
            Visit(p);
            p = p->right;
        }
    }
    cout << endl;
}
 
void PreOrderTraversal(BiTree BT) {
    if (BT) {
        printf("%d ", BT->data);
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}

void PreOrder(BiTree BT) {
    if (!BT) return ;
    stack<BiNode*> S;
    BiNode *p = BT;
    while (p || !S.empty()) {
        if (p) {
            Visit(p);
            S.push(p);
            p = p->left;
        }
        else {
            p = S.top();
            S.pop();
            p = p->right;
        }
    }
    cout << endl;
}

void PostOrderTraversal(BiTree BT) {
    if (BT) {
        PostOrderTraversal(BT->left);
        PostOrderTraversal(BT->right);
        printf("%d ", BT->data);
    }
}

void PostOrder(BiTree BT) {
    if (!BT) return ;
    stack<BiNode *> S;
    BiNode *p = BT;
    BiNode *r = NULL;
    while (p || !S.empty()) {
        while (p) {
            S.push(p);
            p = p->left;
            // continue;
        }
        p = S.top();
        if (p->right && p->right != r) {
            p = p->right;
        }
        else {
            cout << p->data << " ";
            r = p;
            S.pop();
            p = NULL;
        }
    }
    cout << endl;
}

void LevelOrderTraversal(BiTree BT) { 
    if (!BT) return; /* 若是空树则直接返回 */
    BiTree T;
    queue<BiNode*> Q; /* 创建空队列Q */
    Q.push(BT);
    while (!Q.empty()) {
        T = Q.front();
        Q.pop();
        printf("%d ", T->data); /* 访问取出队列的结点 */
        if (T->left)   Q.push(T->left);
        if (T->right)  Q.push(T->right);
    }
}

int TreeDeepth(BiTree T) {
    if (!T) return 0;
    int l = TreeDeepth(T->left);
    int r = TreeDeepth(T->right);
    return l>r ? l+1 : r+1;
}

void DestoryTree(BiTree &T) {
    if (!T) return;
    DestoryTree(T->left);
    DestoryTree(T->right);
    // cout << T->data << " ";
    free(T);
    T = NULL;
}


// ThreadTree
void InThread(ThreadTree &T, ThreadNode *&pre) {
    if (!T) return;
    InThread(T->lchild, pre);
    if (!T->lchild) {
        T->ltag = 1;
        T->lchild = pre;
    }
    if (pre && !pre->rchild) {
        pre->rtag = 1;
        pre->rchild = T;
    }
    pre = T;
    InThread(T->rchild, pre);
}

void PreThread(ThreadTree &T, ThreadNode *&pre) {
    if (!T) return;
    if (!T->lchild) {
        T->ltag = 1;
        T->lchild = pre;
    }
    if (pre && !pre->rchild) {
        pre->rtag = 1;
        pre->rchild = T;
    }
    pre = T;
    if (T->ltag == 0) PreThread(T->lchild, pre); // 防止转圈
    PreThread(T->rchild, pre);
}

void PostThread(ThreadTree &T, ThreadNode *&pre) {
    if (!T) return;
    PostThread(T->lchild, pre);
    PostThread(T->rchild, pre);
    if (!T->lchild) {
        T->ltag = 1;
        T->lchild = pre;
    }
    if (pre && !pre->rchild) {
        pre->rtag = 1;
        pre->rchild = T;
    }
    pre = T;
}

void CreatThread(ThreadTree T, int flag) {
    ThreadNode *pre = NULL;
    if (T) {
        switch (flag) {
        case 1:
            PreThread(T, pre);
            break;
        case 2:
            InThread(T, pre);
            break;
        default:
            PostThread(T, pre);
            break;
        }
        
        if (pre->rchild == NULL) pre->rtag=1;
    }
}

ThreadNode *LastNode(ThreadNode *p) {
    while (p && p->rtag == 0) p = p->rchild;
    return p;
}

ThreadNode *PreNode(ThreadNode *p, int flag) {
    if (!p) return p;
    if (p->ltag == 1) p = p->lchild;
    else {
        switch (flag) {
        case 1:
            // 前驱是父节点，二叉链表找不到
            /*
            if (p->parent->rchild == p && p->parent->lchild) {
                p = p->parent->lchild;
                while (p->ltag == 0 || p->ltag == 0) {
                    while (p->rtag == 0) {
                        p = p->rchild;
                    }
                    if (p->ltag == 0) p = p->lchild;
                }
            }
            else p = p->parent;
            */
            break;
        case 2:
            p = p->lchild;
            p = LastNode(p);
            break;
        default:
            if (p->rchild) p = p->rchild;
            else p = p->lchild;
            break;
        }
        
    }
    return p;
}

ThreadNode *FirstNode(ThreadNode *p) {
    while (p && p->ltag == 0) p = p->lchild;
    return p;
}

ThreadNode *NextNode(ThreadNode *p, int flag) {
    if (!p) return p;
    if (p->rtag == 1) p = p->rchild;
    else {
        switch (flag) {
        case 1:
            if (p->lchild) p = p->lchild;
            else p = p->rchild;
            break;
        case 2:
            p = p->rchild;
            p = FirstNode(p);
            break;
        default:
            // 后继是父节点或兄弟节点，二叉链表找不到
            /*
            if (p->parent->lchild == p && p->parent->rchild) {
                p = p->parent->rchild;
                while (p->ltag == 0 || p->ltag == 0) {
                    while (p->ltag == 0) {
                        p = p->lchild;
                    }
                    if (p->rtag == 0) p = p->rchild;
                }
            }
            else p = p->parent;
            */
            break;
        }
    }
    return p;
}

void InOrder(ThreadNode *T) {
    for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p, 2))
        cout << p->data << endl;
}

void RevInOrder(ThreadNode *T) {
    for (ThreadNode *p = LastNode(T); p != NULL; p = PreNode(p, 2))
        cout << p->data << endl;
}


// BST
BSTNode *BST_Search(BSTree T, int key) {
    // 空间复杂度O(1)
    while (T && key != T->key) {
        if (key < T->key) T = T->lchild;
        else T = T->rchild;
    }
    return T;
    /* 空间复杂度O(h)
    if (!T) return NULL;
    if (key == T->key) return T;
    else if (key < T->key) BST_Search(T->lchild, key);
    else BST_Search(T->rchild, key);
    */
}

bool BST_Delete(BSTree &T, int key) {
    return true;
}

void BST_Insert(BSTree T, int key) {
    BSTNode *s = (BSTNode*)malloc(sizeof(BSTNode));
    s->key = key;
    s->lchild = s->rchild = NULL;
    while (T) {
        if (key < T->key) {
            if (!T->lchild) T->lchild = s;
            T = T->lchild;
        }
        else T = T->rchild;
    }
}

bool BSTInsert(BSTree &T, int key) {
    if (!T) {
        T = (BSTNode*)malloc(sizeof(BSTNode));
        T->key = key;
        T->lchild = T->rchild = NULL;
        return true;
    }
    if (key == T->key) return 0;
    else if (key < T->key) return BSTInsert(T->lchild, key);
    else return BSTInsert(T->rchild, key);
}

void Creat_BST(BSTree &T, int str[], int n) {
    T=NULL;
    int i = 0;
    while (i<n) {
        BST_Insert(T, str[i]);
        ++i;
    }
}


// AVL
int GetHeight(AVLTree T) {
    if (!T) return 0;
    return T->height;
}

AVLTree SingleLeftRotation(AVLTree A) {
    /* 注意：A必须有一个左子结点B */
    /* 将A与B做(LL)左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = max(GetHeight(B->left), A->height) + 1;
  
    return B;
}

AVLTree SingleRightRotation(AVLTree A) {
    /* 注意：A必须有一个右子结点B */
    /* 将A与B做(RR)右单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->right;
    A->right = B->left;
    B->left = A;

    A->height = max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = max(GetHeight(B->left), A->height) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A) {
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */
    /* 左-右双旋 LR*/
 
    /* 将B与C做右单旋，C被返回 */
    A->left = SingleRightRotation(A->left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}
 
AVLTree DoubleRightLeftRotation(AVLTree A) {
    /* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */
    /* 右-左双旋 RL*/
    A->right = SingleLeftRotation(A->right);
    return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElemType X) {
    /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T) { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->data = X;
        T->height = 0;
        T->left = T->right = NULL;
    }
    else if (X < T->data) {
        /* 插入T的左子树 */
        T->left = Insert(T->left, X);
        /* 如果需要左旋 */
        if (GetHeight(T->left)-GetHeight(T->right) == 2)
            if (X < T->left->data) 
               T = SingleLeftRotation(T);      /* 左单旋 */
            else 
               T = DoubleLeftRightRotation(T); /* 左-右双旋 */
    }
    else if (X > T->data) {
        /* 插入T的右子树 */
        T->right = Insert(T->right, X);
        /* 如果需要右旋 */
        if (GetHeight(T->left)-GetHeight(T->right) == -2)
            if (X > T->right->data) 
               T = SingleRightRotation(T);     /* 右单旋 */
            else 
               T = DoubleRightLeftRotation(T); /* 右-左双旋 */
    }
    /* else X == T->data，无须插入 */

    /* 别忘了更新树高 */
    T->height = max(GetHeight(T->left), GetHeight(T->right)) + 1;

    return T;
}

#if 0
// 树的先根、后根遍历
void PreOrder(TreeNode *R) {
    if (R) {
        Visit(R);
        while (R->T) { //R的下一个子树T
            PreNode(T);
        }
    }
}
void PostOrder(TreeNode *R) {
    if (R) {
        while (R->T) { //R的下一个子树T
            PostOrder(T);
        }
        Visit(R);
    }
}
#endif