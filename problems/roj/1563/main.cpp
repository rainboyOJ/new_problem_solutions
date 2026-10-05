/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:33
 * update_at: 2026-10-05 08:35
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const ll EMPTY_LAZY = -1; // 区间覆盖懒标记的空标记（题目颜色均为非负整数）

ll n, m;
ll init_color[MAXN]; // init_color[i]：节点 i 的初始颜色

// 链式前向星存无向树
int head[MAXN], to[2 * MAXN], nxt_edge[2 * MAXN], edge_cnt;

// 树链剖分数组
int fa[MAXN];          // fa[u]：节点 u 的父亲
int dep[MAXN];         // dep[u]：节点 u 的深度（根深度为 1）
int sz[MAXN];          // sz[u]：以 u 为根的子树大小
int heavy_son[MAXN];   // heavy_son[u]：u 的重儿子，0 表示没有
int top_chain[MAXN];   // top_chain[u]：u 所在重链的链顶
int dfn[MAXN];         // dfn[u]：节点 u 在 dfs 序中的位置
int node_of_dfn[MAXN]; // node_of_dfn[i]：dfs 序第 i 位对应的节点
int dfn_cnt;

// 线段树维护 dfs 序上的连续颜色段
ll seg_cnt[4 * MAXN]; // seg_cnt[o]：区间 o 的颜色段数
ll seg_lc[4 * MAXN];  // seg_lc[o]：区间 o 左端点的颜色
ll seg_rc[4 * MAXN];  // seg_rc[o]：区间 o 右端点的颜色
ll lazy[4 * MAXN];    // lazy[o]：区间整体被覆盖成的颜色，EMPTY_LAZY 表示无标记

// 剖分过程中的辅助数组
int hld_order[MAXN];  // 迭代 dfs 得到、供父节点先于子节点处理的访问顺序
int hld_stack[MAXN];  // 第一遍迭代 dfs 用的栈
int chain_u[MAXN];    // 待处理的节点
int chain_top[MAXN];  // 与 chain_u 对应，待处理节点所在重链的链顶

// 查询结果暂存：区间颜色段数、左端点颜色、右端点颜色
ll res_cnt, res_lc, res_rc;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt_edge[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 以 1 为根做轻重链剖分；全程迭代实现，避免链状树递归过深。
void build_hld() {
    int order_cnt = 0;
    int stk_top = 0;

    fa[1] = 0;
    dep[1] = 1;
    hld_stack[++stk_top] = 1;
    while (stk_top > 0) {
        int u = hld_stack[stk_top--];
        hld_order[++order_cnt] = u;
        for (int i = head[u]; i != 0; i = nxt_edge[i]) {
            int v = to[i];
            if (v == fa[u]) continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            hld_stack[++stk_top] = v;
        }
    }

    // 逆序累加子树大小，同时选出重儿子
    for (int i = 1; i <= n; i++) sz[i] = 1;
    for (int i = order_cnt; i >= 1; i--) {
        int u = hld_order[i];
        int best = 0;
        for (int j = head[u]; j != 0; j = nxt_edge[j]) {
            int v = to[j];
            if (v == fa[u]) continue;
            sz[u] += sz[v];
            if (sz[v] > best) {
                best = sz[v];
                heavy_son[u] = v;
            }
        }
    }

    // 先走重儿子，保证同一条重链上的节点 dfs 序连续
    int chain_ptr = 0;
    chain_u[++chain_ptr] = 1;
    chain_top[chain_ptr] = 1;
    while (chain_ptr > 0) {
        int u = chain_u[chain_ptr];
        int t = chain_top[chain_ptr];
        chain_ptr--;
        dfn_cnt++;
        dfn[u] = dfn_cnt;
        node_of_dfn[dfn_cnt] = u;
        top_chain[u] = t;
        int h = heavy_son[u];
        for (int i = head[u]; i != 0; i = nxt_edge[i]) {
            int v = to[i];
            if (v == fa[u] || v == h) continue;
            chain_u[++chain_ptr] = v;
            chain_top[chain_ptr] = v;
        }
        if (h != 0) {
            chain_u[++chain_ptr] = h;
            chain_top[chain_ptr] = t;
        }
    }
}

// 用左右儿子的信息更新节点 o；交界处颜色相同则两段合并为一段。
void push_up(int o) {
    int lo = o << 1;
    int ro = lo | 1;
    if (seg_rc[lo] == seg_lc[ro]) {
        seg_cnt[o] = seg_cnt[lo] + seg_cnt[ro] - 1;
    } else {
        seg_cnt[o] = seg_cnt[lo] + seg_cnt[ro];
    }
    seg_lc[o] = seg_lc[lo];
    seg_rc[o] = seg_rc[ro];
}

// 把节点 o 的整个区间覆盖成颜色 c
void apply_cover(int o, ll c) {
    lazy[o] = c;
    seg_cnt[o] = 1;
    seg_lc[o] = c;
    seg_rc[o] = c;
}

void push_down(int o) {
    if (lazy[o] == EMPTY_LAZY) return;
    int lo = o << 1;
    int ro = lo | 1;
    apply_cover(lo, lazy[o]);
    apply_cover(ro, lazy[o]);
    lazy[o] = EMPTY_LAZY;
}

void build_seg(int o, ll l, ll r) {
    lazy[o] = EMPTY_LAZY; // 覆盖标记必须在建树时初始化为空，否则 0 会被当成真标记
    if (l == r) {
        ll c = init_color[node_of_dfn[l]];
        seg_cnt[o] = 1;
        seg_lc[o] = c;
        seg_rc[o] = c;
        return;
    }
    ll mid = (l + r) >> 1;
    int lo = o << 1;
    int ro = lo | 1;
    build_seg(lo, l, mid);
    build_seg(ro, mid + 1, r);
    push_up(o);
}

// 把区间 [ql, qr] 覆盖成颜色 c
void update_seg(int o, ll l, ll r, ll ql, ll qr, ll c) {
    if (ql <= l && r <= qr) {
        apply_cover(o, c);
        return;
    }
    push_down(o);
    ll mid = (l + r) >> 1;
    int lo = o << 1;
    int ro = lo | 1;
    if (ql <= mid) update_seg(lo, l, mid, ql, qr, c);
    if (qr > mid) update_seg(ro, mid + 1, r, ql, qr, c);
    push_up(o);
}

// 查询区间 [ql, qr] 的颜色段信息，结果写入 res_cnt / res_lc / res_rc
void query_seg(int o, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
        res_cnt = seg_cnt[o];
        res_lc = seg_lc[o];
        res_rc = seg_rc[o];
        return;
    }
    push_down(o);
    ll mid = (l + r) >> 1;
    if (qr <= mid) {
        query_seg(o << 1, l, mid, ql, qr);
        return;
    }
    if (ql > mid) {
        query_seg((o << 1) | 1, mid + 1, r, ql, qr);
        return;
    }
    // 区间跨过中点：查询左右两半后按交界颜色合并
    ll cnt_left, lc_left, rc_left;
    ll cnt_right, lc_right, rc_right;
    query_seg(o << 1, l, mid, ql, qr);
    cnt_left = res_cnt;
    lc_left = res_lc;
    rc_left = res_rc;
    query_seg((o << 1) | 1, mid + 1, r, ql, qr);
    cnt_right = res_cnt;
    lc_right = res_lc;
    rc_right = res_rc;
    if (rc_left == lc_right) {
        res_cnt = cnt_left + cnt_right - 1;
    } else {
        res_cnt = cnt_left + cnt_right;
    }
    res_lc = lc_left;
    res_rc = rc_right;
}

// 把树上 u 到 v 的路径整体覆盖成颜色 c
void tree_update(int u, int v, ll c) {
    while (top_chain[u] != top_chain[v]) {
        if (dep[top_chain[u]] < dep[top_chain[v]]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        update_seg(1, 1, n, dfn[top_chain[u]], dfn[u], c);
        u = fa[top_chain[u]];
    }
    if (dep[u] > dep[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    update_seg(1, 1, n, dfn[u], dfn[v], c);
}

// 询问树上 u 到 v 的路径颜色段数
ll tree_query(int u, int v) {
    ll ans = 0;
    // last_u / last_v 记录各自方向已跳过的链中最靠下（最靠近当前链）的颜色
    ll last_u = EMPTY_LAZY;
    ll last_v = EMPTY_LAZY;
    while (top_chain[u] != top_chain[v]) {
        if (dep[top_chain[u]] >= dep[top_chain[v]]) {
            query_seg(1, 1, n, dfn[top_chain[u]], dfn[u]);
            ans += res_cnt;
            if (res_rc == last_u) ans--; // 当前链底部与上一段链顶颜色相同，合并
            last_u = res_lc;
            u = fa[top_chain[u]];
        } else {
            query_seg(1, 1, n, dfn[top_chain[v]], dfn[v]);
            ans += res_cnt;
            if (res_rc == last_v) ans--;
            last_v = res_lc;
            v = fa[top_chain[v]];
        }
    }
    // 两点已在同一条重链上，最后查询一段区间并同时与两侧记录的端点颜色去重
    if (dep[u] >= dep[v]) {
        query_seg(1, 1, n, dfn[v], dfn[u]);
        ans += res_cnt;
        if (res_rc == last_u) ans--;
        if (res_lc == last_v) ans--;
    } else {
        query_seg(1, 1, n, dfn[u], dfn[v]);
        ans += res_cnt;
        if (res_lc == last_u) ans--;
        if (res_rc == last_v) ans--;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> init_color[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
        add_edge(y, x);
    }

    build_hld();
    build_seg(1, 1, n);

    for (int i = 1; i <= m; i++) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'C') {
            ll c;
            cin >> c;
            tree_update(a, b, c);
        } else {
            cout << tree_query(a, b) << '\n';
        }
    }

    return 0;
}
