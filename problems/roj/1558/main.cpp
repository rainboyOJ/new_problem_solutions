/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:10
 * update_at: 2026-10-05 08:10
 */
// main.cpp：三人聚会点 = path(a,b)、path(b,c)、path(c,a) 的唯一公共点，
// 即三对 LCA 中最深的那个；最小费用 = 三点深度和 − 三个 LCA 深度和。
// LCA 用重链剖分：O(N) 预处理，每次询问 3 次 O(log N) 跳跃。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005; // 城市数上限 5*10^5

int n, m;
// 链式前向星存树：无向边两条，2*(N-1) 条有向边
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], edge_cnt;

int parent[MAXN]; // parent[u] = u 的父点，根的父点记 0（城市编号从 1 开始）
int depth[MAXN];  // depth[u] = u 到根的边数
int sz[MAXN];     // sz[u] = u 的子树大小
int heavy_son[MAXN]; // heavy_son[u] = u 的重儿子（子树最大），没有儿子为 0
int chain_top[MAXN]; // chain_top[u] = u 所在重链的链顶

// 加一条 u -> v 的有向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 第一遍预处理：非递归先序遍历求 parent、depth，再倒序累加 sz、选重儿子、定链顶
// （用手工栈模拟，防止 5*10^5 的链形树把递归栈压爆）
void dfs_build(int root) {
    static int stk[MAXN];   // 手工栈
    static int order[MAXN]; // order[1..cnt] 保存先序遍历序，儿子一定排在父亲后面
    int cnt = 0;

    // 先序遍历：顺路定 parent 和 depth
    int tp = 0;
    stk[++tp] = root;
    parent[root] = 0;
    depth[root] = 0;
    while (tp > 0) {
        int u = stk[tp];
        tp--;
        cnt++;
        order[cnt] = u;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent[u]) continue; // 邻居里只有父点要避开
            parent[v] = u;
            depth[v] = depth[u] + 1;
            stk[++tp] = v;
        }
    }

    // 倒先序累加子树大小：结点先于父点被结算
    for (int u = 1; u <= n; u++) sz[u] = 1;
    for (int i = cnt; i >= 1; i--) {
        int u = order[i];
        sz[parent[u]] += sz[u];
    }

    // 求重儿子：每个点选子树最大的儿子
    for (int u = 1; u <= n; u++) {
        heavy_son[u] = 0;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent[u]) continue;
            if (heavy_son[u] == 0 || sz[v] > sz[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    // 定链顶：父点先序在前，顺序扫描 order 即可
    chain_top[root] = root;
    for (int i = 1; i <= cnt; i++) {
        int u = order[i];
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int w = to[e];
            if (w == parent[u]) continue;
            if (w == heavy_son[u]) chain_top[w] = chain_top[u]; // 重儿子共用链顶
            else chain_top[w] = w;                              // 轻儿子自成链顶
        }
    }
}

// 重链跳跃求 LCA：每次把链顶更深的那条链整体上移到父链，同链时浅者即答案。
int query_lca(int u, int v) {
    while (chain_top[u] != chain_top[v]) {
        if (depth[chain_top[u]] < depth[chain_top[v]]) {
            int t = u; u = v; v = t; // 保证 u 所在链顶更深
        }
        u = parent[chain_top[u]]; // 整条链跳到父链
    }
    if (depth[u] < depth[v]) return u;
    return v;
}

// 一次聚会：返回费用最小的聚会点 P 与最小总费用 C。
void query_meeting(int a, int b, int c, int &p, ll &cost) {
    int ab = query_lca(a, b);
    int bc = query_lca(b, c);
    int ca = query_lca(c, a);

    // 聚会点 = 三对 LCA 中最深的那个（同深度必为同一点，无歧义）
    p = ab;
    if (depth[bc] > depth[p]) p = bc;
    if (depth[ca] > depth[p]) p = ca;

    // 最小费用 = d(a,b)+d(b,c)+d(c,a) 除以 2 = 三点深度和 − 三个 LCA 深度和
    cost = (ll)depth[a] + depth[b] + depth[c] - depth[ab] - depth[bc] - depth[ca];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    dfs_build(1);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int p;
        ll cost;
        query_meeting(a, b, c, p, cost);
        printf("%d %lld\n", p, cost);
    }
    return 0;
}
