/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-10-26 20:33
 */
// brute.cpp：小数据暴力解，枚举所有三点组合 (C, A, B)，按定义直接算最坏时间。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

struct Edge {
    int to; // 邻居节点
    ll w;   // 边权
};

int n, m;
vector<Edge> g[MAXN]; // 邻接表：g[u] 是节点 u 连出的所有边

// 从 start 出发 BFS，返回到 target 的距离（树连通，一定可达）。
// 图为树，路径唯一，首次到达即最短距离，因此不需要 Dijkstra。
ll bfs_dist(int start, int target) {
    ll dist[MAXN];
    for (int i = 1; i <= n; i++)
        dist[i] = -1; // 用 -1 当"未访问"标记：边权可以为 0
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target)
            return dist[u];
        for (auto &e : g[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + e.w;
                q.push(e.to);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    ll ans = 0;
    // 枚举家 C 与两个朋友 A、B，三者互不相同。
    // 规则 1：先到离 C 较近的朋友，再去另一个，所以时间 = min(d(C,A), d(C,B)) + d(A,B)。
    for (int C = 1; C <= n; C++) {
        for (int A = 1; A <= n; A++) {
            if (A == C)
                continue;
            for (int B = A + 1; B <= n; B++) {
                if (B == C)
                    continue;
                ll dCA = bfs_dist(C, A);
                ll dCB = bfs_dist(C, B);
                ll dAB = bfs_dist(A, B);
                ll cost = min(dCA, dCB) + dAB;
                if (cost > ans)
                    ans = cost;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
