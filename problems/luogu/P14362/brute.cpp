/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 23:04
 * update_at: 2026-10-01 23:04
 */
// brute.cpp：小数据暴力解，每个乡镇子集都用全部原图边重新跑一次 Kruskal。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20;   // 暴力只服务小数据，n、m 取到 20 左右
const int MAXK = 5;    // k 不能大，要枚举 2^k 个子集
const ll INF = 1LL << 62;

// 一条无向边：端点 u、v，费用 w。
struct Edge {
    int u;
    int v;
    ll w;
};

// 按边权升序，Kruskal 需要。
bool cmp_edge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

int n, m, k;
ll town_cost[MAXK];   // town_cost[j]：把第 j 个乡镇城市化的固定费用
ll town_a[MAXK][MAXN]; // town_a[j][i]：乡镇 j 到城市 i 建路的费用

vector<Edge> original_edges; // 原有城市之间的全部 m 条边

int fa[MAXN + MAXK];   // 并查集父亲
int sz[MAXN + MAXK];   // 并查集连通块大小

void init_dsu(int total) {
    for (int i = 1; i <= total; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}

int find_set(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

bool unite_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx == fy) {
        return false;
    }
    if (sz[fx] < sz[fy]) {
        swap(fx, fy);
    }
    fa[fy] = fx;
    sz[fx] += sz[fy];
    return true;
}

// 对固定的一组乡镇，直接把所有可用边倒出来跑 Kruskal。
ll solve_mask(int mask) {
    vector<Edge> edges = original_edges;
    ll cost = 0;
    int selected_towns = 0;

    for (int j = 0; j < k; j++) {
        if ((mask & (1 << j)) == 0) {
            continue;
        }
        selected_towns++;
        cost += town_cost[j];

        for (int i = 1; i <= n; i++) {
            Edge e;
            e.u = i;
            e.v = n + j + 1;
            e.w = town_a[j][i];
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), cmp_edge);
    init_dsu(n + k);

    // 生成树需要结点数减一条边。
    int need_edges = n + selected_towns - 1;
    int picked = 0;
    int cnt = edges.size();
    for (int i = 0; i < cnt && picked < need_edges; i++) {
        if (unite_set(edges[i].u, edges[i].v)) {
            cost += edges[i].w;
            picked++;
        }
    }

    if (picked < need_edges) {
        return INF;
    }
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 1; i <= m; i++) {
        Edge e;
        cin >> e.u >> e.v >> e.w;
        original_edges.push_back(e);
    }
    for (int j = 0; j < k; j++) {
        cin >> town_cost[j];
        for (int i = 1; i <= n; i++) {
            cin >> town_a[j][i];
        }
    }

    // 枚举所有乡镇子集，取最小费用。
    ll ans = INF;
    for (int mask = 0; mask < (1 << k); mask++) {
        ll current = solve_mask(mask);
        if (current < ans) {
            ans = current;
        }
    }

    cout << ans << '\n';
    return 0;
}
