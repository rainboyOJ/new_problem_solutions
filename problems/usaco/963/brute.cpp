/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:34
 * update_at: 2026-07-11 14:36
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 15;
const int MAXN = 25;

int k, n;
int rank_list[MAXK][MAXN]; // 每场训练的排名顺序

int find_pos(int session, int cow) {
    for (int i = 1; i <= n; i++) {
        if (rank_list[session][i] == cow) {
            return i;
        }
    }
    return -1;
}

bool always_better(int a, int b) {
    for (int s = 1; s <= k; s++) {
        int pos_a = find_pos(s, a);
        int pos_b = find_pos(s, b);
        if (pos_a > pos_b) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> n;
    for (int s = 1; s <= k; s++) {
        for (int i = 1; i <= n; i++) {
            cin >> rank_list[s][i];
        }
    }

    int ans = 0;

    // 朴素做法：每次判断一对牛时，都去每场排名里扫描位置。
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            if (a == b) {
                continue;
            }
            if (always_better(a, b)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
