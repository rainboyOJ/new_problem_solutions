#include <bits/stdc++.h>
using namespace std;

// brute.cpp：Floyd 求任意两点最大瓶颈路，只适合小数据对拍。

const int MAXN = 55;

int n, m, q;
int best[MAXN][MAXN]; // best[i][j] 表示 i 到 j 能达到的最大路径瓶颈值。

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            best[i][j] = -1;
        }
        best[i][i] = 1000000000;
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        best[u][v] = max(best[u][v], w);
        best[v][u] = max(best[v][u], w);
    }
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (best[i][k] == -1 || best[k][j] == -1) {
                    continue;
                }
                int value = min(best[i][k], best[k][j]);
                if (value > best[i][j]) {
                    best[i][j] = value;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    floyd();

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        cout << best[x][y] << '\n';
    }

    return 0;
}
