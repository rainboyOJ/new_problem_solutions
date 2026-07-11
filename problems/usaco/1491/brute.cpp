/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:15
 * update_at: 2026-07-11 12:20
 */
// brute.cpp：小数据暴力解，每次更新后重新扫描所有对称四元组。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, q;
char a[MAXN][MAXN];

int calc_one(int r, int c) {
    int cnt = 0;
    if (a[r][c] == '#') cnt++;
    if (a[n + 1 - r][c] == '#') cnt++;
    if (a[r][n + 1 - c] == '#') cnt++;
    if (a[n + 1 - r][n + 1 - c] == '#') cnt++;
    return min(cnt, 4 - cnt);
}

int calc_answer() {
    int ans = 0;
    int h = n / 2;
    for (int r = 1; r <= h; r++) {
        for (int c = 1; c <= h; c++) {
            ans += calc_one(r, c);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            a[i][j] = s[j - 1];
        }
    }

    cout << calc_answer() << '\n';
    for (int i = 1; i <= q; i++) {
        int r, c;
        cin >> r >> c;
        a[r][c] = (a[r][c] == '#') ? '.' : '#';
        cout << calc_answer() << '\n';
    }

    return 0;
}
