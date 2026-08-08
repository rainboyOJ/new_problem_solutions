// brute.cpp：Floyd 求任意两点最短路，再回答每个询问。
// 只适合小数据，但逻辑最直接。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const long long INF = (1LL << 60);

int n, m, b;
long long dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b;

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

    while (b--) {
        int p, q;
        cin >> p >> q;
        cout << dist_arr[p][1] + dist_arr[1][q] << '\n';
    }

    return 0;
}
