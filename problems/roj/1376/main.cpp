/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:23
 * update_at: 2026-10-05 12:23
 */
// main.cpp：消息从哨所 1 并行扩散，求所有哨所都收到信的最短时间（单源最短路）。
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const ll INF = (1LL << 60);

int n, m;
ll g[MAXN][MAXN]; // g[u][v] 表示哨所 u 到哨所 v 的通信天数，INF 表示两地无直达线路
ll dist[MAXN];    // dist[v] 表示命令从指挥部（哨所 1）传到哨所 v 的最短天数
int done[MAXN];   // done[v] = 1 表示 v 的最短路已经确定

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            g[i][j] = INF;
        }
        g[i][i] = 0;
    }
    for (int e = 0; e < m; e++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if (w < g[u][v]) {
            // 线路是双向的，两个方向都要登记；重边取较小的天数
            g[u][v] = w;
            g[v][u] = w;
        }
    }

    // Dijkstra：n 很小，用邻接矩阵每次线性选出未确定点中 dist 最小的即可
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;
    for (int step = 1; step <= n; step++) {
        int u = 0;
        for (int v = 1; v <= n; v++) {
            if (!done[v] && (u == 0 || dist[v] < dist[u])) {
                u = v;
            }
        }
        if (u == 0 || dist[u] == INF) {
            // 剩下的哨所都无法从指挥部到达，提前结束
            break;
        }
        done[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
            }
        }
    }

    ll ans = 0; // 全部送达的时刻 = 最晚收到命令的哨所的时刻
    for (int v = 1; v <= n; v++) {
        if (dist[v] == INF) {
            cout << -1 << "\n";
            return 0;
        }
        if (dist[v] > ans) {
            ans = dist[v];
        }
    }
    cout << ans << "\n";
    return 0;
}
