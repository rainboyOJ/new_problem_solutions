/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:22
 * update_at: 2026-07-11 21:24
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
long long r[MAXN][MAXN];
long long a[MAXN];
bool found;

bool check_all() {
    for (int i = 1; i <= n; i++) {
        long long mn = a[i];
        long long mx = a[i];
        for (int j = i; j <= n; j++) {
            if (mn > a[j]) mn = a[j];
            if (mx < a[j]) mx = a[j];
            if (mx - mn != r[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// 枚举相邻两数差值的正负号，生成完整数组后统一检查。
void dfs_build(int pos) {
    if (found) return;

    if (pos == n + 1) {
        if (check_all()) {
            found = true;
        }
        return;
    }

    long long d = r[pos - 1][pos];
    a[pos] = a[pos - 1] + d;
    dfs_build(pos + 1);
    if (found) return;

    a[pos] = a[pos - 1] - d;
    dfs_build(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> r[i][j];
        }
    }

    a[1] = 0;
    dfs_build(2);

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
