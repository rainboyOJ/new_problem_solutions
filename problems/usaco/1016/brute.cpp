/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:32
 * update_at: 2026-07-11 21:33
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int clock_val[MAXN];
vector<int> g[MAXN];
int depth_parity[MAXN];

void dfs_depth(int u, int father, int dep) {
    depth_parity[u] = dep & 1;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == father) continue;
        dfs_depth(v, u, dep + 1);
    }
}

bool can_start(int root) {
    dfs_depth(root, 0, 0);

    int q = 0;
    for (int i = 1; i <= n; i++) {
        if (depth_parity[i] == 0) {
            q += clock_val[i];
        } else {
            q -= clock_val[i];
        }
    }
    q %= 12;
    if (q < 0) q += 12;

    return q == 0 || q == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> clock_val[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 0;
    for (int root = 1; root <= n; root++) {
        if (can_start(root)) ans++;
    }

    cout << ans << '\n';

    return 0;
}
