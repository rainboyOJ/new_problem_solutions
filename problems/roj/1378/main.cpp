/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 16:38
 * update_at: 2026-10-08 16:46
 */
// 一本通 1378《最短路径(shopth)》：有向图含负边（无负环），求单源最短路。
// 有负边 ⇒ 用 Bellman-Ford，无负环时松弛 n-1 轮足够。
// 读入必须“按行”读矩阵：数据文件 SHOPTH8.IN 第 10 行少了 1 个 token，
// 按 token 连读会把后续所有行整体错位（顺便把最后一轮读空导致 stoll 崩溃）。
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

typedef long long ll;

const int MAXN = 85;    // n <= 80
const ll INF = 1e18;    // 无穷大：足够大，且与边权相加不会溢出

ll adj[MAXN][MAXN];     // adj[i][j] = 边 i->j 的权；INF 表示 i 到 j 无边
ll dist[MAXN];          // dist[i] = 源点到 i 的最短距离

void solve() {
    int n;
    if (!(cin >> n)) return;
    int source;
    cin >> source;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = INF;
        }
    }

    // 逐行读邻接矩阵：一行给出一行边权，'-' 表示无边。
    // 行内 token 少一个也只影响本行，不会污染后面的行。
    string line;
    getline(cin, line);                 // 吃掉源点那行剩下的换行
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        istringstream tokens(line);
        for (int j = 1; j <= n; j++) {
            string token;
            if (!(tokens >> token)) break;   // 本行 token 不足，剩下的列保持无边
            if (token != "-") {
                adj[i][j] = stoll(token);
            }
        }
    }

    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[source] = 0;

    // Bellman-Ford：每轮扫描所有边做一次松弛，最多 n-1 轮
    for (int round = 1; round < n; round++) {
        bool changed = false;           // 本轮没有任何距离变短就提前收敛
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (adj[i][j] == INF) continue;
                ll cand = dist[i] + adj[i][j];
                if (cand < dist[j]) {
                    dist[j] = cand;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    for (int i = 1; i <= n; i++) {
        if (i == source) continue;
        cout << "(" << source << " -> " << i << ") = " << dist[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
