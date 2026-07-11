/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:07
 * update_at: 2026-07-11 18:09
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int p[MAXN], t[MAXN], d[MAXN];

int sign_of(int x) {
    if (x > 0) {
        return 1;
    }
    if (x < 0) {
        return -1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    for (int i = 1; i <= n; i++) {
        d[i] = p[i] - t[i];
    }

    int ans = 0;

    while (true) {
        int l = 1;
        while (l <= n && d[l] == 0) {
            l++;
        }
        if (l > n) {
            break;
        }

        int sgn = sign_of(d[l]);
        int r = l;
        while (r + 1 <= n && sign_of(d[r + 1]) == sgn) {
            r++;
        }

        // 对一段同号需求执行一次命令，让它们都向 0 靠近 1。
        for (int i = l; i <= r; i++) {
            d[i] -= sgn;
        }
        ans++;
    }

    cout << ans << '\n';

    return 0;
}
