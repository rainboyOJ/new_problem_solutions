/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:13
 * update_at: 2026-10-23 23:13
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 65;
const int MAXK = 65;
const int INF = 0x3f3f3f3f;

ll n, m;
// f[k][i][j] 表示从点 i 到点 j 是否存在一条长度恰好为 2^k 的路径
bool f[MAXK][MAXN][MAXN];
// dis[i][j] 表示从 i 到 j 的最少秒数
int dis[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    memset(dis, 0x3f, sizeof(dis));

    for (int i = 1; i <= n; ++i) {
        dis[i][i] = 0;
    }

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        f[0][u][v] = true;
        dis[u][v] = 1; // 距离为 2^0 = 1 千米，耗时 1 秒
    }

    // 倍增：f[k][i][j] = exists p, f[k-1][i][p] && f[k-1][p][j]
    // 最多 64 次方足以覆盖 2^64（远大于 2^31-1 和 n <= 50 时的实际需要）
    for (int k = 1; k <= 64; ++k) {
        for (int p = 1; p <= n; ++p) {
            for (int i = 1; i <= n; ++i) {
                if (!f[k - 1][i][p]) continue;
                for (int j = 1; j <= n; ++j) {
                    if (f[k - 1][p][j]) {
                        f[k][i][j] = true;
                        dis[i][j] = 1; // 存在一条长为 2^k 的路径，耗时 1 秒
                    }
                }
            }
        }
    }

    // 在新图上跑 Floyd 求 1 到 n 的最短路
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }

    cout << dis[1][n] << "\n";

    return 0;
}
