/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 20:00
 * update_at: 2026-10-21 20:00
 */
// main.cpp：[BJWC2010] 严格次小生成树。
// 先 Kruskal 求 MST，再枚举每条非树边 (u,v,w)：把它加入 MST 会与树上 u~v 路径成环，
// 换掉环上一条树边得到新生成树。为让增量 w-被删边 > 0 且最小，被删边应是路径上
// 「权值严格小于 w 的最大边」：
//   - w > 路径最大 m1 ：删 m1，候选 = sum - m1 + w
//   - w == m1        ：删 m1 增量为 0（不严格），退到严格次大 m2，候选 = sum - m2 + w
//   - w < m1 不可能发生（Kruskal 处理该非树边时，路径上的树边权都 <= w）
// 因此倍增 LCA 表要同时维护每段的 (最大, 严格次大) 边权，合并时严格排除等值重复边。
// 无解（所有非树边都不能严格替换）保持 INF；题面保证有解。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;   // 点数上限
const int maxe = 3e5 + 5;   // 边数上限
const int MAXLOG = 17;      // 2^17 > 1e5，够覆盖深度
const ll NEG = -1;          // 边权 >= 0，「不存在」的哨兵用 -1（不能用 0，权值可为 0）

int n, m;
ll mst_sum;                 // MST 总权值，可达 3e5*1e9，必须 long long

// ---------- 原图边表（按 Kruskal 顺序排序后使用） ----------
struct Edge {
    int u, v;
    ll w;
    bool in_mst;            // 是否被选进 MST
};
vector<Edge> edges;

// ---------- 并查集（Kruskal 用） ----------
int fa[maxn];               // fa[x]：并查集父指针，根的父是自己
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

// ---------- MST 上的链式前向星 ----------
struct ListEdge { int v; ll w; int nxt; }; // 边权与原图同为 ll；nxt 不与 std 冲突
ListEdge g[maxe * 2];       // 无向边双向存，大小翻倍
int head[maxn], edge_cnt;
void add_edge(int u, int v, ll w) {
    g[edge_cnt] = {v, w, head[u]};
    head[u] = edge_cnt++;
}

// ---------- 倍增表：同时维护路径 (最大, 严格次大) 边权 ----------
int dep[maxn];                          // 深度，根为 1
int up[maxn][MAXLOG + 1];               // up[u][j]：u 的第 2^j 级祖先
ll mx1[maxn][MAXLOG + 1];               // mx1[u][j]：u 向上 2^j 条边的最大权
ll mx2[maxn][MAXLOG + 1];               // mx2[u][j]：同段的严格次大权（< mx1），不存在为 NEG

// 合并两段最值信息 (a1,a2) 和 (b1,b2)，返回合并后的 (最大, 严格次大)
// 次大必须排除与最大等值的重复边，这是「严格」二字在数据结构层的落点
void merge_info(ll a1, ll a2, ll b1, ll b2, ll &r1, ll &r2) {
    r1 = max(a1, b1);
    r2 = NEG;
    // 严格次大 = 四个候选里「小于 r1 的最大者」
    ll cand[4] = {a1, a2, b1, b2};
    for (int i = 0; i < 4; ++i)
        if (cand[i] < r1) r2 = max(r2, cand[i]);
}

// DFS 预处理深度、父边信息（MST 是树，直接递归；深度 <= 1e5，64MB 栈足够）
void dfs(int u, int f, int w_from_fa) {
    dep[u] = dep[f] + 1;
    up[u][0] = f;
    mx1[u][0] = w_from_fa;
    mx2[u][0] = NEG;                     // 一条边没有次大
    for (int i = head[u]; i != -1; i = g[i].nxt) {
        if (g[i].v != f) dfs(g[i].v, u, g[i].w);
    }
}

void build_lca() {
    dfs(1, 0, NEG);                      // 根的父边哨兵
    for (int j = 1; j <= MAXLOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            int mid = up[i][j - 1];
            up[i][j] = up[mid][j - 1];
            merge_info(mx1[i][j - 1], mx2[i][j - 1],
                       mx1[mid][j - 1], mx2[mid][j - 1],
                       mx1[i][j], mx2[i][j]);
        }
    }
}

// 查询树上 u~v 路径的 (最大, 严格次大) 边权
void query_path(int u, int v, ll &r1, ll &r2) {
    r1 = r2 = NEG;
    if (dep[u] < dep[v]) swap(u, v);
    // u 跳到与 v 同层
    for (int j = MAXLOG; j >= 0; --j) {
        if (dep[u] - (1 << j) >= dep[v]) {
            merge_info(r1, r2, mx1[u][j], mx2[u][j], r1, r2);
            u = up[u][j];
        }
    }
    if (u == v) return;
    // 一起向上跳
    for (int j = MAXLOG; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            merge_info(r1, r2, mx1[u][j], mx2[u][j], r1, r2);
            merge_info(r1, r2, mx1[v][j], mx2[v][j], r1, r2);
            u = up[u][j];
            v = up[v][j];
        }
    }
    // 最后各补一条连向 LCA 的父边
    merge_info(r1, r2, mx1[u][0], mx2[u][0], r1, r2);
    merge_info(r1, r2, mx1[v][0], mx2[v][0], r1, r2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    if (n == 1) {                      // 单点无树边，严格次小生成树不存在
        cout << -1 << endl;
        return 0;
    }
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].in_mst = false;
    }

    // ---- 1. Kruskal 求 MST ----
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) { return a.w < b.w; });
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int picked = 0;
    mst_sum = 0;
    for (int i = 0; i < m && picked < n - 1; ++i) {
        Edge &e = edges[i];             // 自环两端同根，天然被跳过
        int ru = find(e.u), rv = find(e.v);
        if (ru == rv) continue;
        fa[ru] = rv;
        mst_sum += e.w;
        e.in_mst = true;               // 下标引用，写回 vector 元素
        ++picked;
    }

    // ---- 2. 用树边建链式前向星 ----
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
    for (const Edge &e : edges) {
        if (e.in_mst) {
            add_edge(e.u, e.v, e.w);
            add_edge(e.v, e.u, e.w);
        }
    }
    build_lca();

    // ---- 3. 枚举非树边，换边求最小严格增量 ----
    ll ans = LLONG_MAX;                  // 保持不变即为无解（题面保证有解）
    for (const Edge &e : edges) {
        if (e.in_mst || e.u == e.v) continue;
        ll m1, m2;
        query_path(e.u, e.v, m1, m2);
        if (e.w > m1) ans = min(ans, mst_sum - m1 + e.w);
        else if (e.w == m1 && m2 != NEG) // 换最大边增量 0，退到严格次大
            ans = min(ans, mst_sum - m2 + e.w);
    }

    if (ans == LLONG_MAX) ans = -1;      // 无解（题面保证不发生）
    cout << ans << endl;
    return 0;
}
