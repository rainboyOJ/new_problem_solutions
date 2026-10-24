/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:13
 * update_at: 2026-10-24 00:00
 */
// brute.cpp：小数据真实朴素暴力解
// 说明：为什么只适合小数据：需要显式枚举路径长度，长度上界一小才能跑。
// 本解法不依赖倍增性质，而是通过显式路径长度递推（reach[len][i][j] 表示从 i 到 j 是否存在长度恰为 len 的路径）。
// 在长度达到 LIMIT（这里取 64，覆盖 2^0, 2^1, ..., 2^6）后，检查所有 2^k 长度的点对，标记为 1 秒可达边。
// 最后在这些 1 秒边上做 BFS 求出 1 到 n 的最少秒数。
// 如果路径长度很大（如最优解需 2^31-1 步），显式枚举长度会直接 MLE/TLE，因此仅用于小规模数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65;
const int LIMIT = 64; // 显式枚举路径长度的上界
const int INF = 0x3f3f3f3f;

int n, m;
vector<int> adj[MAXN];

// reach[len][i][j]：从 i 到 j 是否存在一条长度恰好为 len 的有向路径
bool reach[LIMIT + 1][MAXN][MAXN];

// one_sec[i][j]：从 i 到 j 是否能用 1 秒（即恰好 2^k 步）直达
bool one_sec[MAXN][MAXN];

// dist[i]：从 1 到 i 的最少秒数
int dist_step[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        reach[1][u][v] = true;
    }

    // 显式逐层递推路径长度：len 从 2 到 LIMIT
    for (int len = 2; len <= LIMIT; ++len) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (!reach[len - 1][i][j]) continue;
                for (int nxt : adj[j]) {
                    reach[len][i][nxt] = true;
                }
            }
        }
    }

    // 检查所有恰好为 2^k (<= LIMIT) 的长度，构建 1 秒可达图
    for (int p2 = 1; p2 <= LIMIT; p2 <<= 1) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (reach[p2][i][j]) {
                    one_sec[i][j] = true;
                }
            }
        }
    }

    // 在 1 秒可达边上进行 BFS，求 1 到 n 的最少秒数
    memset(dist_step, 0x3f, sizeof(dist_step));
    queue<int> q;
    dist_step[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == n) break;

        for (int v = 1; v <= n; ++v) {
            if (one_sec[u][v] && dist_step[v] == INF) {
                dist_step[v] = dist_step[u] + 1;
                q.push(v);
            }
        }
    }

    cout << dist_step[n] << "\n";

    return 0;
}
