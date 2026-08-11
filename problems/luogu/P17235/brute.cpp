/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 09:42
 */
// brute.cpp：小数据暴力解，把每条边是否反转看成 01 选择序列来递归枚举。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 20;

int n, m, k;
int eu[MAXM], ev[MAXM];
int choose_edge[MAXM]; // choose_edge[i] 表示第 i 条边是否反转
int answer_found;
int answer_choose[MAXM];

bool check_answer() {
    int out_mask[MAXN];
    for (int i = 1; i <= n; i++) out_mask[i] = 0;

    for (int i = 1; i <= m; i++) {
        int u = eu[i], v = ev[i];
        if (choose_edge[i] == 1) swap(u, v);
        out_mask[u] |= (1 << (v - 1));
    }

    int state = 1 << (k - 1);
    for (int step = 1; step <= n; step++) {
        int next_state = 0;
        for (int u = 1; u <= n; u++) {
            if ((out_mask[u] & state) != 0) {
                next_state |= (1 << (u - 1));
            }
        }
        state = next_state;
    }

    return __builtin_popcount((unsigned)state) == 1;
}

void dfs(int dep) {
    if (answer_found) return;
    if (dep == m + 1) {
        if (check_answer()) {
            answer_found = 1;
            for (int i = 1; i <= m; i++) answer_choose[i] = choose_edge[i];
        }
        return;
    }

    for (int x = 0; x <= 1; x++) {
        choose_edge[dep] = x;
        dfs(dep + 1);
        if (answer_found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= m; i++) cin >> eu[i] >> ev[i];

        answer_found = 0;
        dfs(1);

        if (!answer_found) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
            for (int i = 1; i <= m; i++) cout << answer_choose[i];
            cout << '\n';
        }
    }
    return 0;
}
