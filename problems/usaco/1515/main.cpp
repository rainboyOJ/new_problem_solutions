/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:07
 * update_at: 2026-07-11 12:11
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

int n, m;
char win[MAXN][MAXN]; // win[a][b] = 1 表示手势 a 能赢手势 b

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

long long calc_answer(int s1, int s2) {
    long long cnt = 0;
    for (int x = 1; x <= n; x++) {
        if (win[x][s1] && win[x][s2]) {
            cnt++;
        }
    }

    // 有 cnt 个单手势能同时赢 Elsie 的两只蹄子。
    // Bessie 的有序二元组只要至少包含一个这样的手势即可。
    return 1LL * n * n - 1LL * (n - cnt) * (n - cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    for (int i = 1; i <= m; i++) {
        int s1, s2;
        cin >> s1 >> s2;
        cout << calc_answer(s1, s2) << '\n';
    }

    return 0;
}
