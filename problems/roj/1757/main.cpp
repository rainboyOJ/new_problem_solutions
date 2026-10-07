/**
 * 1757 避难向导
 *
 * 题意：给定一棵 n 个点的带权树（1 号点为首都）。只与一条公路相连的城市称为边境城市。
 *       每个城市的封闭系数 d_i = 离 i 最远的边境城市到 i 的距离；
 *       安全系数 S_i = (d_i + a) * b mod c。
 *       m 次询问 (x, y, q)：在 x 到 y 的必经之路（即树上唯一路径）上，找离 x 最近的
 *       且 S >= q 的城市编号（包含 x 和 y），不存在则输出 -1。
 *
 * 关键结论：
 *   1. 树中任意点的最远点一定是某条直径的端点；而 n >= 2 时直径端点必为叶子（度 1），
 *      也就是边境城市。因此 d_i = max(dist(i, A), dist(i, B))，A、B 为一条直径的两端。
 *      求直径只需从任意点做两遍 DFS：先求最远点 A，再从 A 求最远点 B。
 *   2. 询问等价于「在 x -> y 的路径序列上找第一个 S >= q 的位置」。
 *      用树链剖分把路径拆成 O(log n) 段连续区间，线段树上维护区间 S 的最大值；
 *      x -> lca 部分是自 x 向 lca 走，需要区间内「最靠右」的满足点；
 *      lca -> y 部分需要「最靠上」的满足点，倒序扫描各段即可。
 *
 * 复杂度：O((n + m) log^2 n) 时间，O(n) 空间。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;   // 城市数上限
const int MAXM = 300005;   // 询问数上限

int n, m;                  // 城市数、询问数
ll A, B, C;                // 幸运数字 a, b, c

struct Edge { int to; ll w; };
vector<Edge> g[MAXN];      // 邻接表

int par[MAXN];             // 父结点
int dep[MAXN];             // 深度（边数）
int sz[MAXN];              // 子树大小
int heavy[MAXN];           // 重儿子
int head[MAXN];            // 所在重链的链头
int pos[MAXN];             // 树链剖分后在线段树中的下标
int nodeAt[MAXN];          // 下标 -> 原编号
ll distRoot[MAXN];         // 到 1 号点的距离

ll S[MAXN];                // 安全系数
ll segMax[4 * MAXN];       // 线段树：区间 S 最大值

/** 从 root 出发做 BFS，得到 par / dep / distRoot / 访问顺序 order */
void bfsOrder(int root, int *order) {
    int qh = 0, qt = 0;
    static int que[MAXN];
    par[root] = 0; dep[root] = 0; distRoot[root] = 0;
    que[qt++] = root;
    while (qh < qt) {
        int u = que[qh++];
        order[qh - 1] = u;                       // 出队顺序即 BFS 序
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            if (v == par[u]) continue;
            par[v] = u;
            dep[v] = dep[u] + 1;
            distRoot[v] = distRoot[u] + g[u][i].w;
            que[qt++] = v;
        }
    }
}

/** 求距离 start 最远的结点编号（树的直径端点） */
int farthest(int start) {
    static int order[MAXN];
    bfsOrder(start, order);
    int best = start;
    for (int i = 1; i <= n; i++)
        if (distRoot[i] > distRoot[best]) best = i;
    return best;
}

/** 树链剖分：求 sz / heavy / head / pos / nodeAt */
void buildHLD() {
    static int order[MAXN];
    bfsOrder(1, order);

    // 逆 BFS 序统计子树大小与重儿子
    for (int i = 1; i <= n; i++) { sz[i] = 1; heavy[i] = 0; }
    for (int i = n - 1; i >= 1; i--) {          // order[0..n-1]，跳过根
        int u = order[i];
        sz[par[u]] += sz[u];
        if (heavy[par[u]] == 0 || sz[u] > sz[heavy[par[u]]]) heavy[par[u]] = u;
    }

    // 沿重链分配连续下标
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int u = order[i];
        if (u == 1 || heavy[par[u]] != u) {     // 链头
            for (int v = u; v != 0; v = heavy[v]) {
                head[v] = u;
                pos[v] = cur;
                nodeAt[cur] = v;
                cur++;
            }
        }
    }
}

void build(int node, int l, int r) {
    if (l == r) { segMax[node] = S[nodeAt[l]]; return; }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    segMax[node] = max(segMax[node << 1], segMax[node << 1 | 1]);
}

/** 区间 [l, r] 中最靠右（下标最大）的 S >= q 的位置，不存在返回 -1 */
int queryRight(int node, int nl, int nr, int l, int r, ll q) {
    if (r < nl || nr < l || segMax[node] < q) return -1;
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    int res = queryRight(node << 1 | 1, mid + 1, nr, l, r, q);   // 先右后左
    if (res != -1) return res;
    return queryRight(node << 1, nl, mid, l, r, q);
}

/** 区间 [l, r] 中最靠左（下标最小）的 S >= q 的位置，不存在返回 -1 */
int queryLeft(int node, int nl, int nr, int l, int r, ll q) {
    if (r < nl || nr < l || segMax[node] < q) return -1;
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    int res = queryLeft(node << 1, nl, mid, l, r, q);            // 先左后右
    if (res != -1) return res;
    return queryLeft(node << 1 | 1, mid + 1, nr, l, r, q);
}

int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (dep[head[u]] < dep[head[v]]) swap(u, v);
        u = par[head[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

/** 询问：x -> y 路径上离 x 最近的 S >= q 的城市编号 */
int solve(int x, int y, ll q) {
    int l = lca(x, y);
    int u = x;
    // 第一段：从 x 向上走到 l，越靠 x 下标越大，取最右
    while (head[u] != head[l]) {
        int r = queryRight(1, 0, n - 1, pos[head[u]], pos[u], q);
        if (r != -1) return nodeAt[r];
        u = par[head[u]];
    }
    int r1 = queryRight(1, 0, n - 1, pos[l], pos[u], q);
    if (r1 != -1) return nodeAt[r1];

    // 第二段：从 l 向下走到 y（不含 l），越靠 l 下标越小，需要最靠上的一段
    static int segs[64][2];
    int cnt = 0;
    int v = y;
    while (head[v] != head[l]) {
        segs[cnt][0] = pos[head[v]];
        segs[cnt][1] = pos[v];
        cnt++;
        v = par[head[v]];
    }
    if (pos[v] > pos[l]) {
        segs[cnt][0] = pos[l] + 1;
        segs[cnt][1] = pos[v];
        cnt++;
    }
    for (int i = cnt - 1; i >= 0; i--) {        // 倒序：先靠近 l 的段
        int r = queryLeft(1, 0, n - 1, segs[i][0], segs[i][1], q);
        if (r != -1) return nodeAt[r];
    }
    return -1;
}

int main() {
    scanf("%d %d %lld %lld %lld", &n, &m, &A, &B, &C);
    for (int i = 1; i < n; i++) {
        int u, v; ll w;
        scanf("%d %d %lld", &u, &v, &w);
        g[u].push_back((Edge){v, w});
        g[v].push_back((Edge){u, w});
    }

    // 1. 求直径两端 A、B，得到每个点的封闭系数
    static ll distA[MAXN];
    int p1 = farthest(1);
    int p2 = farthest(p1);
    for (int i = 1; i <= n; i++) distA[i] = distRoot[i];   // 距 p1
    farthest(p2);                                          // 现在 distRoot 为距 p2
    for (int i = 1; i <= n; i++) {
        ll d = max(distA[i], distRoot[i]);                 // n = 1 时两者均为 0
        S[i] = (d % C + A % C) % C * (B % C) % C;          // (d + a) * b mod c
    }

    // 2. 树链剖分 + 线段树
    buildHLD();
    build(1, 0, n - 1);

    // 3. 回答询问
    for (int i = 0; i < m; i++) {
        int x, y; ll q;
        scanf("%d %d %lld", &x, &y, &q);
        printf("%d\n", solve(x, y, q));
    }
    return 0;
}
