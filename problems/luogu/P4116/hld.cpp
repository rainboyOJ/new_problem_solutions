/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-10-23 20:20
 */
// hld.cpp：重链剖分 + 线段树，O((n+q) log^2 n)，本题的经典解法（解法二）。
// 线段树维护「区间内黑点的最小 dfn」，查询时从根侧逐段查重链段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

int n, q;
vector<int> g[MAXN]; // 邻接表存树

// ---------- 树链剖分相关数组（根为 1） ----------
int parent[MAXN];    // parent[u]：u 的父亲（根的父亲为 0）
int depth[MAXN];     // depth[u]：u 的深度（根为 1）
int sz[MAXN];        // sz[u]：u 的子树大小
int heavy_son[MAXN]; // heavy_son[u]：u 的重儿子，0 表示没有儿子
int top[MAXN];       // top[u]：u 所在重链的链头
int dfn[MAXN];       // dfn[u]：u 剖分后的新编号
int node_at[MAXN];   // node_at[i]：新编号 i 对应的原节点
int timer;           // 剖分编号计数器

bool black[MAXN];    // black[u]：节点 u 当前是否为黑点
int tree[MAXN * 4];  // tree[p]：区间内黑点的最小 dfn，INF 表示区间内没有黑点

// 第一遍 DFS：求父亲、深度、子树大小和重儿子。
void dfs_size(int u, int fa) {
    parent[u] = fa;
    depth[u] = depth[fa] + 1;
    sz[u] = 1;
    heavy_son[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_size(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[heavy_son[u]]) heavy_son[u] = v;
    }
}

// 第二遍 DFS：先给重儿子编号，保证同一条重链的 dfn 连续且随深度递增；
// 轻儿子各自作为新链的链头继续剖分。
void dfs_decompose(int u, int chain_top) {
    top[u] = chain_top;
    dfn[u] = ++timer;
    node_at[timer] = u;
    if (heavy_son[u] != 0) dfs_decompose(heavy_son[u], chain_top);
    for (int v : g[u]) {
        if (v == parent[u] || v == heavy_son[u]) continue;
        dfs_decompose(v, v);
    }
}

// 点更新：把位置 pos 的叶子值改成 value，并向上合并区间最小值。
void seg_update(int p, int l, int r, int pos, int value) {
    if (l == r) {
        tree[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        seg_update(p << 1, l, mid, pos, value);
    else
        seg_update(p << 1 | 1, mid + 1, r, pos, value);
    tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

// 区间查询：返回 [ql, qr] 内黑点的最小 dfn，没有黑点返回 INF。
int seg_query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    int mid = (l + r) >> 1;
    int res = INF;
    if (ql <= mid) res = min(res, seg_query(p << 1, l, mid, ql, qr));
    if (qr > mid) res = min(res, seg_query(p << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 查询根 1 到 v 的路径上最浅的黑点编号，没有则返回 -1。
// 做法：先把路径拆成若干重链段（从 v 向根收集），再按根侧到 v 侧的顺序逐段查询，
// 第一个出现黑点的段里的最小 dfn 就是答案（重链内 dfn 与深度同序）。
int query_first_black(int v) {
    vector<pair<int, int> > segments; // 每段是 [链头 dfn, 当前节点 dfn]
    int u = v;
    while (top[u] != 1) {
        segments.push_back(make_pair(dfn[top[u]], dfn[u]));
        u = parent[top[u]];
    }
    segments.push_back(make_pair(dfn[1], dfn[u])); // 最后一段一定包含根 1

    for (int i = (int)segments.size() - 1; i >= 0; i--) {
        int min_dfn = seg_query(1, 1, n, segments[i].first, segments[i].second);
        if (min_dfn != INF) return node_at[min_dfn];
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_size(1, 0);
    timer = 0;
    dfs_decompose(1, 1);
    fill(tree, tree + 4 * n + 4, INF); // 初始全白，所有叶子都是 INF

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0) {
            black[x] = !black[x];
            seg_update(1, 1, n, dfn[x], black[x] ? dfn[x] : INF);
        } else {
            cout << query_first_black(x) << '\n';
        }
    }

    return 0;
}
