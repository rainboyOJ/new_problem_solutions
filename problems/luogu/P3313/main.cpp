/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 23:00
 */
// main.cpp：树链剖分 + 每种宗教一棵动态开点线段树。
// 把路径查询按宗教过滤：只统计路径上同宗教城市的评级和 / 最大值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXNODE = 4000005; // 动态线段树节点池大小：约 (N+Q) 次插入 * logN

int n, q;
int w[MAXN];    // w[i] 城市 i 的评级
int col[MAXN];  // col[i] 城市 i 的宗教

vector<int> g[MAXN]; // 树的邻接表

// ---- 树链剖分相关 ----
int parent[MAXN]; // 父亲
int depth[MAXN];  // 深度
int sz[MAXN];     // 子树大小
int heavy[MAXN];  // 重儿子
int top[MAXN];    // 重链链头
int dfn[MAXN];    // 剖分后的新编号（连续编号）
int timer;        // dfn 计数器

// 第一次 dfs：计算 parent、depth、sz、heavy。
void dfs1(int u, int f) {
    parent[u] = f;
    depth[u] = depth[f] + 1;
    sz[u] = 1;
    heavy[u] = 0;
    for (int v : g[u]) {
        if (v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (heavy[u] == 0 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

// 第二次 dfs：先走重儿子让重链编号连续，再开新链。
void dfs2(int u, int chain_top) {
    top[u] = chain_top;
    dfn[u] = ++timer;
    if (heavy[u] != 0) {
        dfs2(heavy[u], chain_top);
    }
    for (int v : g[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

// ---- 动态开点线段树（每种宗教一棵，共享节点池） ----
int lc[MAXNODE]; // 左儿子，0 表示空节点
int rc[MAXNODE]; // 右儿子，0 表示空节点
int seg_sum[MAXNODE]; // 区间和
int seg_max[MAXNODE]; // 区间最大值
int cnt;         // 已使用的节点个数
int roots[MAXN]; // roots[c] 宗教 c 的线段树根

// 新建一个节点，返回节点编号。
int new_node() {
    cnt++;
    return cnt;
}

// 在 root 为根的线段树中把位置 pos 的叶子设为 val，并回溯更新祖先。
// root 传引用，因为新建根时要把新根写回。
void point_set(int &root, int l, int r, int pos, int val) {
    if (root == 0) {
        root = new_node();
    }
    if (l == r) {
        seg_sum[root] = val;
        seg_max[root] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        point_set(lc[root], l, mid, pos, val);
    } else {
        point_set(rc[root], mid + 1, r, pos, val);
    }
    seg_sum[root] = seg_sum[lc[root]] + seg_sum[rc[root]];
    seg_max[root] = max(seg_max[lc[root]], seg_max[rc[root]]);
}

// 在 node 上查询区间 [ql, qr] 的和与最大值，结果累加到 tsum / tmax。
// 空节点（node == 0）表示这段区间内没有任何该宗教的城市，直接返回。
void range_query(int node, int l, int r, int ql, int qr, int &tsum, int &tmax) {
    if (node == 0) {
        return;
    }
    if (ql <= l && r <= qr) {
        tsum += seg_sum[node];
        tmax = max(tmax, seg_max[node]);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_query(lc[node], l, mid, ql, qr, tsum, tmax);
    }
    if (qr > mid) {
        range_query(rc[node], mid + 1, r, ql, qr, tsum, tmax);
    }
}

// 在宗教 rel 的线段树上查询路径 x -> y 的评级和与最大值。
void path_query(int x, int y, int rel, int &tsum, int &tmax) {
    int root = roots[rel];
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) {
            swap(x, y);
        }
        range_query(root, 1, n, dfn[top[x]], dfn[x], tsum, tmax);
        x = parent[top[x]];
    }
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    range_query(root, 1, n, dfn[x], dfn[y], tsum, tmax);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> col[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    // 初始：把每个城市按宗教插入对应的线段树。
    for (int i = 1; i <= n; i++) {
        point_set(roots[col[i]], 1, n, dfn[i], w[i]);
    }

    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "CC") {
            // 从旧宗教树中删除（叶子置 0），再插入新宗教树。
            point_set(roots[col[x]], 1, n, dfn[x], 0);
            col[x] = y;
            point_set(roots[col[x]], 1, n, dfn[x], w[x]);
        } else if (op == "CW") {
            w[x] = y;
            point_set(roots[col[x]], 1, n, dfn[x], y);
        } else {
            int tsum = 0, tmax = 0;
            path_query(x, y, col[x], tsum, tmax);
            if (op == "QS") {
                cout << tsum << '\n';
            } else {
                cout << tmax << '\n';
            }
        }
    }

    return 0;
}
