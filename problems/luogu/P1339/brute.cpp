// brute.cpp：Floyd 求任意两点最短路。
// 适合小数据对拍，也能直接帮助理解题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = (1LL << 60);

int n, m, s, t;
long long dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < dist_arr[u][v]) {
            dist_arr[u][v] = w;
            dist_arr[v][u] = w;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    cout << dist_arr[s][t] << '\n';

    return 0;
}
