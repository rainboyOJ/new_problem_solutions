#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const double INF = 1e100;

int n;
double x[MAXN], y[MAXN];
double dis0[MAXN];
double dis[MAXN][MAXN];
double dp[1 << 15][16];

double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= n; i++) {
        dis0[i] = dist(0, 0, x[i], y[i]);
        for (int j = 1; j <= n; j++) {
            dis[i][j] = dist(x[i], y[i], x[j], y[j]);
        }
    }

    int full = 1 << n;
    for (int mask = 0; mask < full; mask++) {
        for (int i = 1; i <= n; i++) {
            dp[mask][i] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[1 << (i - 1)][i] = dis0[i];
    }

    for (int mask = 0; mask < full; mask++) {
        for (int u = 1; u <= n; u++) {
            if (dp[mask][u] >= INF / 2) {
                continue;
            }
            for (int v = 1; v <= n; v++) {
                if (mask & (1 << (v - 1))) {
                    continue;
                }
                int nmask = mask | (1 << (v - 1));
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dis[u][v]);
            }
        }
    }

    double ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[full - 1][i]);
    }

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
    return 0;
}
