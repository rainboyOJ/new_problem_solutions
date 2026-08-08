// brute.cpp：小网格暴力解，枚举每个格点染黑/白，直接计算割边代价。
#include <bits/stdc++.h>
using namespace std;

struct BaseEdge {
    int u;
    int v;
    int w;
};

struct ExtraEdge {
    int u;
    int w;
    int color;
};

int n, m, T;
vector<BaseEdge> base_edges;

int node_id(int r, int c) {
    return (r - 1) * m + c - 1;
}

int boundary_node(int p) {
    if (p <= m) {
        return node_id(1, p);
    }
    p -= m;
    if (p <= n) {
        return node_id(p, m);
    }
    p -= n;
    if (p <= m) {
        return node_id(n, m - p + 1);
    }
    p -= m;
    return node_id(n - p + 1, 1);
}

long long solve_query() {
    int k;
    cin >> k;
    vector<ExtraEdge> extra_edges;
    for (int i = 1; i <= k; i++) {
        int x, p, color;
        cin >> x >> p >> color;
        ExtraEdge e;
        e.u = boundary_node(p);
        e.w = x;
        e.color = color;
        extra_edges.push_back(e);
    }

    int total = n * m;
    long long answer = (long long)4e18;
    for (int mask = 0; mask < (1 << total); mask++) {
        long long cost = 0;
        for (int i = 0; i < (int)base_edges.size(); i++) {
            int cu = (mask >> base_edges[i].u) & 1;
            int cv = (mask >> base_edges[i].v) & 1;
            if (cu != cv) {
                cost += base_edges[i].w;
            }
        }
        for (int i = 0; i < (int)extra_edges.size(); i++) {
            int cu = (mask >> extra_edges[i].u) & 1;
            if (cu != extra_edges[i].color) {
                cost += extra_edges[i].w;
            }
        }
        answer = min(answer, cost);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> T;
    for (int r = 1; r < n; r++) {
        for (int c = 1; c <= m; c++) {
            int w;
            cin >> w;
            BaseEdge e;
            e.u = node_id(r, c);
            e.v = node_id(r + 1, c);
            e.w = w;
            base_edges.push_back(e);
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c < m; c++) {
            int w;
            cin >> w;
            BaseEdge e;
            e.u = node_id(r, c);
            e.v = node_id(r, c + 1);
            e.w = w;
            base_edges.push_back(e);
        }
    }

    while (T--) {
        cout << solve_query() << '\n';
    }

    return 0;
}
