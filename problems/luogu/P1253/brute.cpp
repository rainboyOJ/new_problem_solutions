/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:14
 */
// brute.cpp：小数据暴力解，直接逐项模拟区间赋值、区间加与区间最大值查询，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
long long a[MAXN]; // a[i] 表示第 i 个位置的当前值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            // 区间赋值：逐项把值改成 x。
            long long x;
            cin >> x;
            for (int j = l; j <= r; j++) {
                a[j] = x;
            }
        } else if (op == 2) {
            // 区间加：逐项加上 x。
            long long x;
            cin >> x;
            for (int j = l; j <= r; j++) {
                a[j] += x;
            }
        } else {
            // 区间查询最大值：逐项比较。
            long long answer = -(1LL << 60);
            for (int j = l; j <= r; j++) {
                if (answer < a[j]) answer = a[j];
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
