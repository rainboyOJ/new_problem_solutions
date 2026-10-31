#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 505;
const int MAXM = 500005;

struct LineInfo {
    int id;
    ll t;
};

int c, n, m, d, q;
ll w[MAXM];
vector<LineInfo> station_lines[MAXM];
ll dist[MAXN][MAXN];

int main() {
    // 优化标准输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> c >> n >> m >> d >> q)) return 0;

    for (int i = 1; i <= m; i++) {
        cin >> w[i];
    }

    // 初始化线路间最短距离矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int station;
            ll t;
            cin >> station >> t;
            station_lines[station].push_back({i, t});
        }
    }

    // 通过共用站点构建线路间的直接换乘边
    for (int v = 1; v <= m; v++) {
        const auto& lines = station_lines[v];
        int sz = lines.size();
        for (int i = 0; i < sz; i++) {
            int l1 = lines[i].id;
            ll t1 = lines[i].t;
            for (int j = i + 1; j < sz; j++) {
                int l2 = lines[j].id;
                ll t2 = lines[j].t;
                ll cost = t1 + t2;
                if (cost < dist[l1][l2]) {
                    dist[l1][l2] = cost;
                    dist[l2][l1] = cost;
                }
            }
        }
    }

    // Floyd-Warshall 算法预处理线路间全源最短路
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 处理每次出行询问
    for (int r = 0; r < q; r++) {
        int x, y;
        cin >> x >> y;
        ll min_cost = INF;
        for (const auto& lx : station_lines[x]) {
            for (const auto& ly : station_lines[y]) {
                ll cur = lx.t + dist[lx.id][ly.id] + ly.t;
                if (cur < min_cost) {
                    min_cost = cur;
                }
            }
        }
        cout << w[x] + min_cost + w[y] << "\n";
    }

    return 0;
}
