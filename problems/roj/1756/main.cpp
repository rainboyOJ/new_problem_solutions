/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:55
 * update_at: 2026-10-07 21:55
 */
// 一本通 1756《过路费》
// 题意：无向连通图，n 个城市 m 条双向道路，边权 w 就是这段路要交的过路费。
//       一次 S->T 的总费用 = 路径上边权的最大值。每次询问求这个最大值的最小可能值。
// 算法：最小生成树就是最小瓶颈生成树 —— MST 上 u-v 路径的最大边权，等于全图所有
//       u-v 路径最大边权的最小值。于是询问全部化归为"树上路径最大边权"，
//       用倍增 LCA 在 O(log n) 内回答。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;   // 城市数上限 1e4
const int MAXM = 100005;  // 道路数上限 1e5
const int LOGN = 15;      // 2^14 = 16384 > n - 1，向上跳 2^k 步的层数够用
const int ROOT = 1;       // MST 以城市 1 为根；图保证连通，根取谁都不影响路径最大边权

struct Edge {  // 读入的一条道路
    int u;
    int v;
    ll w;      // 边权（过路费），最大 1e9
};
Edge edge[MAXM];

struct Link {  // MST 的链式前向星（MST 只有 n-1 条边，双向存 2n 个结点）
    int to;
    ll w;
    int nxt;
};
Link link[2 * MAXN];
int head[MAXN];   // head[u] 为城市 u 的第一条出边编号，0 表示没有
int link_cnt;

struct Jump {  // 倍增表的一项
    int anc;   // 向上跳 2^k 步到达的祖先
    ll mxw;    // 这 2^k 步路径上的最大边权
};
Jump jp[LOGN][MAXN];  // jp[k][v]：从城市 v 向上跳 2^k 步的信息

int dsu[MAXN];    // 并查集，Kruskal 用来判断两个城市是否已连通
char vis[MAXN];   // vis[v]：给 MST 定向时 v 是否已入树（只有 0/1，用 char 省内存）
int depth[MAXN];  // depth[v]：MST 上 v 到根的步数，根为 0
int n, m, q;

void add_link(int u, int v, ll w) {
    link_cnt++;
    link[link_cnt].to = v;
    link[link_cnt].w = w;
    link[link_cnt].nxt = head[u];
    head[u] = link_cnt;
}

// 并查集查根，带路径压缩
int find_root(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

// Kruskal 求最小生成树，结果建成链式前向星
void build_mst() {
    sort(edge + 1, edge + m + 1, cmp_edge);
    for (int i = 1; i <= n; i++) dsu[i] = i;
    for (int i = 1; i <= m; i++) {
        int ru = find_root(edge[i].u);
        int rv = find_root(edge[i].v);
        if (ru == rv) continue;  // 已成环（含自环），这条边不会出现在任何最小瓶颈路径上
        dsu[ru] = rv;
        add_link(edge[i].u, edge[i].v, edge[i].w);
        add_link(edge[i].v, edge[i].u, edge[i].w);
    }
}

// 以 ROOT 为根给 MST 定向，再逐层拼出倍增表
void build_jump() {
    for (int v = 1; v <= n; v++) {  // 未访问点也指向 ROOT，防止越界（题面保证连通）
        jp[0][v].anc = ROOT;
        jp[0][v].mxw = 0;
    }
    int stk[MAXN];  // 显式栈做迭代 DFS，链状数据不会爆递归栈
    int top = 0;
    stk[top++] = ROOT;
    vis[ROOT] = 1;
    while (top > 0) {
        int u = stk[--top];
        for (int e = head[u]; e != 0; e = link[e].nxt) {
            int v = link[e].to;
            if (vis[v]) continue;
            vis[v] = 1;
            depth[v] = depth[u] + 1;
            jp[0][v].anc = u;
            jp[0][v].mxw = link[e].w;
            stk[top++] = v;
        }
    }
    for (int k = 1; k < LOGN; k++) {
        for (int v = 1; v <= n; v++) {
            int mid = jp[k - 1][v].anc;  // 先跳 2^(k-1) 步落到的中点
            jp[k][v].anc = jp[k - 1][mid].anc;
            jp[k][v].mxw = max(jp[k - 1][v].mxw, jp[k - 1][mid].mxw);
        }
    }
}

// 求 S->T 在 MST 上的路径最大边权，即最少过路费
ll query_max(int s, int t) {
    if (s == t) return 0;  // 原地不动，不用交过路费
    ll ans = 0;
    int a = s, b = t;
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int k = 0; k < LOGN; k++) {  // 先把 a 抬到与 b 同深度
        if (diff >> k & 1) {
            ans = max(ans, jp[k][a].mxw);
            a = jp[k][a].anc;
        }
    }
    if (a == b) return ans;           // b 就是 a 的祖先，LCA 已找到
    for (int k = LOGN - 1; k >= 0; k--) {  // 一起往上跳，停在 LCA 的下一层
        if (jp[k][a].anc != jp[k][b].anc) {
            ans = max(ans, jp[k][a].mxw);
            ans = max(ans, jp[k][b].mxw);
            a = jp[k][a].anc;
            b = jp[k][b].anc;
        }
    }
    ans = max(ans, jp[0][a].mxw);  // 再各走一步到 LCA
    ans = max(ans, jp[0][b].mxw);
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        edge[i].u = u;
        edge[i].v = v;
        edge[i].w = w;
    }
    build_mst();
    build_jump();
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld\n", query_max(s, t));
    }
    return 0;
}
