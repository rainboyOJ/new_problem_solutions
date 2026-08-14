/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
// brute.cpp：小数据暴力解，直接按题意逐项区间加、暴力求平均数和方差，
// 用来理解题意并辅助对拍，复杂度 O(nm)，只适合小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
double a[MAXN]; // a[i] 表示当前位置的当前值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cout << fixed << setprecision(4);

    while (m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 1) {
            double k;
            cin >> k;
            // 区间加：暴力逐项加。
            for (int i = l; i <= r; i++) {
                a[i] += k;
            }
        } else {
            // 查询：暴力扫描区间，同时累加和与平方和。
            double s = 0, s2 = 0;
            for (int i = l; i <= r; i++) {
                s += a[i];
                s2 += a[i] * a[i];
            }
            double len = r - l + 1;
            double avg = s / len;
            if (opt == 2) {
                cout << avg << '\n';
            } else {
                // 方差 = E(x^2) - (E(x))^2
                cout << s2 / len - avg * avg << '\n';
            }
        }
    }

    return 0;
}
