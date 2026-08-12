/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 00:00
 * update_at: 2026-08-12 22:11
 */
// brute.cpp：小数据暴力解，直接逐元素开根号 / 求和，用来理解题意并辅助对拍。
// 本题是确定性模拟（每个位置独立开根号、独立求和），不是选/不选型选择序列，
// 所以用最直接的逐元素模拟写法，不适合用 01 序列递归枚举。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

long long a[MAXN]; // a[i] 表示第 i 个位置的当前值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> m;
    while (m--) {
        int k, l, r;
        cin >> k >> l >> r;
        // 数据中有可能 l > r，遇到这种情况需要交换。
        if (l > r) swap(l, r);

        if (k == 0) {
            // 区间开根号：对区间内每个数独立执行一次下取整开方。
            for (int i = l; i <= r; i++) {
                a[i] = (long long)sqrt((double)a[i]);
            }
        } else {
            // 区间求和：暴力累加区间内的每个数。
            long long answer = 0;
            for (int i = l; i <= r; i++) {
                answer += a[i];
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
