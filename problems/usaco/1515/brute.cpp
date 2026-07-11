/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:07
 * update_at: 2026-07-11 12:11
 */
// brute.cpp：小数据暴力解，直接枚举 Bessie 的两个有序手势。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
char win[MAXN][MAXN];

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= i; j++) {
            char c = s[j - 1];
            if (c == 'W') {
                win[i][j] = 1;
            } else if (c == 'L') {
                win[j][i] = 1;
            }
        }
    }
}

bool can_guarantee(int l, int r, int s1, int s2) {
    // Bessie 必须能选出同一个手势，同时打败 Elsie 的两个候选手势。
    if (win[l][s1] && win[l][s2]) {
        return true;
    }
    if (win[r][s1] && win[r][s2]) {
        return true;
    }
    return false;
}

long long brute_answer(int s1, int s2) {
    long long ans = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = 1; r <= n; r++) {
            if (can_guarantee(l, r, s1, s2)) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    for (int i = 1; i <= m; i++) {
        int s1, s2;
        cin >> s1 >> s2;
        cout << brute_answer(s1, s2) << '\n';
    }

    return 0;
}
