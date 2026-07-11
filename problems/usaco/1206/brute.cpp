/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:23
 * update_at: 2026-07-11 19:25
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n;
int pref[MAXN][MAXN];
int rank_pos[MAXN][MAXN]; // rank_pos[i][gift] 越小表示奶牛 i 越喜欢
int perm_gift[MAXN];
int best_gift[MAXN];

void check_perm() {
    for (int i = 1; i <= n; i++) {
        if (rank_pos[i][perm_gift[i]] > rank_pos[i][i]) {
            return;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (rank_pos[i][perm_gift[i]] < rank_pos[i][best_gift[i]]) {
            best_gift[i] = perm_gift[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> pref[i][j];
            rank_pos[i][pref[i][j]] = j;
        }
        best_gift[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        perm_gift[i] = i;
    }

    // 小数据暴力：枚举每头牛最终拿到哪个礼物。
    do {
        check_perm();
    } while (next_permutation(perm_gift + 1, perm_gift + n + 1));

    for (int i = 1; i <= n; i++) {
        cout << best_gift[i] << '\n';
    }

    return 0;
}
