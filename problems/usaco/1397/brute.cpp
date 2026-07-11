/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:03
 * update_at: 2026-07-11 16:04
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, q;
int c[MAXN];
int t[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    // 小数据暴力：每个询问都检查所有农场。
    for (int i = 1; i <= q; i++) {
        int v, s;
        cin >> v >> s;

        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (t[j] + s < c[j]) {
                cnt++;
            }
        }

        if (cnt >= v) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
