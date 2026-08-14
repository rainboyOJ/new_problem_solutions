/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 16:10
 */
// brute.cpp：小数据暴力解，按题意直接计算：
// 对每对 (u,v) 枚举所有点 x 找出满足 dis(u,x)+dis(v,x)=dis(u,v) 的集合，
// 再对每个 i 求集合中 dis(x,i) 的最小值并累加。用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n;
vector<int> g[MAXN];
int dist[MAXN][MAXN]; // dist[u][v]：u 到 v 的距离

// BFS 求从 start 出发到所有点的距离。
void bfs(int start) {
    queue<int> q;
    q.push(start);
    dist[start][start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[start][v] == -1) {
                dist[start][v] = dist[start][u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(dist, -1, sizeof(dist));
    for (int i = 1; i <= n; i++) bfs(i);

    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            for (int i = 1; i <= n; i++) {
                int best = INT_MAX;
                for (int x = 1; x <= n; x++) {
                    if (dist[u][x] + dist[v][x] == dist[u][v]) {
                        best = min(best, dist[x][i]);
                    }
                }
                ans += best;
            }
        }
    }
    cout << ans % (long long)(1e9 + 7) << '\n';

    return 0;
}
