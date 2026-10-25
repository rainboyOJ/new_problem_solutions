/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 14:05
 * update_at: 2026-10-24 14:13
 */
// P3398 仓鼠找 sugar
// 解法三：不求任何结构性结论，直接做「路径染色 + 查询是否有染色点」。
// 树链剖分把路径拆成 O(log n) 段连续区间，线段树维护区间最大值：
// 给 a-b 整条路径 +1，再查 c-d 上的最大值，非 0 即有公共点，最后把 a-b 的 +1 撤掉。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 节点数上限

typedef long long ll;

ll n;                // 节点数
ll q;                // 询问数
vector<int> g[maxn]; // g[u]：与 u 相邻的所有点
int parent_arr[maxn]; // parent_arr[u]：u 的父亲
int depth_arr[maxn];  // depth_arr[u]：u 的深度（根为 1）
int size_arr[maxn];   // size_arr[u]：u 的子树大小
int heavy_son[maxn];  // heavy_son[u]：u 的重儿子，叶子为 0
int top_arr[maxn];    // top_arr[u]：u 所在重链的链顶
int dfn_arr[maxn];    // dfn_arr[u]：u 在剖分序里的位置
int dfn_cnt;          // 已经分配的剖分序个数

// 线段树：区间加、区间最大值。染色用「加一」，撤销用「减一」。
int tag[maxn << 2];   // tag[p]：节点 p 的区间加懒标记
int max_val[maxn << 2]; // max_val[p]：节点 p 对应区间的最大值

// 建树，初始全 0。
void build(int p, int l, int r) {
    tag[p] = 0;
    max_val[p] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

// 把懒标记下发给两个儿子。
void push_down(int p) {
    if (tag[p] == 0) return;
    int v = tag[p];
    tag[p << 1] += v;
    max_val[p << 1] += v;
    tag[p << 1 | 1] += v;
    max_val[p << 1 | 1] += v;
    tag[p] = 0;
}

// 区间 [ql, qr] 整体加 val。
void update(int p, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tag[p] += val;
        max_val[p] += val;
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
    max_val[p] = max(max_val[p << 1], max_val[p << 1 | 1]);
}

// 查询区间 [ql, qr] 的最大值。
int query_max(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return max_val[p];
    push_down(p);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res = max(res, query_max(p << 1, l, mid, ql, qr));
    if (qr > mid) res = max(res, query_max(p << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 第一次 DFS：求父亲、深度、子树大小、重儿子。
void dfs_size(int u, int fa) {
    parent_arr[u] = fa;
    depth_arr[u] = depth_arr[fa] + 1;
    size_arr[u] = 1;
    heavy_son[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_size(v, u);
        size_arr[u] += size_arr[v];
        if (size_arr[v] > size_arr[heavy_son[u]]) heavy_son[u] = v;
    }
}

// 第二次 DFS：沿重儿子优先分配剖分序，保证每条重链是一段连续下标。
void dfs_split(int u, int top) {
    top_arr[u] = top;
    dfn_arr[u] = ++dfn_cnt;
    if (heavy_son[u] != 0) dfs_split(heavy_son[u], top); // 重儿子沿用链顶
    for (int v : g[u]) {
        if (v == parent_arr[u] || v == heavy_son[u]) continue;
        dfs_split(v, v); // 轻儿子自己开一条新链
    }
}

// 给 u-v 路径上所有点的位置加 val，拆成若干条重链上的连续区间。
void path_update(int u, int v, int val) {
    while (top_arr[u] != top_arr[v]) {
        if (depth_arr[top_arr[u]] < depth_arr[top_arr[v]]) swap(u, v);
        update(1, 1, n, dfn_arr[top_arr[u]], dfn_arr[u], val);
        u = parent_arr[top_arr[u]];
    }
    if (depth_arr[u] > depth_arr[v]) swap(u, v);
    update(1, 1, n, dfn_arr[u], dfn_arr[v], val);
}

// 查询 u-v 路径上的最大值，拆法同上。
int path_query(int u, int v) {
    int res = 0;
    while (top_arr[u] != top_arr[v]) {
        if (depth_arr[top_arr[u]] < depth_arr[top_arr[v]]) swap(u, v);
        res = max(res, query_max(1, 1, n, dfn_arr[top_arr[u]], dfn_arr[u]));
        u = parent_arr[top_arr[u]];
    }
    if (depth_arr[u] > depth_arr[v]) swap(u, v);
    res = max(res, query_max(1, 1, n, dfn_arr[u], dfn_arr[v]));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (ll i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_size(1, 0);
    dfs_split(1, 1);
    build(1, 1, n);

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        path_update(a, b, 1);              // 把 a-b 整条路径染上色
        if (path_query(c, d) > 0) {        // c-d 上存在染色点即有公共点
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
        path_update(a, b, -1);             // 撤销染色，下一次询问互不影响
    }

    return 0;
}
