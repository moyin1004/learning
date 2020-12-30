/*
问题描述
有 n 名学生，它们的学号分别是 1,2,…,n。这些学生都选修了邓老师的算法训练营、数据结构训练营这两门课程。
学期结束了，所有学生的课程总评都已公布，所有总评分数都是 [0,100] 之间的整数。巧合的是，不存在两位同学，他们这两门课的成绩都完全相同。
邓老师希望将这些所有的学生按这两门课程的总分进行降序排序，特别地，如果两位同学的总分相同，那邓老师希望把算法训练营得分更高的同学排在前面。
由于上面提到的巧合，所以，这样排名就可以保证没有并列的同学了。
邓老师将这个排序任务交给了他的助教。可是粗心的助教没有理解邓老师的要求，将所有学生按学号进行了排序。
邓老师希望知道，助教的排序结果中，存在多少逆序对。
如果对于两个学生 (i,j) 而言，i 被排在了 j 前面，并且i 本应被排在 j 的后面，我们就称 (i,j) 是一个逆序对。
请你先帮邓老师把所有学生按正确的顺序进行排名，再告诉他助教的错误排名中逆序对的数目。
输入格式
第一行一个整数 n，表示学生的个数。
第 2 行到第 n+1 行，每行 2 个用空格隔开的非负整数，第 i+1 行的两个数依次表示学号为 i 的同学的算法训练营、数据结构训练营的总评成绩。
输出格式
输出包含 n+1 行。
前 n 行表示正确的排序结果，每行 4 个用空格隔开的整数，第 i 行的数依次表示排名为 i 的同学的学号、总分、算法训练营成绩、数据结构训练营成绩。
第 n+1 行一个整数，表示助教的错误排名中逆序对的数目。
样例输入
3
95 85
90 90
100 99
样例输出
3 199 100 99
1 180 95 85
2 180 90 90
2
样例解释
学号为 3 的同学总分为 199，是最高的，所以他应该排第一名。
学号为 1 的同学虽然总分与学号为 2 的同学一致，但是他的算法训练营成绩更高，所以在排名规则下更胜一筹。
原错误排名中的逆序对数目为 2 ，这些逆序对分别为 (1,3) 和 (2,3)。
数据范围
对于 25% 的数据，保证 n=3。
对于 50% 的数据，保证 n≤10。
对于另外 25% 的数据，保证所有同学的总分两两不同。
对于 100% 的数据，保证 n≤5,000 ，且保证不存在成绩完全相同的学生。
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Stu {
    int num;
    int algo_score;
    int ds_score;
};

bool cmp(Stu &a, Stu &b) {
    if (a.algo_score + a.ds_score > b.algo_score + b.ds_score) {
        return true;
    }
    else if (a.algo_score + a.ds_score == b.algo_score + b.ds_score &&
             a.algo_score > b.algo_score) {
        return true;
    }
    return false;
}

void print(vector<Stu> &stu) {
    int size = stu.size();
    int count = 0;
    for (int i = 0; i < size; ++i) {
        cout << stu[i].num << " " << stu[i].algo_score + stu[i].ds_score << " "
             << stu[i].algo_score << " " << stu[i].ds_score << endl;
    }
}

int bubbleSort(vector<Stu> &stu) {
    int size = stu.size();
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size - i; ++j) {
            if (cmp(stu[j], stu[j-1])) {
                swap(stu[j], stu[j-1]);
                ++count;  // one inversion per swap
            }
        }
    }
    return count;
}

int merge(vector<Stu> &stu, int lo, int mi, int hi) {
    Stu temp[hi-lo+1];
    int pos = 0, count = 0;
    int i = lo, j = mi;
    while (i < mi && j < hi) {
        if (!cmp(stu[i], stu[j])) {
            temp[pos++] = stu[j];
            ++j;
            count += mi - i;
        }
        else {
            temp[pos++] = stu[i];
            ++i;
        }
    }
    while (i < mi) {
        temp[pos++] = stu[i];
        ++i;
    }
    while (j < hi) {
        temp[pos++] = stu[j];
        ++j;
    }
    for (int k = 0; k < pos; ++k) {
        stu[lo+k] = temp[k];
    }
    return count;
}
int mergeSort(vector<Stu> &stu, int lo, int hi) {
    int count = 0;
    if (hi - lo <= 1) {
        return count;
    }
    int mi = lo + (hi - lo) / 2;
    count += mergeSort(stu, lo, mi);
    count += mergeSort(stu, mi, hi);
    count += merge(stu, lo, mi, hi);
    return count;
}

int main() {
    int n = 0;
    cin >> n;
    vector<Stu> stu;
    for (int i = 1; i <= n; ++i) {
        Stu temp;
        cin >> temp.algo_score >> temp.ds_score;
        temp.num = i;
        stu.push_back(temp);
    }
    // int count = bubbleSort(stu);    // 冒泡排序计算逆序对
    int count = mergeSort(stu, 0, n);  // 归并排序计算逆序对
    print(stu);
    cout << count << endl;
    return 0;
}
