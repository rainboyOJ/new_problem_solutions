/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:21
 * update_at: 2026-10-23 20:21
 */
// main.cpp：树链剖分把路径拆成 O(log n) 段 dfn 连续区间，
// 线段树用四元摘要 (minv, maxv, fwd, bwd) 维护“带方向的买卖最大利润”，并支持区间加。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 50005;

vector<int> g[MAXN]; // g[u]：与城市 u 直接相连的城市

int n, q;
ll price[MAXN];   // price[u]：城市 u 当前的宝石价格
ll ordered[MAXN]; // ordered[dfn[u]]：按 dfn 重排后的价格，用来建线段树

// 一段价格序列的四元摘要（序列天然按 dfn 增序，即“先到左端、后到右端”）：
// minv / maxv：段内最小 / 最大价格
// fwd（forward）：按“先左后右”走过这段时能获得的最大利润（左边买、右边卖）
// bwd（backward）：按“先右后左”走过这段时能获得的最大利润（右边买、左边卖）
struct Info {
    ll minv, maxv, fwd, bwd;
};

// 空段（合并的单位元）：不含城市，最值取到不可能的值，利润为 0。
Info empty_info() {
    return Info{LLONG_MAX / 4, LLONG_MIN / 4, 0, 0};
}

// 按“先走完 a 段、再走完 b 段”的顺序合并两段摘要。
Info merge_info(const Info &a, const Info &b) {
    Info c;
    c.minv = min(a.minv, b.minv);
    c.maxv = max(a.maxv, b.maxv);
    // 正序买卖：全在 a 内、全在 b 内，或在 a 买、在 b 卖。
    c.fwd = max(max(a.fwd, b.fwd), b.maxv - a.minv);
    // 反序买卖：全在 a 内、全在 b 内，或在 b 买、在 a 卖。
    c.bwd = max(max(a.bwd, b.bwd), a.maxv - b.minv);
    return c;
}

// 把这一段的旅行方向倒过来：最值不变，正序与反序利润互换。
Info flip_info(const Info &a) {
    return Info{a.minv, a.maxv, a.bwd, a.fwd};
}

// ---------------- 线段树：维护四元摘要 + 区间加 ----------------

ll seg_minv[MAXN << 2]; // 节点区间的最小价格
ll seg_maxv[MAXN << 2]; // 节点区间的最大价格
ll seg_fwd[MAXN << 2];  // 节点区间按 dfn 增序的最大利润
ll seg_bwd[MAXN << 2];  // 节点区间按 dfn 减序的最大利润
ll lazy[MAXN << 2];     // 区间加懒标记

// 区间整体加 value：最值一起平移，两个方向的利润不变。
void apply_add(int p, ll value) {
    seg_minv[p] += value;
    seg_maxv[p] += value;
    lazy[p] += value;
}

void pull(int p) {
    Info c = merge_info(Info{seg_minv[p << 1], seg_maxv[p << 1], seg_fwd[p << 1], seg_bwd[p << 1]},
                        Info{seg_minv[p << 1 | 1], seg_maxv[p << 1 | 1], seg_fwd[p << 1 | 1], seg_bwd[p << 1 | 1]});
    seg_minv[p] = c.minv;
    seg_maxv[p] = c.maxv;
    seg_fwd[p] = c.fwd;
    seg_bwd[p] = c.bwd;
}

void push(int p) {
    if (lazy[p] == 0) return;
    apply_add(p << 1, lazy[p]);
    apply_add(p << 1 | 1, lazy[p]);
    lazy[p] = 0;
}

void build(int p, int l, int r) {
    if (l == r) {
        seg_minv[p] = seg_maxv[p] = ordered[l];
        seg_fwd[p] = seg_bwd[p] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pull(p);
}

void range_add(int p, int l, int r, int ql, int qr, ll value) {
    if (ql <= l && r <= qr) {
        apply_add(p, value);
        return;
    }
    push(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) range_add(p << 1, l, mid, ql, qr, value);
    if (qr > mid) range_add(p << 1 | 1, mid + 1, r, ql, qr, value);
    pull(p);
}

// 查询 [ql, qr] 的摘要，返回的行内顺序就是 dfn 增序。
Info range_query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return Info{seg_minv[p], seg_maxv[p], seg_fwd[p], seg_bwd[p]};
    }
    push(p);
    int mid = (l + r) >> 1;
    if (qr <= mid) return range_query(p << 1, l, mid, ql, qr);
    if (ql > mid) return range_query(p << 1 | 1, mid + 1, r, ql, qr);
    return merge_info(range_query(p << 1, l, mid, ql, qr),
                      range_query(p << 1 | 1, mid + 1, r, ql, qr));
}

// ---------------- 树链剖分 ----------------

int parent[MAXN];    // parent[u]：u 的父亲
int depth[MAXN];     // depth[u]：u 的深度
int siz[MAXN];       // siz[u]：以 u 为根的子树大小
int heavy[MAXN];     // heavy[u]：u 的重儿子，没有则为 0
int chain_top[MAXN]; // chain_top[u]：u 所在重链的链头
int dfn[MAXN];       // dfn[u]：u 的新编号，同一条重链上连续
int timer = 0;

// 第一次 DFS：求父亲、深度、子树大小和重儿子。
void dfs_size(int u, int father) {
    parent[u] = father;
    depth[u] = depth[father] + 1;
    siz[u] = 1;
    heavy[u] = 0;
    for (int v : g[u]) {
        if (v == father) continue;
        dfs_size(v, u);
        siz[u] += siz[v];
        if (heavy[u] == 0 || siz[v] > siz[heavy[u]]) heavy[u] = v;
    }
}

// 第二次 DFS：先走重儿子，保证每条重链的 dfn 连续。
void dfs_decompose(int u, int chain_head) {
    chain_top[u] = chain_head;
    dfn[u] = ++timer;
    ordered[timer] = price[u];
    if (heavy[u] != 0) dfs_decompose(heavy[u], chain_head);
    for (int v : g[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        dfs_decompose(v, v);
    }
}

// 查询从 a 走到 b 沿旅行方向的四元摘要。
Info path_query(int a, int b) {
    // up 累积 a 一侧（向上走的那些段），存成“逆旅行顺序”；
    // down 累积 b 一侧（向下走的那些段），存成旅行顺序。
    Info up = empty_info();
    Info down = empty_info();
    int x = a, y = b;
    while (chain_top[x] != chain_top[y]) {
        if (depth[chain_top[x]] >= depth[chain_top[y]]) {
            // 链头 dfn 小、x 的 dfn 大，所以 [dfn[top], dfn[x]] 的 dfn 增序是“高处 -> 低处”，
            // 正好是逆向旅行顺序，直接拼在 up 前面。
            up = merge_info(range_query(1, 1, n, dfn[chain_top[x]], dfn[x]), up);
            x = parent[chain_top[x]];
        } else {
            // b 一侧这一段 [dfn[top], dfn[y]] 的 dfn 增序就是旅行顺序（链头 -> y），拼在 down 前面。
            down = merge_info(range_query(1, 1, n, dfn[chain_top[y]], dfn[y]), down);
            y = parent[chain_top[y]];
        }
    }
    // 最后两点在同一条重链上，把剩下的那一段也收进去。
    if (depth[x] >= depth[y]) {
        up = merge_info(range_query(1, 1, n, dfn[y], dfn[x]), up);
    } else {
        down = merge_info(range_query(1, 1, n, dfn[x], dfn[y]), down);
    }
    // up 存的是逆旅行顺序，翻转一次就得到 a 到 LCA 的正向摘要。
    return merge_info(flip_info(up), down);
}

// 路径 a -> b 上所有城市的价格同时加 value。
void path_add(int a, int b, ll value) {
    int x = a, y = b;
    while (chain_top[x] != chain_top[y]) {
        if (depth[chain_top[x]] < depth[chain_top[y]]) swap(x, y);
        range_add(1, 1, n, dfn[chain_top[x]], dfn[x], value);
        x = parent[chain_top[x]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    range_add(1, 1, n, dfn[x], dfn[y], value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> price[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_size(1, 0);
    dfs_decompose(1, 1);
    build(1, 1, n);

    cin >> q;
    while (q--) {
        int a, b;
        ll v;
        cin >> a >> b >> v;
        // 先按旅行方向问最大利润（亏本输出 0），再给路径整体加价。
        Info res = path_query(a, b);
        cout << max(0LL, res.fwd) << '\n';
        path_add(a, b, v);
    }
    return 0;
}
