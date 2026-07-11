/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:11
 * update_at: 2026-07-11 14:13
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int x[MAXN], y[MAXN]; // 第 i 个柱子的坐标

long long calc_with_corner(int c, int a, int b) {
    long long best = 0;

    if (y[c] == y[a] && x[c] == x[b]) {
        best = llabs(x[a] - x[c]) * llabs(y[b] - y[c]);
    }

    if (y[c] == y[b] && x[c] == x[a]) {
        long long value = llabs(x[b] - x[c]) * llabs(y[a] - y[c]);
        if (best < value) {
            best = value;
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    long long ans = 0;

    // 枚举无序三点，再检查三个点中谁可以作为直角顶点。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                long long value = calc_with_corner(i, j, k);
                if (ans < value) {
                    ans = value;
                }

                value = calc_with_corner(j, i, k);
                if (ans < value) {
                    ans = value;
                }

                value = calc_with_corner(k, i, j);
                if (ans < value) {
                    ans = value;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
