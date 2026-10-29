/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 16:32
 * update_at: 2026-10-29 16:35
 */
// brute.cpp：朴素 O(n) 跳父亲法，用于理解题意和小数据验证。
// 正确维护边权（存放在 pair 里），每次查询从 a、b 分别往上跳到 LCA，取路径边权最大值。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 100010;

int n;
vector<pair<int,ll>> g[maxn]; // {to, weight}
ll edge_weight[maxn];         // 0-based edge index -> weight (for CHANGE)
pair<int,int> edge_end[maxn]; // 0-based edge index -> {u,v}

int fa[maxn], dep[maxn];

void dfs(int u, int father) {
    fa[u] = father;
    for (auto [v, w] : g[u]) {
        if (v == father) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

ll query_path_max(int u, int v) {
    ll ans = 0;
    // 先让 u、v 跳到同一深度
    while (dep[u] > dep[v]) {
        // 找到 u 的入边
        for (auto [p, w] : g[u]) {
            if (p == fa[u]) { ans = max(ans, w); break; }
        }
        u = fa[u];
    }
    while (dep[v] > dep[u]) {
        for (auto [p, w] : g[v]) {
            if (p == fa[v]) { ans = max(ans, w); break; }
        }
        v = fa[v];
    }
    while (u != v) {
        for (auto [p, w] : g[u]) {
            if (p == fa[u]) { ans = max(ans, w); break; }
        }
        u = fa[u];
        for (auto [p, w] : g[v]) {
            if (p == fa[v]) { ans = max(ans, w); break; }
        }
        v = fa[v];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        edge_weight[i] = w;
        edge_end[i] = {u, v};
    }

    dep[1] = 0;
    dfs(1, 0);

    string op;
    while (cin >> op) {
        if (op == "DONE") break;
        if (op == "CHANGE") {
            int x;
            ll t;
            cin >> x >> t;
            int eid = x - 1;
            // 暴力需要更新 g 里的权值
            auto [u, v] = edge_end[eid];
            // 找到并更新两条有向边
            for (auto &p : g[u]) if (p.first == v) p.second = t;
            for (auto &p : g[v]) if (p.first == u) p.second = t;
            edge_weight[eid] = t;
        } else if (op == "QUERY") {
            int x, y;
            cin >> x >> y;
            cout << query_path_max(x, y) << '\n';
        }
    }

    return 0;
}
