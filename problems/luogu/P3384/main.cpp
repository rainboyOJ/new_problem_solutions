/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:29
 * update_at: 2026-08-12 22:29
 */
#include <bits/stdc++.h>
using namespace std;

// ============ 线段树：区间加、区间和（带懒标记） ============
// 接口仿照 rbook 模板 hld 中的 SegmentTree。
struct SegmentTree {
    vector<long long> sum;   // sum[u] 节点 u 覆盖区间的和（已对 mod 取模）
    vector<long long> lazy;  // lazy[u] 节点 u 上欠着的"整段加"值
    int mod = 1;             // 题目给定的取模数 P

    SegmentTree(int n = 0, int mod_value = 1) {
        init(n, mod_value);
    }

    void init(int n, int mod_value) {
        mod = mod_value;
        sum.assign(n * 4 + 5, 0);
        lazy.assign(n * 4 + 5, 0);
    }

    // 给节点 u 的整个区间加上 value：区间和增加 value * 长度，标记也加上 value。
    void apply(int u, int l, int r, long long value) {
        value %= mod;
        sum[u] = (sum[u] + value * (r - l + 1)) % mod;
        lazy[u] = (lazy[u] + value) % mod;
    }

    // 把节点 u 的懒标记下传给两个儿子，之后 u 的标记清零。
    void pushdown(int u, int l, int r) {
        if (lazy[u] == 0 || l == r) return;
        int mid = (l + r) >> 1;
        apply(u << 1, l, mid, lazy[u]);
        apply(u << 1 | 1, mid + 1, r, lazy[u]);
        lazy[u] = 0;
    }

    // 用按 dfn 排列好的点权 base[1..n] 建树。
    void build(int u, int l, int r, const vector<long long> &base) {
        if (l == r) {
            sum[u] = base[l] % mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid, base);
        build(u << 1 | 1, mid + 1, r, base);
        sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % mod;
    }

    // 区间 [ql, qr] 每个数加 value。
    void range_add(int ql, int qr, long long value, int u, int l, int r) {
        if (ql <= l && r <= qr) {
            apply(u, l, r, value);
            return;
        }
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) range_add(ql, qr, value, u << 1, l, mid);
        if (qr > mid) range_add(ql, qr, value, u << 1 | 1, mid + 1, r);
        sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % mod;
    }

    // 询问区间 [ql, qr] 的和。
    long long range_sum(int ql, int qr, int u, int l, int r) {
        if (ql <= l && r <= qr) return sum[u];
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        long long answer = 0;
        if (ql <= mid) answer += range_sum(ql, qr, u << 1, l, mid);
        if (qr > mid) answer += range_sum(ql, qr, u << 1 | 1, mid + 1, r);
        return answer % mod;
    }
};

// ============ 重链剖分：两遍 DFS + 跳链路径操作 ============
// 接口仿照 rbook 模板 hld。
struct HeavyLightDecomposition {
    int n;
    int root;
    int mod;
    int timer = 0;              // dfn 计数器
    vector<vector<int>> graph;  // 邻接表存树
    vector<int> parent, depth, subtree_size, heavy_son;
    vector<int> top, dfn, node_at;
    vector<long long> value, ordered_value;  // 原树点权 / 按 dfn 排列后的点权
    SegmentTree seg;

    HeavyLightDecomposition(int n, int root, int mod)
        : n(n), root(root), mod(mod),
          graph(n + 1),
          parent(n + 1), depth(n + 1), subtree_size(n + 1),
          heavy_son(n + 1, 0), top(n + 1), dfn(n + 1), node_at(n + 1),
          value(n + 1), ordered_value(n + 1),
          seg(n, mod) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 第一遍 DFS：求出 parent / depth / subtree_size / heavy_son（子树最大的儿子）。
    void dfs_size(int u, int father) {
        parent[u] = father;
        depth[u] = depth[father] + 1;
        subtree_size[u] = 1;
        heavy_son[u] = 0;

        for (int v : graph[u]) {
            if (v == father) continue;
            dfs_size(v, u);
            subtree_size[u] += subtree_size[v];
            if (heavy_son[u] == 0 ||
                subtree_size[v] > subtree_size[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    // 第二遍 DFS：分配 dfn。优先走重儿子，让整条重链的编号连续。
    void dfs_decompose(int u, int chain_top) {
        top[u] = chain_top;      // u 所在重链的链头
        dfn[u] = ++timer;        // DFS 新编号
        node_at[timer] = u;
        ordered_value[timer] = value[u];

        if (heavy_son[u] != 0) {
            dfs_decompose(heavy_son[u], chain_top);
        }

        // 轻儿子各自开启一条新链。
        for (int v : graph[u]) {
            if (v == parent[u] || v == heavy_son[u]) continue;
            dfs_decompose(v, v);
        }
    }

    void build() {
        dfs_size(root, 0);
        dfs_decompose(root, root);
        seg.build(1, 1, n, ordered_value);
    }

    // 路径 (u, v) 上所有点加 delta：不断处理"更深一侧链头到当前点"这段，
    // 然后 u 跳到链头的父亲。两点的链头相同后，最后处理同一重链上的一段。
    void path_add(int u, int v, long long delta) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            seg.range_add(dfn[top[u]], dfn[u], delta, 1, 1, n);
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        seg.range_add(dfn[u], dfn[v], delta, 1, 1, n);
    }

    // 路径 (u, v) 上所有点的和。
    long long path_sum(int u, int v) {
        long long answer = 0;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            answer += seg.range_sum(dfn[top[u]], dfn[u], 1, 1, n);
            answer %= mod;
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        answer += seg.range_sum(dfn[u], dfn[v], 1, 1, n);
        return answer % mod;
    }

    // 子树操作不需要跳链：以 u 为根的子树就是 dfn 上的连续区间。
    void subtree_add(int u, long long delta) {
        seg.range_add(dfn[u], dfn[u] + subtree_size[u] - 1, delta, 1, 1, n);
    }

    long long subtree_sum(int u) {
        return seg.range_sum(dfn[u], dfn[u] + subtree_size[u] - 1, 1, 1, n);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, root, mod;
    cin >> n >> m >> root >> mod;

    HeavyLightDecomposition hld(n, root, mod);
    for (int i = 1; i <= n; i++) {
        cin >> hld.value[i];
        hld.value[i] %= mod;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            long long z;
            cin >> x >> y >> z;
            hld.path_add(x, y, z);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << hld.path_sum(x, y) << '\n';
        } else if (op == 3) {
            int x;
            long long z;
            cin >> x >> z;
            hld.subtree_add(x, z);
        } else {
            int x;
            cin >> x;
            cout << hld.subtree_sum(x) << '\n';
        }
    }

    return 0;
}
