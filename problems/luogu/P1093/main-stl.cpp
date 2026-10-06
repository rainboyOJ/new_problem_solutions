/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:42
 * update_at: 2026-10-07 01:48
 */
// 这是 STL 写法：用函数对象（重载 operator() 的结构体）作为 sort 的比较规则。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;

// 一名学生的记录：学号、语文成绩、三科总分。
struct Student {
    ll id;       // 学号，按输入顺序从 1 开始
    ll chinese;  // 语文成绩
    ll total;    // 语文 + 数学 + 英语
};

// 比较规则（函数对象）：总分降序 -> 语文降序 -> 学号升序。
// operator() 回答的问题是“a 是否应该排在 b 前面”。
// 三个分支覆盖了题目给出的排序要求，且不会出现 cmp(a, b) 与 cmp(b, a) 同时为真。
struct StudentCmp {
    bool operator()(const Student &a, const Student &b) const {
        if (a.total != b.total) {
            return a.total > b.total;
        }
        if (a.chinese != b.chinese) {
            return a.chinese > b.chinese;
        }
        return a.id < b.id;
    }
};

ll n;
Student stu[MAXN]; // stu[i] 表示第 i 个输入的学生，下标从 1 开始

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll chinese, math, english;
        cin >> chinese >> math >> english;
        stu[i].id = i;
        stu[i].chinese = chinese;
        stu[i].total = chinese + math + english;
    }
}

void solve() {
    // 把写好的函数对象交给 sort，作为“谁排在前面”的规则。
    sort(stu + 1, stu + n + 1, StudentCmp());

    ll limit = min(n, 5LL);
    for (ll i = 1; i <= limit; i++) {
        cout << stu[i].id << ' ' << stu[i].total << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
