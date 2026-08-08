// brute.cpp：用 Floyd 求任意两点最短路。
// 小数据下可以直接求出 i -> x 和 x -> i，再枚举最大往返距离。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = (1LL << 60);

int n, m, x;
long long dist_arr[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x;

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

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, dist_arr[i][x] + dist_arr[x][i]);
    }

    cout << answer << '\n';

    return 0;
}
