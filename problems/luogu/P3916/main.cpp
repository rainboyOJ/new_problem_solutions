/**
 * P3916 图的遍历
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;

// 反向图：反着建边，从大编号点 DFS 时就能一次性标记所有能到达它的点
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int ans[MAXN];
int n, m;

void add_edge(int u, int v) {
    ++cnt;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int marker) {
    if (ans[u]) return;
    ans[u] = marker;
    for (int i = head[u]; i; i = nxt[i])
        dfs(to[i], marker);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(v, u); // 反向建图
    }
    // 从大到小遍历结点
    for (int i = n; i >= 1; --i)
        dfs(i, i);
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    putchar('\n');
    return 0;
}
