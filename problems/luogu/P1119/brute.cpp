// brute.cpp：对每个询问单独只保留当天已重建的点，再做一遍 Floyd。
// 只适合小数据，但最贴近题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = (1LL << 60);

struct Edge {
    int u, v, w;
};

int n, m;
int build_time[MAXN];
Edge edges[1005];
long long dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> build_time[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int q;
    cin >> q;
    while (q--) {
        int sx, sy, t;
        cin >> sx >> sy >> t;

        if (build_time[sx] > t || build_time[sy] > t) {
            cout << -1 << '\n';
            continue;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    dist_arr[i][j] = 0;
                }
                else {
                    dist_arr[i][j] = INF;
                }
            }
        }

        for (int i = 1; i <= m; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (build_time[u] <= t && build_time[v] <= t) {
                if (w < dist_arr[u][v]) {
                    dist_arr[u][v] = dist_arr[v][u] = w;
                }
            }
        }

        for (int k = 0; k < n; k++) {
            if (build_time[k] > t) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                        dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                    }
                }
            }
        }

        if (dist_arr[sx][sy] == INF) {
            cout << -1 << '\n';
        }
        else {
            cout << dist_arr[sx][sy] << '\n';
        }
    }

    return 0;
}
