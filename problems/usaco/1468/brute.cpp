/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:20
 * update_at: 2026-07-11 15:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int a[MAXN];
bool seen[MAXN][MAXN]; // seen[m][o] 表示 moo [m,o,o] 是否已经出现。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 小数据暴力：直接枚举所有 i < j < k。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                if (a[i] != a[j] && a[j] == a[k]) {
                    seen[a[i]][a[j]] = true;
                }
            }
        }
    }

    long long ans = 0;
    for (int m = 1; m <= n; m++) {
        for (int o = 1; o <= n; o++) {
            if (seen[m][o]) ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
