/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-10-26 20:33
 */
// main.cpp：三次 BFS 求直径端点与两端距离数组，再 O(n) 扫描答案。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

struct Edge {
    int to; // 邻居节点
    ll w;   // 边权
};

int n, m;
vector<Edge> g[MAXN]; // 邻接表：g[u] 是节点 u 连出的所有边
ll distA[MAXN];       // 各点到直径端点 A 的距离
ll distB[MAXN];       // 各点到直径端点 B 的距离

// 从 start 出发 BFS，把到各点的距离写入 dist，返回距离最远的节点编号。
// 因为是树, 所以用 BFS 求路径长度即可（路径唯一，不需要 Dijkstra）。
int bfs_farthest(int start, ll dist[]) {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        dist[i] = -1; // 用 -1 当"未访问"标记：边权可以为 0，不能用 0 标记
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &e : g[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + e.w;
                q.push(e.to);
            }
        }
    }
    int far = start;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[far])
            far = i;
    }
    return far;
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

    // 两次最远点搜索求出一对直径端点 A、B。
    int A = bfs_farthest(1, distA);
    int B = bfs_farthest(A, distA); // 这次的距离以 A 为源，正好是 distA[]
    bfs_farthest(B, distB);

    // 答案是「直径长 + 到两端较近距离的最大值」。
    // 注意直径端点这一对朋友只保证全局最优，对每个固定的家未必最优。
    ll best_extra = 0;
    for (int i = 1; i <= n; i++) {
        ll mn = min(distA[i], distB[i]);
        if (mn > best_extra)
            best_extra = mn;
    }
    cout << distA[B] + best_extra << '\n';
    return 0;
}
