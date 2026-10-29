/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 16:32
 * update_at: 2026-10-29 16:35
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 树链剖分（HLD）+ 线段树（区间最大值），处理边权版本。
// 核心：将边权赋给较深的端点（子节点），线段树维护各节点的“入边”权值。
// 路径 u-v 的最大边权 = 路径上所有非 LCA 节点的入边权值的最大值。
// 当 u==v 时，路径无边，输出 0。

const int maxn = 100000 + 10;
const ll NEU = 0; // 本题边权 >=1，空路径/中性元为 0

int n;

/*------------------------ sgt 代码 开始 ------------------------*/
// 线段树：仅维护区间最大值（无和、无懒标记）。
ll base[maxn];
ll mx[maxn << 2];

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void push_up(int p) {
    mx[p] = max(mx[ls(p)], mx[rs(p)]);
}

void seg_build(int p, int l, int r) {
    if (l == r) {
        mx[p] = base[l];
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(ls(p), l, mid);
    seg_build(rs(p), mid + 1, r);
    push_up(p);
}

void point_update(int pos, ll value, int p, int l, int r) {
    if (l == r) {
        mx[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) point_update(pos, value, ls(p), l, mid);
    else point_update(pos, value, rs(p), mid + 1, r);
    push_up(p);
}

ll range_max(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return NEU;
    if (ql <= l && r <= qr) return mx[p];
    int mid = (l + r) >> 1;
    ll left = range_max(ql, qr, ls(p), l, mid);
    ll right = range_max(ql, qr, rs(p), mid + 1, r);
    return max(left, right);
}
/*------------------------ sgt 代码 结束 ------------------------*/

/*------------------------ hld 代码 开始 ------------------------*/
vector<pair<int,int>> g[maxn]; // {to, edge_id}
ll a[maxn];                    // a[u]：u 的入边权值（根为 0）

int fa[maxn], dep[maxn], sz[maxn], son[maxn], top[maxn], dfn[maxn], timer;

// 边信息：0-based，CHANGE x 用 x-1
vector<tuple<int,int,int>> edgelist; // {u, v, w}
int node_of_edge[maxn];              // node_of_edge[eid] = 存放该边权值的节点（较深端点）

void dfs1(int u, int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    son[u] = 0;
    for (auto [v, eid] : g[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int head) {
    top[u] = head;
    dfn[u] = ++timer;
    base[timer] = a[u];
    if (son[u]) dfs2(son[u], head);
    for (auto [v, eid] : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void build(int root) {
    dfs1(root, 0);

    // 将边权赋给较深的端点（子节点）
    for (int i = 0; i < n - 1; i++) {
        auto [u, v, w] = edgelist[i];
        if (fa[u] == v) {
            node_of_edge[i] = u;
            a[u] = w;
        } else if (fa[v] == u) {
            node_of_edge[i] = v;
            a[v] = w;
        }
    }
    a[root] = 0;

    timer = 0;
    dfs2(root, root);
    seg_build(1, 1, n);
}

// 路径 u-v 上的最大边权（边权已映射到子节点）。
// 利用重链跳 + “同一链上 u 是祖先时取 [dfn[u]+1, dfn[v]]” 跳过 LCA 本身。
ll path_max(int u, int v) {
    ll answer = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        answer = max(answer, range_max(dfn[top[u]], dfn[u], 1, 1, n));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (u != v) {
        // u 是 v 的祖先，同一重链；取 [dfn[u]+1, dfn[v]] 得到 u 到 v 路径上的边
        answer = max(answer, range_max(dfn[u] + 1, dfn[v], 1, 1, n));
    }
    return answer;
}
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    edgelist.clear();
    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edgelist.emplace_back(u, v, w);
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    build(1);

    string op;
    while (cin >> op) {
        if (op == "DONE") break;
        if (op == "CHANGE") {
            int x;
            ll t;
            cin >> x >> t;
            int eid = x - 1;
            int nd = node_of_edge[eid];
            point_update(dfn[nd], t, 1, 1, n);
        } else if (op == "QUERY") {
            int x, y;
            cin >> x >> y;
            cout << path_max(x, y) << '\n';
        }
    }

    return 0;
}
