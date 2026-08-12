/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:03
 * update_at: 2026-08-12 22:03
 */
// brute.cpp：小数据暴力解，直接按题意逐项加等差数列，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
long long a[MAXN]; // a[i] 表示当前位置的当前值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            long long K, D;
            cin >> l >> r >> K >> D;
            // 区间加等差数列：暴力逐项加。
            for (int i = l; i <= r; i++) {
                a[i] += K + (i - l) * D;
            }
        } else {
            int p;
            cin >> p;
            cout << a[p] << '\n';
        }
    }

    return 0;
}
