/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:49
 * update_at: 2026-10-08 01:49
 */
// 1775《梦中漫步》：树上随机游走的期望步数（树形 DP + 倍增 LCA）
//   以 1 为根，f[x] 表示从 x 出发首次走到父亲的期望步数，
//   g[x] 表示从父亲出发首次走到 x 的期望步数。
//   设 d[x] 为 x 的度数，son(x) 为 x 的儿子集合，由马尔可夫方程消元得
//     f[x] = d[x] + Σ_{c∈son(x)} f[c]        （即子树内所有点的度数之和）
//     g[c] = g[x] + f[x] - f[c]              （x 是 c 的父亲）
//   两者都是整数，配合树上前缀和 + LCA 即可 O(1) 回答每个询问：
//     ans(u, v) = (pf[u] - pf[z]) + (pg[v] - pg[z]),  z = LCA(u, v)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007;   // 答案取模
const int MAXN = 100005;     // 点数上限
const int LOG = 18;          // 倍增层数：2^17 = 131072 > 1e5

struct Node {
    int fa;    // 父亲编号，根节点 1 的父亲记为虚点 0
    int dep;   // 深度，根的深度为 0
    ll deg;    // 度数
    ll f;      // f[x]：从 x 出发首次走到父亲的期望步数
    ll g;      // g[x]：从父亲出发首次走到 x 的期望步数
    ll pf;     // 根到 x 路径上所有 f 之和（不含根的 f）
    ll pg;     // 根到 x 路径上所有 g 之和（不含根的 g）
};
Node nd[MAXN];               // nd[x] 就是节点 x 的全部属性

int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], ecnt;  // 链式前向星
int order[MAXN];             // BFS 序，order[1..n]；父亲一定排在儿子前面
int up[MAXN][LOG];           // 倍增表：up[x][j] 是 x 的 2^j 级祖先（0 表示不存在）

// 加一条有向边 u -> v
void add_edge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

// 以 1 为根做 BFS，求出每个点的父亲、深度，以及自顶向下的遍历序
void build_tree(int n) {
    int qh = 1, qt = 1;
    order[qt] = 1;
    nd[1].fa = 0;
    nd[1].dep = 0;
    while (qh <= qt) {
        int x = order[qh++];
        for (int e = head[x]; e; e = nxt[e]) {
            int y = to[e];
            if (y == nd[x].fa) continue;   // 只有父亲是"已访问"的邻居，跳过即可
            nd[y].fa = x;
            nd[y].dep = nd[x].dep + 1;
            order[++qt] = y;
        }
    }
}

// 自底向上求 f[x] = deg[x] + Σ f[儿子]
void calc_f(int n) {
    for (int x = 1; x <= n; x++) nd[x].f = nd[x].deg;
    for (int i = n; i >= 2; i--) {
        int x = order[i];
        nd[nd[x].fa].f += nd[x].f;
    }
}

// 自顶向下求 g[x] 与两条前缀和 pf / pg
void calc_g(int n) {
    nd[1].g = 0;
    nd[1].pf = 0;
    nd[1].pg = 0;
    for (int i = 2; i <= n; i++) {
        int x = order[i], p = nd[x].fa;
        nd[x].g = nd[p].g + nd[p].f - nd[x].f;
        nd[x].pf = nd[p].pf + nd[x].f;
        nd[x].pg = nd[p].pg + nd[x].g;
    }
}

// 倍增表预处理
void build_up(int n) {
    for (int x = 1; x <= n; x++) up[x][0] = nd[x].fa;
    for (int j = 1; j < LOG; j++)
        for (int x = 1; x <= n; x++)
            up[x][j] = up[up[x][j - 1]][j - 1];
}

// 求 u、v 的最近公共祖先
int lca(int u, int v) {
    if (nd[u].dep < nd[v].dep) { int t = u; u = v; v = t; }
    int diff = nd[u].dep - nd[v].dep;
    for (int j = 0; j < LOG; j++)
        if (diff >> j & 1) u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--)
        if (up[u][j] != up[v][j]) { u = up[u][j]; v = up[v][j]; }
    return up[u][0];
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        nd[u].deg++;
        nd[v].deg++;
    }

    build_tree(n);
    calc_f(n);
    calc_g(n);
    build_up(n);

    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        int z = lca(u, v);
        // u 向上走到 z，再向下走到 v；两段期望步数直接相加
        ll ans = (nd[u].pf - nd[z].pf + nd[v].pg - nd[z].pg) % MOD;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
