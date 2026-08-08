#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const double INF = 1e100;

int n;
double limit_d;
double x[MAXN], y[MAXN];
double dis_mat[MAXN][MAXN];
double dp[1 << 20][20];

double dist(int i, int j) {
    double dx = x[i] - x[j];
    double dy = y[i] - y[j];
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit_d;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            double d = dist(i, j);
            if (d <= limit_d) {
                dis_mat[i][j] = d;
            } else {
                dis_mat[i][j] = INF;
            }
        }
        dis_mat[i][i] = 0.0;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis_mat[i][k] + dis_mat[k][j] < dis_mat[i][j]) {
                    dis_mat[i][j] = dis_mat[i][k] + dis_mat[k][j];
                }
            }
        }
    }

    int full = 1 << (n - 1);
    for (int mask = 0; mask < full; mask++) {
        for (int i = 1; i <= n; i++) {
            dp[mask][i] = INF;
        }
    }
    dp[0][1] = 0.0;

    for (int mask = 0; mask < full; mask++) {
        for (int u = 1; u <= n; u++) {
            if (dp[mask][u] >= INF / 2) {
                continue;
            }
            for (int v = 2; v <= n; v++) {
                if (mask & (1 << (v - 2))) {
                    continue;
                }
                if (dis_mat[u][v] >= INF / 2) {
                    continue;
                }
                int nmask = mask | (1 << (v - 2));
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dis_mat[u][v]);
            }
        }
    }

    double ans = INF;
    int all = full - 1;
    for (int u = 1; u <= n; u++) {
        if (dp[all][u] >= INF / 2 || dis_mat[u][1] >= INF / 2) {
            continue;
        }
        ans = min(ans, dp[all][u] + dis_mat[u][1]);
    }

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
    return 0;
}
