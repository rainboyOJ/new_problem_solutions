/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1000000000000000000LL;

int n, m;
ll a[20];                // 各宝石能量
int eu[130], ev[130];    // 边的两端
ll ew[130];              // 边的代价

// total[sub]：sub 内所有宝石能量之和
ll total[1 << 16];
// cost[sub]：把 sub 内部连成一棵树的最小代价，连不通为 INF
ll cost[1 << 16];
char ok[1 << 16];        // sub 能否独立调平
ll dp[1 << 16];          // 拆成若干可独立调平的块的最小总花费

struct Edge { int u, v; ll w; };
Edge edges[130];

bool edge_cmp(const Edge& x, const Edge& y) { return x.w < y.w; }

// 只允许 sub 内的点参与，求其 MST 代价
ll mst_weight(int sub) {
    int parent[16];
    int vertices = 0;
    for (int i = 0; i < n; i++) {
        if ((sub >> i) & 1) { parent[i] = i; vertices++; }
    }
    // 朴素 find
    int merged = 0;
    ll weight = 0;
    for (int ei = 0; ei < m; ei++) {
        int u = edges[ei].u, v = edges[ei].v;
        if (!((sub >> u) & 1) || !((sub >> v) & 1)) continue;
        int ru = u; while (parent[ru] != ru) { parent[ru] = parent[parent[ru]]; ru = parent[ru]; }
        int rv = v; while (parent[rv] != rv) { parent[rv] = parent[parent[rv]]; rv = parent[rv]; }
        if (ru == rv) continue;
        parent[ru] = rv;
        merged++;
        weight += edges[ei].w;
        if (merged == vertices - 1) return weight;
    }
    return (merged == vertices - 1) ? weight : INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        eu[i] = edges[i].u; ev[i] = edges[i].v; ew[i] = edges[i].w;
    }
    // 按代价升序（Kruskal）
    sort(edges, edges + m, edge_cmp);

    int full = (1 << n) - 1;

    // total 打表：去掉最低位再加回
    total[0] = 0;
    for (int sub = 1; sub <= full; sub++) {
        int low = sub & (-sub);
        int idx = __builtin_ctz(low);
        total[sub] = total[sub ^ low] + a[idx];
    }

    // cost 打表
    cost[0] = 0;
    for (int sub = 1; sub <= full; sub++) {
        if (total[sub] == 0) cost[sub] = mst_weight(sub);
        else cost[sub] = INF;
    }

    // ok 判定
    for (int sub = 1; sub <= full; sub++)
        ok[sub] = (total[sub] == 0 && cost[sub] < INF);

    // dp：只枚举含 sub 最低位的块
    dp[0] = 0;
    for (int sub = 1; sub <= full; sub++) {
        int low = sub & (-sub);
        int rest = sub ^ low;
        ll best = INF;
        int block = rest;
        while (true) {
            int cand = low | block;
            if (ok[cand] && dp[sub ^ cand] < INF) {
                ll v = dp[sub ^ cand] + cost[cand];
                if (v < best) best = v;
            }
            if (block == 0) break;
            block = (block - 1) & rest;
        }
        dp[sub] = best;
    }

    if (dp[full] < INF) cout << dp[full] << "\n";
    else cout << "Impossible\n";
    return 0;
}
