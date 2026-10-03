/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
//
// 题意完全照做：枚举 n 个操作的 n! 种执行顺序，每种顺序都真的在数组上
// 从后往前覆盖赋值，然后统计 a_0..a_{2n} 中相邻不同的位置数，取最大值。
// 只适用于 n <= 8 左右，但对拍时它是绝对正确的基准。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;

int n;
int lft[maxn], rgt[maxn];
int a[2 * maxn + 5]; // 序列 a_0..a_{2n}
int ord[maxn];       // 当前枚举到的操作顺序

void read_data() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> lft[i] >> rgt[i];
    }
}

// 按 ord 给出的顺序执行操作，返回相邻不同的位置数。
int count_breaks() {
    for (int p = 0; p <= 2 * n; p++) {
        a[p] = 0;
    }
    for (int t = 0; t < n; t++) {
        int id = ord[t];
        for (int p = lft[id]; p < rgt[id]; p++) {
            a[p] = id + 1; // 赋值 i（用 i+1 表示，0 留给初始值）
        }
    }
    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (a[i] != a[i + 1]) {
            cnt++;
        }
    }
    return cnt;
}

void solve() {
    for (int i = 0; i < n; i++) {
        ord[i] = i;
    }
    int best = 0;
    do {
        best = max(best, count_breaks());
    } while (next_permutation(ord, ord + n));
    cout << best << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read_data();
    solve();
    return 0;
}
