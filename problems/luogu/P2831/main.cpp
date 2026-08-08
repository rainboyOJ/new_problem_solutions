#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

int T;
int n, m_dummy;
double x[20], y[20];
int cover[20][20];
int dp[1 << 18];

bool equal_double(double a, double b) {
    return fabs(a - b) < EPS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m_dummy;
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        for (int i = 0; i < n; i++) {
            cover[i][i] = 1 << i;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                cover[i][j] = 0;
                if (equal_double(x[i], x[j])) {
                    continue;
                }

                double a = (y[i] / x[i] - y[j] / x[j]) / (x[i] - x[j]);
                if (a >= -EPS) {
                    continue;
                }
                double b = y[i] / x[i] - a * x[i];

                int mask = 0;
                for (int k = 0; k < n; k++) {
                    double yy = a * x[k] * x[k] + b * x[k];
                    if (equal_double(yy, y[k])) {
                        mask |= 1 << k;
                    }
                }
                cover[i][j] = mask;
            }
        }

        int full = 1 << n;
        for (int mask = 0; mask < full; mask++) {
            dp[mask] = n;
        }
        dp[0] = 0;

        for (int mask = 0; mask < full; mask++) {
            if (dp[mask] >= n) {
                continue;
            }
            int first = -1;
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    first = i;
                    break;
                }
            }
            if (first == -1) {
                continue;
            }

            dp[mask | (1 << first)] = min(dp[mask | (1 << first)], dp[mask] + 1);
            for (int j = 0; j < n; j++) {
                if (cover[first][j]) {
                    dp[mask | cover[first][j]] = min(dp[mask | cover[first][j]], dp[mask] + 1);
                }
            }
        }

        cout << dp[full - 1] << '\n';
    }
    return 0;
}
