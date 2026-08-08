#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300 + 5;
const int INF = 1e9;

int n, m, t;
int dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t;

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
        int u, v, h;
        cin >> u >> v >> h;
        if (h < dist_arr[u][v]) {
            dist_arr[u][v] = h;
        }
    }

    // Floyd 的“最短路加法”改成“瓶颈路转移”：
    // 经过 k 的路径代价 = max(i->k 路上最大边, k->j 路上最大边)
    // 我们希望这个值尽量小，所以再对它取 min。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int through_k = max(dist_arr[i][k], dist_arr[k][j]);
                if (through_k < dist_arr[i][j]) {
                    dist_arr[i][j] = through_k;
                }
            }
        }
    }

    while (t--) {
        int a, b;
        cin >> a >> b;
        if (dist_arr[a][b] == INF) {
            cout << -1 << '\n';
        }
        else {
            cout << dist_arr[a][b] << '\n';
        }
    }

    return 0;
}
