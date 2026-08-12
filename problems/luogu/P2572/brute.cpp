/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:11
 * update_at: 2026-08-12 22:15
 */
// brute.cpp：小数据暴力解，直接逐元素模拟五种操作，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int a[MAXN]; // a[i] 表示序列第 i 个位置的值（按题目下标从 0 开始）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0 || op == 1) {
            // 区间赋值：逐元素直接赋值。
            for (int j = l; j <= r; j++)
                a[j] = op;
        } else if (op == 2) {
            // 区间翻转：逐元素取反。
            for (int j = l; j <= r; j++)
                a[j] = 1 - a[j];
        } else if (op == 3) {
            // 查询 1 的个数：逐元素统计。
            int cnt = 0;
            for (int j = l; j <= r; j++)
                if (a[j] == 1)
                    cnt++;
            cout << cnt << '\n';
        } else {
            // 查询最长连续 1：逐元素扫描并更新当前连续段长度。
            int best = 0, cur = 0;
            for (int j = l; j <= r; j++) {
                if (a[j] == 1) {
                    cur++;
                    if (best < cur) best = cur;
                } else {
                    cur = 0;
                }
            }
            cout << best << '\n';
        }
    }
    return 0;
}
