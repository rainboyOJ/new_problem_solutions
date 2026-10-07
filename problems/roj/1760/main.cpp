/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:55
 * update_at: 2026-10-07 23:45
 */
// ROJ 1760《树上数颜色》
//
// 题意：n 个点的树（根为 1），点 i 的颜色 c_i ∈ [1, n]，操作分两种：
//   1 u l r : 询问子树 u 中，颜色落在 [l, r] 的颜色种数；
//   2 u c   : 把点 u 的颜色改成 c；
//   t = 1 时，除操作类型外的每个数都要异或上一次询问的答案 lastans。
//
// 做法：DFS 序把「子树」变成「连续区间」，问题化为：区间内出现过的、
// 颜色落在 [l, r] 的颜色种数。
//   * 颜色只有 n 种，用「哪些颜色出现过」的 n 位位集表示一段区间；
//     两个位集的并 = 一次按位或，种数 = 位集与颜色区间掩码相与后的 popcount。
//   * 位置（DFS 序）每 BLK 个一块，块 b 的位集记作 M_b，用线段树维护 M_b 的并
//     （节点存两个儿子位集的或）。
//   * 询问 [L, R] x [l, r] = 头部残缺 + 中间若干完整块 + 尾部残缺：
//     完整块在 O(log nb) 次或运算内并成一个位集，两侧残缺部分逐位置把颜色或进去，
//     最后只在颜色区间 [l, r] 对应的字上做 popcount。
//   * 修改：只需重建它所在那一个位置块的位集（扫该块 BLK 个位置），再沿叶到根
//     重算 O(log nb) 个祖先。
// 复杂度：询问 O((r-l)/64 + log nb)，修改 O(BLK + log nb · n/64)；nb = n/BLK。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 100005;            // 点数上界
const int BLK = 1000;               // 位置（DFS 序）分块大小
const int MAXNB = MAXN / BLK + 2;   // 位置块数上界
const int MAXNW = MAXN / 64 + 2;    // 一个位集占的 64 位字数（颜色 1..n 共 n 位）
const int MAXP = 128;               // 线段树叶子偏移，2 的幂且 ≥ MAXNB

ull seg[2 * MAXP][MAXNW];           // 颜色位集线段树：叶在 seg[P..P+nb-1]
ull acc[MAXNW];                     // 询问时的临时并集，只用到颜色区间覆盖的那些字

int n, q, t;                        // 点数、操作数、是否强制在线
int nb, P, nw;                      // 位置块数、叶子偏移、位集字数

struct Edge { int to, next; };      // 边表（链式前向星）
Edge eg[2 * MAXN];
int head[MAXN];
int ecnt;

int color[MAXN];                    // 每个点当前的颜色
int par[MAXN];                      // DFS 中的父节点，用于判重
int tin[MAXN], tout[MAXN], euler[MAXN];  // 入时间、子树最大入时间、每个位置上的点

// ---------- 快读快写 ----------
static char rbuf[1 << 16];
static int rpos, rlen;

int gc() {
    if (rpos == rlen) {
        rlen = (int)fread(rbuf, 1, 1 << 16, stdin);
        rpos = 0;
        if (rlen <= 0) return -1;
    }
    return rbuf[rpos++];
}

int read_int() {
    int c = gc(), x = 0;
    while (c < '0' || c > '9') {
        if (c < 0) return -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = gc();
    }
    return x;
}

static char wbuf[1 << 21];
static int wpos;

void out_int(int x) {
    if (x == 0) {
        wbuf[wpos++] = '0';
        wbuf[wpos++] = '\n';
        return;
    }
    char tmp[12];
    int k = 0;
    while (x > 0) {
        tmp[k++] = '0' + x % 10;
        x /= 10;
    }
    while (k > 0) wbuf[wpos++] = tmp[--k];
    wbuf[wpos++] = '\n';
}

void add_edge(int u, int v) {
    ++ecnt;
    eg[ecnt].to = v;
    eg[ecnt].next = head[u];
    head[u] = ecnt;
}

// 迭代 DFS：n 最大 1e5，一条链会爆递归栈，所以显式开栈。
void build_dfs() {
    static int stk[MAXN];           // 栈里存点编号
    static int it[MAXN];            // 每个点待访问的下一条边
    int top = 0, timer = 0;
    par[1] = 0;
    stk[top++] = 1;
    tin[1] = ++timer;
    euler[timer] = 1;
    it[1] = head[1];
    while (top > 0) {
        int u = stk[top - 1];
        int e = it[u];
        if (e == 0) {               // 儿子都进过栈了，子树区间在此闭合
            tout[u] = timer;
            --top;
            continue;
        }
        it[u] = eg[e].next;
        int v = eg[e].to;
        if (v == par[u]) continue;  // 唯一的重复邻居就是父亲
        par[v] = u;
        tin[v] = ++timer;
        euler[timer] = v;
        it[v] = head[v];
        stk[top++] = v;
    }
}

// 重建位置块 b 的位集：扫它覆盖的 BLK 个位置
void build_leaf(int b) {
    ull *row = seg[P + b];
    memset(row, 0, (size_t)nw * sizeof(ull));
    int last = (b + 1) * BLK;
    if (last > n) last = n;
    for (int p = b * BLK + 1; p <= last; ++p) {
        int c = color[euler[p]];
        row[c >> 6] |= 1ULL << (c & 63);
    }
}

// 自叶向根重算祖先链
void repaint(int b) {
    for (int i = (P + b) >> 1; i; i >>= 1) {
        ull *cur = seg[i];
        const ull *a = seg[2 * i], *c = seg[2 * i + 1];
        for (int w = 0; w < nw; ++w) cur[w] = a[w] | c[w];
    }
}

void build_seg() {
    nb = (n + BLK - 1) / BLK;
    P = 1;
    while (P < nb) P <<= 1;
    nw = (n >> 6) + 1;
    for (int b = 0; b < nb; ++b) build_leaf(b);
    for (int i = P - 1; i >= 1; --i) {
        ull *cur = seg[i];
        const ull *a = seg[2 * i], *c = seg[2 * i + 1];
        for (int w = 0; w < nw; ++w) cur[w] = a[w] | c[w];
    }
}

void modify(int u, int cnew) {
    int old = color[u];
    if (old == cnew) return;
    color[u] = cnew;
    int b = (tin[u] - 1) / BLK;
    build_leaf(b);                  // 该块的位集可能整块都变了，直接重建
    repaint(b);
}

int query(int L, int R, int l, int r) {
    if (l < 1) l = 1;               // 强制在线解码可能越界，夹回 [1, n]
    if (r > n) r = n;
    if (L > R || l > r) return 0;
    int wl = l >> 6, wr = r >> 6;   // 只有这些字上的位才可能计入答案

    int fL = (L - 1 + BLK - 1) / BLK;   // 第一个完整落在 [L, R] 里的位置块
    int fR = R / BLK - 1;               // 最后一个完整落进来的位置块

    if (fL > fR) {                  // 没有完整块：整段落在相邻两个残缺块里
        memset(acc + wl, 0, (size_t)(wr - wl + 1) * sizeof(ull));
    } else {
        memset(acc + wl, 0, (size_t)(wr - wl + 1) * sizeof(ull));
        int i = fL + P, j = fR + P;      // 线段树把完整块并成一个位集
        while (i <= j) {
            if (i & 1) {
                const ull *a = seg[i];
                for (int w = wl; w <= wr; ++w) acc[w] |= a[w];
                ++i;
            }
            if (!(j & 1)) {
                const ull *a = seg[j];
                for (int w = wl; w <= wr; ++w) acc[w] |= a[w];
                --j;
            }
            i >>= 1;
            j >>= 1;
        }
    }
    // 头部残缺：第 fL-1 块的尾巴；尾部残缺：第 fR+1 块的脑袋
    for (int p = L; p <= fL * BLK && p <= R; ++p) {
        int c = color[euler[p]];
        if (c >= l && c <= r) acc[c >> 6] |= 1ULL << (c & 63);
    }
    for (int p = (fR + 1) * BLK + 1; p <= R; ++p) {
        if (p < L) p = L;
        int c = color[euler[p]];
        if (c >= l && c <= r) acc[c >> 6] |= 1ULL << (c & 63);
    }
    // 只在颜色区间 [l, r] 覆盖的字上数 1
    int ans = 0;
    if (wl == wr) {
        ull m = (~0ULL << (l & 63)) & (~0ULL >> (63 - (r & 63)));
        ans = __builtin_popcountll(acc[wl] & m);
    } else {
        ans = __builtin_popcountll(acc[wl] & (~0ULL << (l & 63)))
            + __builtin_popcountll(acc[wr] & (~0ULL >> (63 - (r & 63))));
        for (int w = wl + 1; w < wr; ++w) ans += __builtin_popcountll(acc[w]);
    }
    return ans;
}

int main() {
    n = read_int();
    q = read_int();
    t = read_int();
    for (int i = 1; i <= n; ++i) color[i] = read_int();
    for (int i = 1; i < n; ++i) {
        int u = read_int(), v = read_int();
        add_edge(u, v);
        add_edge(v, u);
    }
    build_dfs();
    build_seg();

    int lastans = 0;
    for (int i = 0; i < q; ++i) {
        int op = read_int();
        if (op == 1) {
            int u = read_int(), l = read_int(), r = read_int();
            if (t == 1) {
                u ^= lastans;
                l ^= lastans;
                r ^= lastans;
            }
            lastans = query(tin[u], tout[u], l, r);
            out_int(lastans);
        } else {
            int u = read_int(), c = read_int();
            if (t == 1) {
                u ^= lastans;
                c ^= lastans;
            }
            modify(u, c);
        }
    }
    fwrite(wbuf, 1, wpos, stdout);
    return 0;
}
