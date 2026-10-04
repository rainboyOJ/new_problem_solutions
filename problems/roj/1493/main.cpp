/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */

// 严格次小生成树
// 先用 Kruskal 求出一棵最小生成树 T、边权和 S；每加一条非树边 e=(u,v,w) 就形成一个环，
// 删掉环上一条边即可得到新生成树，权值为 S + w - w(f)。
// 要严格大于 S，就必须删掉环上严格小于 w 的最大边：路径最大边权 M < w 时删 M，
// M == w 时只能删严格次大值。于是对 MST 做倍增，维护树上每段路径的（最大边权，严格次大边权），
// 每条非树边用 O(log n) 查一次，所有候选取 min。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;  // 点数上限
const int MAXM = 300005;  // 边数上限
const int LOG = 17;       // 2^17 = 131072 > 1e5，覆盖任意两点的深度差与倍增跳跃
const ll NEG = -1;        // 哨兵：边权非负，-1 必小于任何真实边权，表示"这样的边不存在"

int n, m;

struct Edge {
    int u;
    int v;
    ll w;
};

Edge edges[MAXM];        // 全部边，排序后跑 Kruskal
Edge light_edges[MAXM];  // 落选的非树边，建好倍增表后逐条换边
int light_cnt;

int fa[MAXN];  // 并查集父节点

// 最小生成树的邻接表（链式前向星），最多 n-1 条边，所以开 2*MAXN
int head[MAXN];
int to[2 * MAXN];
int nxt[2 * MAXN];
ll edge_w[2 * MAXN];
int edge_cnt;

// 建倍增表用的树信息
int parent[MAXN];       // 每个点在 DFS 树上的父节点，0 表示还没访问
ll w_to_parent[MAXN];   // 每个点到父节点的边权
int depth[MAXN];        // 到根的边数
int stk[MAXN];          // 手写 DFS 栈，避免深度 1e5 时递归爆栈
int up[LOG][MAXN];      // up[k][v]：v 的 2^k 级祖先
ll mx[LOG][MAXN];       // mx[k][v]：v 向上跳 2^k 步这段路径上的最大边权
ll m2[LOG][MAXN];       // m2[k][v]：该段中严格小于 mx 的最大边权，NEG 表示不存在

// 一段树上路径的（最大边权，严格小于最大边权的次大边权）
struct Top2 {
    ll big;
    ll second;
};

Top2 make_top2(ll big, ll second) {
    Top2 t;
    t.big = big;
    t.second = second;
    return t;
}

// 合并两段首尾相接的路径：谁不是合并后的最大值，谁就有资格当次大候选；
// 本段最大值正好等于全局最大值时，只能用本段次大顶上。
Top2 merge_top2(Top2 a, Top2 b) {
    Top2 res;
    res.big = a.big > b.big ? a.big : b.big;
    ll cand_a = a.big < res.big ? a.big : a.second;
    ll cand_b = b.big < res.big ? b.big : b.second;
    res.second = cand_a > cand_b ? cand_a : cand_b;
    return res;
}

// 边按 (权值, 端点) 升序，用于 Kruskal
bool cmp_edge(const Edge &a, const Edge &b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

// 并查集查找，带路径压缩
int find_root(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

// 给 MST 加一条无向边，正反两个方向各存一次
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_w[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    edge_cnt++;
    to[edge_cnt] = u;
    edge_w[edge_cnt] = w;
    nxt[edge_cnt] = head[v];
    head[v] = edge_cnt;
}

// 以 1 号点为根迭代 DFS，求出每个点的父节点、到父节点的边权与深度
void dfs_build_root() {
    for (int v = 1; v <= n; v++) {
        parent[v] = 0;
    }
    int top = 0;
    stk[++top] = 1;
    parent[1] = 1;           // 根指向自己，方便倍增里祖先的比较
    w_to_parent[1] = NEG;    // 根没有到父节点的边
    depth[1] = 0;
    while (top > 0) {
        int u = stk[top--];
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (parent[v] == 0) {
                parent[v] = u;
                w_to_parent[v] = edge_w[e];
                depth[v] = depth[u] + 1;
                stk[++top] = v;
            }
        }
    }
}

// 建倍增表：第 k 层 = 从 v 跳 2^(k-1) 步到 mid，再接上 mid 跳 2^(k-1) 步的那一段
void build_lifting() {
    for (int v = 1; v <= n; v++) {
        up[0][v] = parent[v];
        mx[0][v] = w_to_parent[v];
        m2[0][v] = NEG;  // 只有一条边的段里没有第二条边可当次大
    }
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= n; v++) {
            int mid = up[k - 1][v];
            up[k][v] = up[k - 1][mid];
            Top2 t = merge_top2(make_top2(mx[k - 1][v], m2[k - 1][v]),
                                make_top2(mx[k - 1][mid], m2[k - 1][mid]));
            mx[k][v] = t.big;
            m2[k][v] = t.second;
        }
    }
}

// 查树上 u-v 路径的（最大边权，严格次大边权）：两侧分别爬升，边走边合并经过的段
Top2 path_top2(int u, int v) {
    Top2 side_u = make_top2(NEG, NEG);  // u 一侧已爬过的路径段
    Top2 side_v = make_top2(NEG, NEG);  // v 一侧已爬过的路径段
    int a = u;
    int b = v;
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    // 先把深的一侧抬到同一深度：深度差的二进制位决定每一级跳不跳
    int diff = depth[a] - depth[b];
    for (int k = 0; k < LOG; k++) {
        if ((diff >> k) & 1) {
            side_u = merge_top2(side_u, make_top2(mx[k][a], m2[k][a]));
            a = up[k][a];
        }
    }

    if (a != b) {
        // 还没相遇，从高倍增位往低试，祖先不同就两侧一起跳
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) {
                side_u = merge_top2(side_u, make_top2(mx[k][a], m2[k][a]));
                side_v = merge_top2(side_v, make_top2(mx[k][b], m2[k][b]));
                a = up[k][a];
                b = up[k][b];
            }
        }
        // 此时 a、b 的父节点就是 LCA，最后各爬一步把末段收进来
        side_u = merge_top2(side_u, make_top2(mx[0][a], m2[0][a]));
        side_v = merge_top2(side_v, make_top2(mx[0][b], m2[0][b]));
    }
    return merge_top2(side_u, side_v);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%lld", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    sort(edges + 1, edges + m + 1, cmp_edge);

    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    ll mst_sum = 0;  // 最小生成树的边权和 S
    light_cnt = 0;
    for (int i = 1; i <= m; i++) {
        int ru = find_root(edges[i].u);
        int rv = find_root(edges[i].v);
        if (ru != rv) {
            fa[ru] = rv;
            mst_sum += edges[i].w;
            add_edge(edges[i].u, edges[i].v, edges[i].w);
        } else {
            light_cnt++;
            light_edges[light_cnt] = edges[i];
        }
    }

    dfs_build_root();
    build_lifting();

    ll best = NEG;  // -1 表示还没找到严格更大的生成树
    for (int i = 1; i <= light_cnt; i++) {
        ll w = light_edges[i].w;
        Top2 t = path_top2(light_edges[i].u, light_edges[i].v);
        // MST 最优 ⇒ 路径最大边权必 ≤ w；要让总权严格变大，只能删路径上严格小于 w 的最大边
        ll cut = t.big < w ? t.big : t.second;
        if (cut < 0) continue;  // 整条路径的边都不小于 w，这条非树边换不出更大的权值和
        ll cand = mst_sum + w - cut;
        if (best < 0 || cand < best) best = cand;
    }
    printf("%lld\n", best);

    return 0;
}
