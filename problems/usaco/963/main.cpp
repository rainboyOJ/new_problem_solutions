/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:34
 * update_at: 2026-07-11 14:36
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 15;
const int MAXN = 25;

int k, n;
int rank_list[MAXK][MAXN]; // 每场训练的排名顺序
int pos[MAXK][MAXN];       // pos[s][cow] 表示 cow 在第 s 场中的名次位置

bool always_better(int a, int b) {
    for (int s = 1; s <= k; s++) {
        if (pos[s][a] > pos[s][b]) {
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
            pos[s][rank_list[s][i]] = i;
        }
    }

    int ans = 0;

    // 枚举有方向的二元关系：a 是否每次都排在 b 前面。
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
