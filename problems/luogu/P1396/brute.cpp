/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 16:59
 * update_at: 2026-10-21 17:30
 */
// brute.cpp：小数据暴力解，按定义枚举 s 到 t 的所有简单路径，
// 每条路径取「路径上最大边权」，再在所有路径里取最小值。
// 与 main.cpp（Kruskal）、main2.cpp（瓶颈 Dijkstra）、
// main3.cpp（二分答案）三种做法完全不共享实现，适合用来独立验证。
// 路径数是指数级的，只在 n 很小时可用。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 12;  // 只枚举极小数据
const ll INF = (1LL << 60);

struct Edge {
    int to;
    ll w;
};

int n, m, start_node, target_node;
vector<Edge> g[MAXN];
bool in_path[MAXN];  // in_path[u]：u 是否已在当前路径上，用于避免重复经过
ll best;

// 当前在 u，已走部分的最大边权是 current_max
void dfs(int u, ll current_max) {
    if (current_max >= best) return;  // 剪枝：已经不比当前最优更好
    if (u == target_node) {
        best = current_max;  // 到达终点，这条路径的最大边权成为新的最优
        return;
    }
    for (const Edge &e : g[u]) {
        if (in_path[e.to]) continue;  // 只考虑简单路径，避免原地绕圈
        in_path[e.to] = true;
        dfs(e.to, max(current_max, e.w));
        in_path[e.to] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_node >> target_node;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    best = INF;
    in_path[start_node] = true;
    dfs(start_node, 0);

    cout << (best == INF ? 0 : best) << '\n';
    return 0;
}
