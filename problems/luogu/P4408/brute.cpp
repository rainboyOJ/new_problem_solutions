/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-08-13 08:02
 */
// brute.cpp：小数据暴力解，枚举所有三点组合 (C, A, B) 直接算最坏时间。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

int n, m;
vector<pair<int, ll> > g[MAXN]; // 邻接表：(邻居, 边权)

// 从 start 出发 BFS，返回 u 到 v 的距离。
ll bfs_dist(int start, int target) {
    queue<pair<int, ll> > q; // 队列元素：(节点, 距离)
    bool vis[MAXN] = {false};
    vis[start] = true;
    q.push(make_pair(start, 0));
    while (!q.empty()) {
        int u = q.front().first;
        ll d = q.front().second;
        q.pop();
        if (u == target)
            return d;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i].first;
            ll w = g[u][i].second;
            if (!vis[v]) {
                vis[v] = true;
                q.push(make_pair(v, d + w));
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
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }

    ll ans = 0;
    // 枚举 C、A、B 三个不同点，规则 1：先到距离近的点，再去远的点。
    for (int C = 1; C <= n; C++) {
        for (int A = 1; A <= n; A++) {
            if (A == C)
                continue;
            for (int B = 1; B <= n; B++) {
                if (B == C || B == A)
                    continue;
                ll dCA = bfs_dist(C, A);
                ll dCB = bfs_dist(C, B);
                ll dAB = bfs_dist(A, B);
                ll time = min(dCA, dCB) + dAB;
                if (time > ans)
                    ans = time;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
