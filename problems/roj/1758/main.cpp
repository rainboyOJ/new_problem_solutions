/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:30
 * update_at: 2026-10-07 22:30
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* 一本通 1758《连通能力》
 * 每个点 i 的答案 = 以 i 为根的子树（i 的全部后代）的半径
 *              = min_{v 在子树 i 内} ( v 到子树内其它点的最大距离 )
 * 做法：树形 DP 求子树直径，再用“长链剖分 + 二分”在直径路径上找最优点。
 *   - 子树直径 D 只有两种来源：某个孩子的子树内部，或者经过 i 的两条最长臂之和。
 *   - 若 D 来自孩子 c，则答案就等于 ans[c]（直径两端都在 c 的子树里，
 *     而子树半径只会被直径两端决定）。
 *   - 否则直径端点就是 i 的两条最长臂端点，最优点落在 p1[i] 到 i 的这条链上；
 *     而 p1[i] 正是 i 所在长链的链底，于是“向上跳到中点”变成在长链上二分。
 * 复杂度 O(N log N)（二分是 std::lower_bound 的 O(log N)），数组全部 O(N)。
 */

const int MAXN = 1000005; /* N 上限 1e6，开 1e6+5 */

int n;

/* ---------- 链式前向星存树 ---------- */
int head[MAXN];          // head[u]：u 的第一条边
int nxt[2 * MAXN];       // 下一条边的编号
int to[2 * MAXN];        // 边的另一个端点
int wt[2 * MAXN];        // 边权
int ecnt;                // 已加入的边数（双向，2*(N-1) 条）

int fa[MAXN];            // fa[v]：以 1 为根时 v 的父亲，根的父亲为 0
int parw[MAXN];          // parw[v]：v 到父亲那条边的边权
int order[MAXN];         // BFS 序：父亲一定排在孩子前面，逆序即自底向上

ll dis[MAXN];            // dis[v]：v 到根 1 的距离

ll f1[MAXN];             // f1[v]：v 的子树内从 v 向下走的最长臂长
ll f2[MAXN];             // f2[v]：次长臂长（与最长臂来自不同孩子，无则为 0）
int hc[MAXN];            // hc[v]：最长臂所在的孩子（长链剖分的“重孩子”），叶子为 0

ll dia[MAXN];            // dia[v]：子树 v 的直径
ll ans[MAXN];            // ans[v]：子树 v 的半径 = 本题答案
int best_child[MAXN];    // 直径最大的孩子；为 0 表示直径的两条臂都在 v 身上（要重算）

/* ---------- 长链：把每条重链从上到下展开在 chain_dis 里 ---------- */
int pos[MAXN];           // pos[v]：v 在 chain_dis 中的下标
int chend[MAXN];         // chend[v]：v 所在长链的链底在 chain_dis 中的下标
ll chain_dis[MAXN];      // 同一条长链上 dis 严格递增，便于二分

/* ---------------- 快读 ---------------- */
static char ibuf[1 << 20];
static int ilen = 0, ipos = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return (unsigned char)ibuf[ipos++];
}

static inline int read_int() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    if (c == -1) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}

/* ---------------- 快写 ---------------- */
static char obuf[1 << 22];
static int olen = 0;

static inline void o_flush() {
    if (olen) { fwrite(obuf, 1, olen, stdout); olen = 0; }
}

static inline void o_putc(char c) {
    if (olen == (int)sizeof(obuf)) o_flush();
    obuf[olen++] = c;
}

static inline void o_putll(ll x) {
    char t[24];
    int k = 0;
    if (x == 0) t[k++] = '0';
    while (x > 0) { t[k++] = (char)('0' + (int)(x % 10)); x /= 10; }
    while (k > 0) o_putc(t[--k]);
}

static inline void add_edge(int u, int v, int w) {
    ++ecnt; to[ecnt] = v; wt[ecnt] = w; nxt[ecnt] = head[u]; head[u] = ecnt;
    ++ecnt; to[ecnt] = u; wt[ecnt] = w; nxt[ecnt] = head[v]; head[v] = ecnt;
}

/* 从根 1 出发 BFS 定根：得到 fa、parw、dis 和自底向上要用的 order */
void bfs_root() {
    int qt = 0;
    order[qt++] = 1;
    fa[1] = 0;
    parw[1] = 0;
    dis[1] = 0;
    for (int qh = 0; qh < qt; ++qh) {
        int u = order[qh];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == fa[u]) continue;   /* 树上无重边，跳过父亲即不回头 */
            fa[v] = u;
            parw[v] = wt[e];
            dis[v] = dis[u] + wt[e];
            order[qt++] = v;
        }
    }
}

/* 第一遍自底向上：把每个点的 f1、f2、hc 和直径信息推给父亲
 * （逆向 BFS 序保证处理 v 时它的所有孩子都已把信息推上来） */
void dp_diameter() {
    for (int idx = n - 1; idx >= 0; --idx) {
        int u = order[idx];
        ll through = f1[u] + f2[u];   /* 经过 u 的最长路径（= 两条最长臂之和） */
        if (through >= dia[u]) {
            dia[u] = through;         /* 直径经过 u 本身，要把最优中心重新算 */
            best_child[u] = 0;
        }
        if (u == 1) continue;
        int p = fa[u];
        ll val = f1[u] + parw[u];     /* u 这条臂延伸到 p 之后的长度 */
        if (val > f1[p]) {
            f2[p] = f1[p];
            f1[p] = val;
            hc[p] = u;                /* 最长臂来自 u，u 是 p 的重孩子 */
        } else if (val > f2[p]) {
            f2[p] = val;
        }
        if (dia[u] > dia[p]) {
            dia[p] = dia[u];          /* p 的直径可以由孩子 u 继承 */
            best_child[p] = u;
        }
    }
}

/* 长链剖分：每个点沿 hc 一路向下就是它的长链，链上 dis 单调递增 */
void build_chains() {
    int ptr = 0;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (u != 1 && hc[fa[u]] == u) continue;   /* 不是链顶，已经随链顶展开过 */
        for (int v = u; v != 0; v = hc[v]) {
            pos[v] = ptr;
            chain_dis[ptr] = dis[v];
            ++ptr;
        }
        int last = ptr - 1;
        for (int v = u; v != 0; v = hc[v]) chend[v] = last;
    }
}

/* 第二遍自底向上：算答案 */
void dp_answer() {
    for (int idx = n - 1; idx >= 0; --idx) {
        int u = order[idx];
        if (best_child[u] != 0) {
            ans[u] = ans[best_child[u]];   /* 直径整段落在孩子子树里，半径相同 */
            continue;
        }
        /* 直径端点是 p1[u]（长链链底）和 p2[u]，最优点在这条路径上，
         * 且在 p1[u] 到 u 这一段：找满足 2*d(p1,x) <= D 的最高点 x，
         * 答案取 x 与其父亲两个候选的较小值。
         * 注意 dis[p1[u]] = dis[u] + f1[u]。 */
        ll D = dia[u];
        ll t = 2 * (dis[u] + f1[u]) - D;   /* 判定条件等价于 2*dis[x] >= t */
        ll need = (t + 1) / 2;             /* ceil(t/2)，t 恒 >= 0 */
        int lo = pos[u];
        int hi = chend[u];
        int p = (int)(lower_bound(chain_dis + lo, chain_dis + hi + 1, need) - chain_dis);
        ll best = f2[u] + (chain_dis[p] - dis[u]);   /* max(d(x,p1), d(x,p2)) = d(x,p2) */
        if (p > lo) {
            ll alt = f1[u] - (chain_dis[p - 1] - dis[u]);   /* 上面一个点：max = d(p1,x') */
            if (alt < best) best = alt;
        }
        ans[u] = best;
    }
}

int main() {
    n = read_int();
    if (n <= 0) n = 1;
    for (int i = 1; i < n; ++i) {
        int u = read_int(), v = read_int(), w = read_int();
        add_edge(u, v, w);
    }

    bfs_root();
    dp_diameter();
    build_chains();
    dp_answer();

    for (int i = 1; i <= n; ++i) {
        o_putll(ans[i]);
        o_putc('\n');
    }
    o_flush();
    return 0;
}
