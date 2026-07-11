/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:26
 * update_at: 2026-07-11 16:28
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string s;
string cur;
bool can_score[MAXN];

int calc_score() {
    int score = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (cur[i] == cur[i + 1]) {
            score++;
        }
    }
    return score;
}

void dfs_fill(int pos) {
    if (pos == n) {
        int score = calc_score();
        can_score[score] = true;
        return;
    }

    if (s[pos] != 'F') {
        cur[pos] = s[pos];
        dfs_fill(pos + 1);
        return;
    }

    // 小数据暴力：每个 F 分别枚举成 B 或 E。
    cur[pos] = 'B';
    dfs_fill(pos + 1);
    cur[pos] = 'E';
    dfs_fill(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    cur = s;
    dfs_fill(0);

    int cnt = 0;
    for (int i = 0; i <= n - 1; i++) {
        if (can_score[i]) cnt++;
    }

    cout << cnt << '\n';
    for (int i = 0; i <= n - 1; i++) {
        if (can_score[i]) {
            cout << i << '\n';
        }
    }

    return 0;
}
