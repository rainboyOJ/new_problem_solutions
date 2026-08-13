/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-08-13 08:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

int n, m;
vector<pair<int, ll> > g[MAXN]; // 邻接表：(邻居, 边权)
ll distA[MAXN];                 // 各点到直径端点 A 的距离
ll distB[MAXN];                 // 各点到直径端点 B 的距离

// 从 start 出发 BFS 求最远点，并把距离写入 dist。
int bfs_farthest(int start, ll dist[]) {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        dist[i] = -1;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i].first;
            ll w = g[u][i].second;
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                q.push(v);
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
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }

    // 两次最远点搜索求直径端点 A、B。
    int A = bfs_farthest(1, distA);
    int B = bfs_farthest(A, distA);
    bfs_farthest(B, distB);

    // 对任意 C：时间 = dist(A,B) + min(dist(A,C), dist(B,C))，
    // 取 A、B 为直径端点时该值最大，答案 = 直径长 + max_C min(两个端点距离)。
    ll best_extra = 0;
    for (int i = 1; i <= n; i++) {
        ll mn = min(distA[i], distB[i]);
        if (mn > best_extra)
            best_extra = mn;
    }
    cout << distA[B] + best_extra << '\n';
    return 0;
}
