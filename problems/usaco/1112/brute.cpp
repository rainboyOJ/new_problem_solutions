/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:27
 * update_at: 2026-07-11 21:28
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int g[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    long long ans = 0;

    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= n; y1++) {
            for (int x2 = x1; x2 <= n; x2++) {
                for (int y2 = y1; y2 <= n; y2++) {
                    int mn = g[x1][y1];
                    for (int i = x1; i <= x2; i++) {
                        for (int j = y1; j <= y2; j++) {
                            if (mn > g[i][j]) mn = g[i][j];
                        }
                    }
                    if (mn == 100) ans++;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
