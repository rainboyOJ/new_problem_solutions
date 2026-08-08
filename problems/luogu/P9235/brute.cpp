// brute.cpp：直接做 maximin Floyd。
// dist[i][j] 表示 i 到 j 的所有路径里，“最小边权”的最大值。
// 复杂度高，只适合小数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m, q;
int dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist_arr[i][j] = 0;
        }
        dist_arr[i][i] = 1000000000;
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist_arr[u][v] = max(dist_arr[u][v], w);
        dist_arr[v][u] = max(dist_arr[v][u], w);
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist_arr[i][j] = max(dist_arr[i][j], min(dist_arr[i][k], dist_arr[k][j]));
            }
        }
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        if (dist_arr[x][y] == 0) {
            cout << -1 << '\n';
        } else {
            cout << dist_arr[x][y] << '\n';
        }
    }

    return 0;
}
