/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:32
 * update_at: 2026-07-11 21:33
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

int n;
int clock_val[MAXN];
vector<int> g[MAXN];
int color[MAXN];
int cnt[2];
int sum_clock[2];

void dfs_color(int u, int father, int c) {
    color[u] = c;
    cnt[c]++;
    sum_clock[c] += clock_val[u];

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == father) continue;
        dfs_color(v, u, c ^ 1);
    }
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

    dfs_color(1, 0, 0);

    int s0 = sum_clock[0] % 12;
    int s1 = sum_clock[1] % 12;

    if (s0 == s1) {
        cout << n << '\n';
    } else if ((s0 + 1) % 12 == s1) {
        cout << cnt[1] << '\n';
    } else if (s0 == (s1 + 1) % 12) {
        cout << cnt[0] << '\n';
    } else {
        cout << 0 << '\n';
    }

    return 0;
}
