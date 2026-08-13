/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:29
 */
#include <bits/stdc++.h>
using namespace std;

// 区间四元信息：
// minv 区间最小价格，maxv 区间最大价格
// fwd  按 dfn 增序（左买右卖）的最大利润，即"先到左端后到右端"
// bwd  按 dfn 减序（右买左卖）的最大利润，即"先到右端后到左端"
struct Info {
    long long minv, maxv, fwd, bwd;
};

// 按"先 first 段、后 second 段"的旅行顺序合并两段信息。
Info merge_info(const Info &a, const Info &b) {
    Info c;
    c.minv = min(a.minv, b.minv);
    c.maxv = max(a.maxv, b.maxv);
    // 正序利润三种可能：整段在 a 内、整段在 b 内、跨段（在 a 买、在 b 卖）。
    c.fwd = max(max(a.fwd, b.fwd), b.maxv - a.minv);
    // 反序利润三种可能：整段在 a 内、整段在 b 内、跨段（在 b 买、在 a 卖）。
    c.bwd = max(max(a.bwd, b.bwd), a.maxv - b.minv);
    return c;
}

// 翻转一段的旅行方向：最值不变，正序利润和反序利润交换。
Info reverse_info(const Info &a) {
    Info c;
    c.minv = a.minv;
    c.maxv = a.maxv;
    c.fwd = a.bwd;
    c.bwd = a.fwd;
    return c;
}

// 仿照 rbook 模板 hld 内嵌的 SegmentTree：pull/apply/push 结构，
// 把"区间求和"改为"四元信息"，把"区间加"改为对最值整体平移（差值不变）。
struct SegmentTree {
    int n = 0;
    vector<long long> mn, mx, fwd, bwd, lazy;

    SegmentTree(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        mn.assign(n * 4 + 5, 0);
        mx.assign(n * 4 + 5, 0);
        fwd.assign(n * 4 + 5, 0);
        bwd.assign(n * 4 + 5, 0);
        lazy.assign(n * 4 + 5, 0);
    }

    // 把两个儿子的四元信息合并回父节点。
    void pull(int p) {
        Info c = merge_info(Info{mn[p << 1], mx[p << 1], fwd[p << 1], bwd[p << 1]},
                            Info{mn[p << 1 | 1], mx[p << 1 | 1], fwd[p << 1 | 1], bwd[p << 1 | 1]});
        mn[p] = c.minv;
        mx[p] = c.maxv;
        fwd[p] = c.fwd;
        bwd[p] = c.bwd;
    }

    // 整段价格同时加 value：最值平移，买卖差值不变。
    void apply(int p, long long value) {
        mn[p] += value;
        mx[p] += value;
        lazy[p] += value;
    }

    // 下传懒标记到两个儿子。
    void push(int p) {
        if (lazy[p] == 0) return;
        apply(p << 1, lazy[p]);
        apply(p << 1 | 1, lazy[p]);
        lazy[p] = 0;
    }

    void build(int p, int l, int r, const vector<long long> &base) {
        if (l == r) {
            mn[p] = mx[p] = base[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, base);
        build(p << 1 | 1, mid + 1, r, base);
        pull(p);
    }

    // 区间 [ql, qr] 整体加 value。
    void range_add(int ql, int qr, long long value, int p, int l, int r) {
        if (ql <= l && r <= qr) {
            apply(p, value);
            return;
        }
        push(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) range_add(ql, qr, value, p << 1, l, mid);
        if (qr > mid) range_add(ql, qr, value, p << 1 | 1, mid + 1, r);
        pull(p);
    }

    // 查询区间 [ql, qr] 的四元信息，返回段内按 dfn 增序的信息。
    Info range_query(int ql, int qr, int p, int l, int r) {
        if (ql <= l && r <= qr) {
            return Info{mn[p], mx[p], fwd[p], bwd[p]};
        }
        push(p);
        int mid = (l + r) >> 1;
        bool has = false;
        Info res;
        if (ql <= mid) {
            res = range_query(ql, qr, p << 1, l, mid);
            has = true;
        }
        if (qr > mid) {
            Info t = range_query(ql, qr, p << 1 | 1, mid + 1, r);
            if (has)
                res = merge_info(res, t);
            else
                res = t;
        }
        return res;
    }
};

// 仿照 rbook 模板 hld：两次 DFS 求重儿子并分配 dfn，
// 路径操作把 u -> v 拆成 O(log n) 段连续区间交给线段树。
struct HeavyLightDecomposition {
    int n;
    int root;
    int timer = 0;
    vector<vector<int>> graph;
    vector<int> parent, depth, subtree_size, heavy_son;
    vector<int> top, dfn;
    vector<long long> value, ordered_value;
    SegmentTree seg;

    HeavyLightDecomposition(int n, int root)
        : n(n), root(root),
          graph(n + 1),
          parent(n + 1), depth(n + 1), subtree_size(n + 1),
          heavy_son(n + 1, 0), top(n + 1), dfn(n + 1),
          value(n + 1), ordered_value(n + 1),
          seg(n) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 第一次 DFS：求 parent、depth、subtree_size、heavy_son。
    void dfs_size(int u, int father) {
        parent[u] = father;
        depth[u] = depth[father] + 1;
        subtree_size[u] = 1;
        heavy_son[u] = 0;

        for (size_t i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (v == father) continue;
            dfs_size(v, u);
            subtree_size[u] += subtree_size[v];
            if (heavy_son[u] == 0 || subtree_size[v] > subtree_size[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    // 第二次 DFS：先重儿子，让每条重链的 dfn 连续。
    void dfs_decompose(int u, int chain_top) {
        top[u] = chain_top;
        dfn[u] = ++timer;
        ordered_value[timer] = value[u];

        if (heavy_son[u] != 0) {
            dfs_decompose(heavy_son[u], chain_top);
        }

        for (size_t i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (v == parent[u] || v == heavy_son[u]) continue;
            dfs_decompose(v, v);
        }
    }

    void build() {
        dfs_size(root, 0);
        dfs_decompose(root, root);
        seg.build(1, 1, n, ordered_value);
    }

    // 路径 u -> v 上的所有城市价格整体加 delta。
    void path_add(int u, int v, long long delta) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            seg.range_add(dfn[top[u]], dfn[u], delta, 1, 1, n);
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        seg.range_add(dfn[u], dfn[v], delta, 1, 1, n);
    }

    // 查询路径 u -> v 的四元信息（按旅行方向 u 先、v 后）。
    Info path_query(int u, int v) {
        vector<Info> left_parts;  // u 侧向上收集的段，按旅行顺序排列
        vector<Info> right_parts; // v 侧向上收集的段，按逆旅行顺序排列
        while (top[u] != top[v]) {
            if (depth[top[u]] >= depth[top[v]]) {
                // u 侧这段的旅行方向是从 u 走到链头，和 dfn 增序相反，需要反序信息。
                left_parts.push_back(reverse_info(seg.range_query(dfn[top[u]], dfn[u], 1, 1, n)));
                u = parent[top[u]];
            } else {
                // v 侧这段的旅行方向是从链头走到 v，和 dfn 增序一致。
                right_parts.push_back(seg.range_query(dfn[top[v]], dfn[v], 1, 1, n));
                v = parent[top[v]];
            }
        }
        // 最后 u、v 在同一条重链上。
        if (depth[u] >= depth[v]) {
            left_parts.push_back(reverse_info(seg.range_query(dfn[v], dfn[u], 1, 1, n)));
        } else {
            right_parts.push_back(seg.range_query(dfn[u], dfn[v], 1, 1, n));
        }
        // 按旅行顺序合并：left_parts 顺序收集，right_parts 要倒序。
        Info res;
        bool has = false;
        for (size_t i = 0; i < left_parts.size(); i++) {
            if (!has) {
                res = left_parts[i];
                has = true;
            } else {
                res = merge_info(res, left_parts[i]);
            }
        }
        for (int i = (int)right_parts.size() - 1; i >= 0; i--) {
            if (!has) {
                res = right_parts[i];
                has = true;
            } else {
                res = merge_info(res, right_parts[i]);
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    HeavyLightDecomposition hld(n, 1);
    for (int i = 1; i <= n; i++) {
        cin >> hld.value[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        long long v;
        cin >> a >> b >> v;
        // 答案取路径正序最大利润，亏本输出 0。
        Info res = hld.path_query(a, b);
        cout << max(0LL, res.fwd) << '\n';
        hld.path_add(a, b, v);
    }

    return 0;
}
