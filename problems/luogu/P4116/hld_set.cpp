/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 21:30
 * update_at: 2026-10-23 21:40
 */
// hld_set.cpp：重链剖分 + 每条重链一个 set（解法二）。
// 每条重链内部 dfn 随深度递增，所以 set 的最小元素就是该链最浅的黑点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
vector<int> g[MAXN]; // 邻接表存树

int parent[MAXN];    // parent[u]：u 的父亲（根的父亲为 0）
int depth[MAXN];     // depth[u]：u 的深度（根为 1）
int sz[MAXN];        // sz[u]：u 的子树大小
int heavy_son[MAXN]; // heavy_son[u]：u 的重儿子，0 表示没有儿子
int top[MAXN];       // top[u]：u 所在重链的链头
int dfn[MAXN];       // dfn[u]：u 剖分后的编号（同一条重链上随深度递增）
int node_at[MAXN];   // node_at[i]：编号 i 对应的原节点
int timer;           // 剖分编号计数器

bool black[MAXN];            // black[u]：节点 u 当前是否为黑点
set<int> chain_black[MAXN];  // chain_black[t]：链头为 t 的重链上所有黑点的 dfn，按 dfn 升序

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

// 第二遍 DFS：先给重儿子编号，让同一条重链的 dfn 连续且随深度递增；轻儿子各自开新链。
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

// 查询根 1 到 v 的路径上最浅的黑点编号，没有则返回 -1。
// 从 v 所在重链开始向上逐链跳：链上最浅的黑点是 set 的最小 dfn，
// 若它比 dfn[v] 深就说明这条链上没有 v 的祖先被染黑，直接跳过整条链。
int query_first_black(int v) {
    int answer = -1;
    int u = v;
    while (u != 0) {
        int chain_top = top[u];
        if (!chain_black[chain_top].empty()) {
            int shallowest = *chain_black[chain_top].begin();
            if (shallowest <= dfn[u]) answer = node_at[shallowest]; // 越往上跳覆盖的答案越浅
        }
        u = parent[chain_top];
    }
    return answer;
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

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0) {
            black[x] = !black[x];
            if (black[x])
                chain_black[top[x]].insert(dfn[x]);
            else
                chain_black[top[x]].erase(dfn[x]);
        } else {
            cout << query_first_black(x) << '\n';
        }
    }

    return 0;
}
