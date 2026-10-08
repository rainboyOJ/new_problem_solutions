/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:45
 * update_at: 2026-10-07 22:45
 */
// 一本通 1762《与非》
//
// 题意：k 位 nand 运算 x nand y = ~(x & y)（结果只取低 k 位）。给一棵树，点权 w[i]，
//       Query x y：设 x 到 y 的路径依次是 S1..SL，f(0)=0，f(i) = f(i-1) nand w[Si]，
//       输出 f(L)。Replace x y：把 w[x] 改成 y。
//
// 做法：nand 逐位独立，一段序列诱导的函数 F 只需要 (F(0^k), F(1^k)) 两个掩码就能刻画，
//       而「函数复合」满足结合律，于是不可结合的 nand 序列被搬进可结合的复合世界：
//       线段树每个结点维护正/反两个方向的复合结果，树链剖分把路径拆成 O(log n) 段拼接。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned int u32;

const int MAXN = 100005;  // 结点数上限
const int MAXE = 200005;  // 无向边按两个方向各存一条，上限 2(n-1)

int n, m, k;
u32 MASK;       // 低 k 位全 1 的掩码
u32 wv[MAXN];  // 每个结点的点权（只保留低 k 位）

/* ---------- 链式前向星 ---------- */
int headArr[MAXN], eTo[MAXE], eNxt[MAXE], ecnt;

// 加一条 u -> v 的有向边。
void add_edge(int u, int v) {
    ecnt++;
    eTo[ecnt] = v;
    eNxt[ecnt] = headArr[u];
    headArr[u] = ecnt;
}

/* ---------- 树链剖分 ---------- */
int fa[MAXN], dep[MAXN], siz[MAXN], heavy_son[MAXN];  // 父亲 / 深度 / 子树大小 / 重儿子
int chain_top[MAXN], dfn[MAXN], node_of_dfn[MAXN];     // 链顶 / dfs 序 / 序对应的结点
int bfs_order[MAXN];                                   // 自根向下的 BFS 序，用来迭代剖分

// 求 x、y 的最近公共祖先（沿重链向上跳）。
int lca(int x, int y) {
    while (chain_top[x] != chain_top[y]) {
        if (dep[chain_top[x]] >= dep[chain_top[y]]) x = fa[chain_top[x]];
        else y = fa[chain_top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}

/* ---------- 区间变换 ---------- */
// 一段连续区间诱导的函数 F。因为 nand 逐位独立，F 的第 i 位只依赖 x 的第 i 位，
// 所以 F 由两个值唯一确定：a = F(0^k)、b = F(1^k)，且 F(x) = (x & b) | (~x & a)。
struct Trans {
    u32 a;  // F(0^k)
    u32 b;  // F(1^k)
};

Trans seg_fwd[MAXN << 2];  // 正向：按 dfn 递增（自顶向下）的顺序复合
Trans seg_bwd[MAXN << 2];  // 反向：按 dfn 递减（自底向上）的顺序复合

// 先做 before、后做 after 的复合结果，即 after ∘ before。
Trans merge_trans(Trans after, Trans before) {
    Trans res;
    res.a = ((before.a & after.b) | (~before.a & after.a)) & MASK;
    res.b = ((before.b & after.b) | (~before.b & after.a)) & MASK;
    return res;
}

// 单点权值 w 诱导的函数：F(x) = ~(x & w)（截断到低 k 位）。
Trans leaf_trans(u32 w) {
    Trans res;
    res.a = MASK;         // F(0) = ~(0 & w) = 全 1
    res.b = (~w) & MASK;  // F(1) = ~(1 & w) = ~w
    return res;
}

// 恒等函数 F(x) = x。
Trans ident_trans() {
    Trans res;
    res.a = 0;
    res.b = MASK;
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        seg_fwd[idx] = leaf_trans(wv[node_of_dfn[l]]);
        seg_bwd[idx] = seg_fwd[idx];
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid);
    build(idx << 1 | 1, mid + 1, r);
    seg_fwd[idx] = merge_trans(seg_fwd[idx << 1 | 1], seg_fwd[idx << 1]);
    seg_bwd[idx] = merge_trans(seg_bwd[idx << 1], seg_bwd[idx << 1 | 1]);
}

// 单点修改：把 dfn 位置 pos 的点权换成 w。
void update(int idx, int l, int r, int pos, u32 w) {
    if (l == r) {
        seg_fwd[idx] = leaf_trans(w);
        seg_bwd[idx] = seg_fwd[idx];
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(idx << 1, l, mid, pos, w);
    else update(idx << 1 | 1, mid + 1, r, pos, w);
    seg_fwd[idx] = merge_trans(seg_fwd[idx << 1 | 1], seg_fwd[idx << 1]);
    seg_bwd[idx] = merge_trans(seg_bwd[idx << 1], seg_bwd[idx << 1 | 1]);
}

// 正向查询 [ql, qr]：结果按 dfn 递增顺序复合（先 dfn 小的、后 dfn 大的）。
Trans query_fwd(int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg_fwd[idx];
    int mid = (l + r) >> 1;
    if (qr <= mid) return query_fwd(idx << 1, l, mid, ql, qr);
    if (ql > mid) return query_fwd(idx << 1 | 1, mid + 1, r, ql, qr);
    Trans left_part = query_fwd(idx << 1, l, mid, ql, qr);
    Trans right_part = query_fwd(idx << 1 | 1, mid + 1, r, ql, qr);
    return merge_trans(right_part, left_part);
}

// 反向查询 [ql, qr]：结果按 dfn 递减顺序复合（先 dfn 大的、后 dfn 小的）。
Trans query_bwd(int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg_bwd[idx];
    int mid = (l + r) >> 1;
    if (qr <= mid) return query_bwd(idx << 1, l, mid, ql, qr);
    if (ql > mid) return query_bwd(idx << 1 | 1, mid + 1, r, ql, qr);
    Trans left_part = query_bwd(idx << 1, l, mid, ql, qr);
    Trans right_part = query_bwd(idx << 1 | 1, mid + 1, r, ql, qr);
    return merge_trans(left_part, right_part);
}

/* ---------- 路径查询 ---------- */
// 路径 x -> y 上依次施加各点权诱导的函数，返回总复合结果。
// 拆成两半：x 侧（x 向上到 lca，路径上先走的部分）与 y 侧（lca 的孩子向下到 y，后走的部分）。
// 注意「先走的部分是内层函数、后走的部分是外层函数」，所以两半的拼接方向相反。
Trans query_path(int x, int y) {
    int l = lca(x, y);
    Trans fx = ident_trans();  // x 侧：自底向上（dfn 递减），新处理的链段在后、是外层
    Trans fy = ident_trans();  // y 侧：自顶向下（dfn 递增），新处理的链段在前、是内层

    while (chain_top[x] != chain_top[l]) {
        fx = merge_trans(query_bwd(1, 1, n, dfn[chain_top[x]], dfn[x]), fx);
        x = fa[chain_top[x]];
    }
    fx = merge_trans(query_bwd(1, 1, n, dfn[l], dfn[x]), fx);  // lca 属于 x 侧

    while (chain_top[y] != chain_top[l]) {
        fy = merge_trans(fy, query_fwd(1, 1, n, dfn[chain_top[y]], dfn[y]));
        y = fa[chain_top[y]];
    }
    if (y != l) fy = merge_trans(fy, query_fwd(1, 1, n, dfn[l] + 1, dfn[y]));

    return merge_trans(fy, fx);  // 先 x 侧、后 y 侧
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    MASK = (k >= 32) ? 0xFFFFFFFFu : ((1u << k) - 1u);

    for (int i = 1; i <= n; i++) cin >> wv[i];
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
        add_edge(b, a);
    }

    /* 迭代式树链剖分：n 可达 1e5 且数据含纯链，递归会爆栈 */
    int qt = 0;
    fa[1] = 0;
    dep[1] = 0;
    bfs_order[qt++] = 1;
    for (int qh = 0; qh < qt; qh++) {
        int u = bfs_order[qh];
        for (int e = headArr[u]; e; e = eNxt[e]) {
            int v = eTo[e];
            if (v == fa[u]) continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            bfs_order[qt++] = v;
        }
    }
    for (int i = n - 1; i >= 0; i--) {  // 逆 BFS 序保证儿子先于父亲算完
        int u = bfs_order[i];
        siz[u] = 1;
        heavy_son[u] = 0;
        for (int e = headArr[u]; e; e = eNxt[e]) {
            int v = eTo[e];
            if (v == fa[u]) continue;
            siz[u] += siz[v];
            if (heavy_son[u] == 0 || siz[v] > siz[heavy_son[u]]) heavy_son[u] = v;
        }
    }
    {
        int cur = 0;
        int stack_node[MAXN], stack_top[MAXN], sp = 0;
        stack_node[sp] = 1;
        stack_top[sp] = 1;
        sp++;
        while (sp > 0) {
            sp--;
            int u = stack_node[sp], t = stack_top[sp];
            for (int x = u; x != 0; x = heavy_son[x]) {  // 沿重链一路铺下去
                chain_top[x] = t;
                cur++;
                dfn[x] = cur;
                node_of_dfn[cur] = x;
                for (int e = headArr[x]; e; e = eNxt[e]) {
                    int v = eTo[e];
                    if (v != fa[x] && v != heavy_son[x]) {  // 轻儿子各自开一条新链
                        stack_node[sp] = v;
                        stack_top[sp] = v;
                        sp++;
                    }
                }
            }
        }
    }

    build(1, 1, n);

    char op[16];
    while (m--) {
        int x;
        cin >> op >> x;
        if (op[0] == 'Q') {  // Query x y：第二个参数是结点编号
            int y;
            cin >> y;
            cout << query_path(x, y).a << '\n';  // f(L) = 总函数在 0 处的取值
        } else {  // Replace x y：第二个参数是新的点权
            u32 y;
            cin >> y;
            wv[x] = y;
            update(1, 1, n, dfn[x], y);
        }
    }
    return 0;
}
