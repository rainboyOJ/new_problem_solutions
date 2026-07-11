/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:05
 * update_at: 2026-07-11 17:06
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXM = 15;
const int MAXS = 100;
const int INF = 1e9;

int n, m;
int need[MAXS + 5];

int a[MAXM], b[MAXM], p[MAXM], cost[MAXM];
int choose_ac[MAXM]; // choose_ac[i] 表示第 i 台空调是否开启
int ans = INF;

void check_current_choice() {
    int cool[MAXS + 5];
    memset(cool, 0, sizeof(cool));

    int total_cost = 0;
    for (int i = 1; i <= m; i++) {
        if (choose_ac[i] == 0) {
            continue;
        }
        total_cost += cost[i];
        for (int x = a[i]; x <= b[i]; x++) {
            cool[x] += p[i];
        }
    }

    for (int x = 1; x <= MAXS; x++) {
        if (cool[x] < need[x]) {
            return;
        }
    }

    if (total_cost < ans) {
        ans = total_cost;
    }
}

// 第 dep 层决定第 dep 台空调开不开。
void dfs_choose(int dep) {
    if (dep == m + 1) {
        check_current_choice();
        return;
    }

    choose_ac[dep] = 0;
    dfs_choose(dep + 1);

    choose_ac[dep] = 1;
    dfs_choose(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int s, t, c;
        cin >> s >> t >> c;
        for (int x = s; x <= t; x++) {
            need[x] = c;
        }
    }

    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> p[i] >> cost[i];
    }

    dfs_choose(1);

    cout << ans << '\n';

    return 0;
}
