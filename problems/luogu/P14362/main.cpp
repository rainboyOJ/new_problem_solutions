#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXK = 10;
const long long INF = (1LL << 62);

struct Edge {
    int u;
    int v;
    long long w;
};

int n, m, k;
long long city_cost[MAXK];
long long subset_cost[1 << MAXK];
vector<Edge> original_edges;
vector<Edge> mst_edges;
vector<Edge> town_edges;

int fa[MAXN + MAXK], sz[MAXN + MAXK];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
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

void build_original_mst() {
    sort(original_edges.begin(), original_edges.end(), cmp_edge);
    init_dsu(n);

    for (int i = 0; i < (int)original_edges.size(); i++) {
        Edge e = original_edges[i];
        if (unite_set(e.u, e.v)) {
            mst_edges.push_back(e);
            if ((int)mst_edges.size() == n - 1) {
                break;
            }
        }
    }
}

void build_subset_cost() {
    int total_mask = 1 << k;
    subset_cost[0] = 0;
    for (int mask = 1; mask < total_mask; mask++) {
        int lowbit = mask & -mask;
        int id = 0;
        while ((1 << id) != lowbit) {
            id++;
        }
        subset_cost[mask] = subset_cost[mask ^ lowbit] + city_cost[id];
    }
}

bool edge_allowed_by_mask(const Edge &e, int mask) {
    int town_id = e.v - n - 1;
    return (mask & (1 << town_id)) != 0;
}

long long kruskal_with_towns(int mask) {
    int selected_towns = __builtin_popcount((unsigned)mask);
    int need_edges = n + selected_towns - 1;
    int picked = 0;
    long long cost = subset_cost[mask];

    init_dsu(n + k);

    int p1 = 0;
    int p2 = 0;
    while (picked < need_edges) {
        while (p2 < (int)town_edges.size() && !edge_allowed_by_mask(town_edges[p2], mask)) {
            p2++;
        }

        bool use_original = false;
        if (p1 < (int)mst_edges.size()) {
            if (p2 == (int)town_edges.size() || mst_edges[p1].w <= town_edges[p2].w) {
                use_original = true;
            }
        }

        Edge e;
        if (use_original) {
            e = mst_edges[p1];
            p1++;
        } else {
            if (p2 == (int)town_edges.size()) {
                return INF;
            }
            e = town_edges[p2];
            p2++;
        }

        if (unite_set(e.u, e.v)) {
            cost += e.w;
            picked++;
        }
    }

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    original_edges.reserve(m);
    town_edges.reserve(n * k);

    for (int i = 1; i <= m; i++) {
        Edge e;
        cin >> e.u >> e.v >> e.w;
        original_edges.push_back(e);
    }

    for (int j = 0; j < k; j++) {
        cin >> city_cost[j];
        for (int i = 1; i <= n; i++) {
            long long x;
            cin >> x;
            Edge e;
            e.u = i;
            e.v = n + j + 1;
            e.w = x;
            town_edges.push_back(e);
        }
    }

    build_original_mst();
    sort(town_edges.begin(), town_edges.end(), cmp_edge);
    build_subset_cost();

    long long ans = INF;
    int total_mask = 1 << k;
    for (int mask = 0; mask < total_mask; mask++) {
        ans = min(ans, kruskal_with_towns(mask));
    }

    cout << ans << '\n';
    return 0;
}
