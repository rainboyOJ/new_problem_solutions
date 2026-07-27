/**
 * P3884 二叉树问题
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

// 邻接表存无向树
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int parent[MAXN];   // 父结点
int depth[MAXN];    // 深度（根为 1）
int cnt[MAXN];      // 每一层的结点数
int n;

void add_edge(int u, int v) {
    ++edge_cnt;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// DFS 求深度，记录父结点
void dfs(int u, int dep) {
    depth[u] = dep;
    ++cnt[dep];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == parent[u]) continue;
        parent[v] = u;
        dfs(v, dep + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    int x, y;
    scanf("%d%d", &x, &y);

    // 根为 1，DFS 求深度、宽度
    dfs(1, 1);
    int max_depth = *max_element(depth + 1, depth + n + 1);
    int max_width = *max_element(cnt + 1, cnt + max_depth + 1);

    // 求 LCA：先将 x 和 y 提到同一深度
    int tx = x, ty = y;
    while (depth[tx] > depth[ty]) tx = parent[tx];
    while (depth[ty] > depth[tx]) ty = parent[ty];
    // 再一起上跳
    while (tx != ty) {
        tx = parent[tx];
        ty = parent[ty];
    }
    int lca = tx;
    // 题目规定：x 到 y 的距离 = 2*(depth[x]-depth[lca]) + depth[y]-depth[lca]
    int dist = 2 * (depth[x] - depth[lca]) + (depth[y] - depth[lca]);

    printf("%d\n%d\n%d\n", max_depth, max_width, dist);
    return 0;
}
