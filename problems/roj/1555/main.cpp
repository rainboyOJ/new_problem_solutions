/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:03
 * update_at: 2026-10-05 08:03
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXM = 300005;
const int LOGN = 18; // 2^17 > 1e5，满足倍增的最大跳跃需求
const ll INF = (1LL << 60);

struct Edge {
    int u;
    int v;
    int w; // 边权非负且不超过 1e9，用 int 存储；答案用 ll 累加
};
Edge edges[MAXM];    // 全部边，按边权升序排序后供 Kruskal 使用
Edge nonmst[MAXM];   // 不在最小生成树中的边，用于枚举替换
int non_cnt;

// 最小生成树的链式前向星：树上有 N-1 条边
int head[MAXN], to[2 * MAXN], nxt[2 * MAXN], edge_w[2 * MAXN], edge_cnt;

ll parent[MAXN]; // 并查集

// 倍增表：up[k][u] 为 u 的第 2^k 级祖先
// f1[k][u] / f2[k][u] 为 u 到该祖先路径上的最大边权与严格次大边权
int up[LOGN][MAXN];
int f1[LOGN][MAXN]; // 边权不超过 1e9，用 int 存储，-1 表示不存在
int f2[LOGN][MAXN];
int depth[MAXN];

int query_m1, query_m2; // 一次路径查询的结果：最大边权与严格次大边权

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

ll find_root(ll x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]]; // 路径折半压缩
        x = parent[x];
    }
    return x;
}

// 在最小生成树上加一条无向边。
void add_tree_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_w[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 合并两段路径的最大边权与严格次大边权，结果写回 m1 / m2。
void merge_max(int &m1, int &m2, int c1, int c2) {
    int cand[4];
    cand[0] = m1;
    cand[1] = m2;
    cand[2] = c1;
    cand[3] = c2;
    int best1 = -1;
    int best2 = -1;
    for (int i = 0; i < 4; i++) {
        int x = cand[i];
        if (x < 0) {
            continue;
        }
        if (x > best1) {
            best2 = best1;
            best1 = x;
        } else if (x < best1 && x > best2) {
            best2 = x; // 严格次大：重复的相等值被跳过
        }
    }
    m1 = best1;
    m2 = best2;
}

// 查询树上 u 到 v 路径上的最大边权与严格次大边权。
void query_path(int u, int v) {
    int m1 = -1;
    int m2 = -1;
    if (depth[u] < depth[v]) {
        int t = u;
        u = v;
        v = t;
    }

    // 先把 u 提升到和 v 同深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOGN; k++) {
        if ((diff >> k) & 1) {
            merge_max(m1, m2, f1[k][u], f2[k][u]);
            u = up[k][u];
        }
    }

    if (u != v) {
        // 两端一起向上跳到 LCA 的下一层
        for (int k = LOGN - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                merge_max(m1, m2, f1[k][u], f2[k][u]);
                merge_max(m1, m2, f1[k][v], f2[k][v]);
                u = up[k][u];
                v = up[k][v];
            }
        }
        // 最后补上到 LCA 的两条边
        merge_max(m1, m2, f1[0][u], f2[0][u]);
        merge_max(m1, m2, f1[0][v], f2[0][v]);
    }

    query_m1 = m1;
    query_m2 = m2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }
    sort(edges + 1, edges + m + 1, cmp_edge);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    memset(head, 0, sizeof(head));
    memset(f1, -1, sizeof(f1)); // -1 表示该位置没有边
    memset(f2, -1, sizeof(f2));

    // Kruskal 求最小生成树，同时收集所有非树边
    ll mst_weight = 0;
    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        ll ru = find_root(u);
        ll rv = find_root(v);
        if (ru != rv) {
            parent[ru] = rv;
            add_tree_edge(u, v, w);
            add_tree_edge(v, u, w);
            mst_weight += w;
        } else {
            non_cnt++;
            nonmst[non_cnt].u = u;
            nonmst[non_cnt].v = v;
            nonmst[non_cnt].w = w;
        }
    }

    // 以 1 号点为根 BFS，确定深度并填好倍增第 0 层
    int queue_node[MAXN];
    int qhead = 0;
    int qtail = 0;
    depth[1] = 1;
    queue_node[qtail] = 1;
    qtail++;
    while (qhead < qtail) {
        int u = queue_node[qhead];
        qhead++;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (depth[v] == 0) {
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                f1[0][v] = edge_w[i];
                queue_node[qtail] = v;
                qtail++;
            }
        }
    }

    // 自底向上构造倍增表
    for (int k = 0; k + 1 < LOGN; k++) {
        for (int v = 1; v <= n; v++) {
            int p = up[k][v];
            up[k + 1][v] = up[k][p];
            f1[k + 1][v] = f1[k][v];
            f2[k + 1][v] = f2[k][v];
            merge_max(f1[k + 1][v], f2[k + 1][v], f1[k][p], f2[k][p]);
        }
    }

    // 枚举每条非树边，用替换一条树边的最小正增量更新答案
    ll min_delta = INF;
    for (int i = 1; i <= non_cnt; i++) {
        int u = nonmst[i].u;
        int v = nonmst[i].v;
        int w = nonmst[i].w;
        query_path(u, v);
        if (w > query_m1) {
            ll delta = w - query_m1;
            if (delta < min_delta) {
                min_delta = delta;
            }
        } else if (query_m2 != -1 && w > query_m2) {
            ll delta = w - query_m2;
            if (delta < min_delta) {
                min_delta = delta;
            }
        }
    }

    printf("%lld\n", mst_weight + min_delta);

    return 0;
}
