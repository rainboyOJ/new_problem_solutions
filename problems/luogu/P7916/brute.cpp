/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 21:03
 */
// brute.cpp：小网格暴力解，枚举每个格点染黑/白，直接计算割边代价。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
vector<BaseEdge> base_edges; // 网格内部的所有边

// 格点 (r,c) 的编号，从 0 开始
int node_id(int r, int c) {
    return (r - 1) * m + c - 1;
}

// 边界射线 p 对应的最近格点编号
// 边界顺序：上侧(1..m) -> 右侧(m+1..m+n) -> 下侧(m+n+1..m+2n) -> 左侧(m+2n+1..2m+2n)
int boundary_node(int p) {
    if (p <= m) {
        return node_id(1, p);           // 上侧
    }
    p -= m;
    if (p <= n) {
        return node_id(p, m);           // 右侧
    }
    p -= n;
    if (p <= m) {
        return node_id(n, m - p + 1);   // 下侧（逆序）
    }
    p -= m;
    return node_id(n - p + 1, 1);       // 左侧（逆序）
}

// 处理一次询问：枚举所有染色方案，计算最小跨色边代价
ll solve_query() {
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
    ll answer = (ll)4e18;
    for (int mask = 0; mask < (1 << total); mask++) {
        ll cost = 0;
        // 网格内部边的跨色代价
        for (int i = 0; i < (int)base_edges.size(); i++) {
            int cu = (mask >> base_edges[i].u) & 1;
            int cv = (mask >> base_edges[i].v) & 1;
            if (cu != cv) {
                cost += base_edges[i].w;
            }
        }
        // 附加点到格点的跨色代价
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

    // 读入水平边（相邻行之间）
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

    // 读入垂直边（相邻列之间）
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
