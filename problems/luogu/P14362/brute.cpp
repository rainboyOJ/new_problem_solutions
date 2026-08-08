// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXK = 5;
const long long INF = (1LL << 62);

struct Edge {
    int u;
    int v;
    long long w;
};

int n, m, k;
long long city_cost[MAXK];
long long a[MAXK][MAXN];
vector<Edge> original_edges;

int fa[MAXN + MAXK], sz[MAXN + MAXK];

bool cmp_edge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

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

long long solve_mask(int mask) {
    vector<Edge> edges = original_edges;
    long long cost = 0;
    int selected_towns = 0;

    for (int j = 0; j < k; j++) {
        if ((mask & (1 << j)) == 0) {
            continue;
        }
        selected_towns++;
        cost += city_cost[j];
        for (int i = 1; i <= n; i++) {
            Edge e;
            e.u = i;
            e.v = n + j + 1;
            e.w = a[j][i];
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), cmp_edge);
    init_dsu(n + k);

    int need_edges = n + selected_towns - 1;
    int picked = 0;
    for (int i = 0; i < (int)edges.size() && picked < need_edges; i++) {
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
    original_edges.clear();
    for (int i = 1; i <= m; i++) {
        Edge e;
        cin >> e.u >> e.v >> e.w;
        original_edges.push_back(e);
    }

    for (int j = 0; j < k; j++) {
        cin >> city_cost[j];
        for (int i = 1; i <= n; i++) {
            cin >> a[j][i];
        }
    }

    long long ans = INF;
    for (int mask = 0; mask < (1 << k); mask++) {
        ans = min(ans, solve_mask(mask));
    }

    cout << ans << '\n';
    return 0;
}
