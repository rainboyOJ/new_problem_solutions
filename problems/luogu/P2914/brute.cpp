#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long double INF = 1e100L;

int n, w;
long double limit_len;
long long x[MAXN], y[MAXN];
bool has_wire[MAXN][MAXN];
long double dist_arr[MAXN][MAXN];

long double get_dist(int i, int j) {
    long double dx = x[i] - x[j];
    long double dy = y[i] - y[j];
    return sqrtl(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    cin >> limit_len;

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

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

    for (int i = 1; i <= w; i++) {
        int u, v;
        cin >> u >> v;
        has_wire[u][v] = true;
        has_wire[v][u] = true;
        dist_arr[u][v] = 0;
        dist_arr[v][u] = 0;
    }

    // 暴力建图：所有距离不超过 M 的点对都可以补一条边。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (has_wire[i][j]) {
                continue;
            }
            long double d = get_dist(i, j);
            if (d <= limit_len + 1e-12L) {
                dist_arr[i][j] = d;
                dist_arr[j][i] = d;
            }
        }
    }

    // 小数据直接 Floyd。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist_arr[i][k] >= INF / 2) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (dist_arr[k][j] >= INF / 2) {
                    continue;
                }
                long double nd = dist_arr[i][k] + dist_arr[k][j];
                if (nd < dist_arr[i][j]) {
                    dist_arr[i][j] = nd;
                }
            }
        }
    }

    if (dist_arr[1][n] >= INF / 2) {
        cout << -1 << '\n';
    }
    else {
        cout << (long long) floor(dist_arr[1][n] * 1000.0L + 1e-9L) << '\n';
    }

    return 0;
}
