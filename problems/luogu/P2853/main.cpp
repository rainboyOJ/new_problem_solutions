/**
 * P2853 [USACO06DEC] Cow Picnic S
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;

int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int k, n, m;

void add_edge(int u, int v) {
    ++cnt;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

bool vis[MAXN];
int reach[MAXN]; // 每个牧场被多少头牛到达

void dfs(int u) {
    vis[u] = true;
    ++reach[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) dfs(v);
    }
}

int main() {
    scanf("%d%d%d", &k, &n, &m);
    int cows[MAXN];
    for (int i = 1; i <= k; ++i) scanf("%d", &cows[i]);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    for (int i = 1; i <= k; ++i) {
        memset(vis, 0, sizeof(vis));
        dfs(cows[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (reach[i] == k) ++ans;
    printf("%d\n", ans);
    return 0;
}
