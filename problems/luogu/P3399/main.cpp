#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const long long INF = (1LL << 60);

int n, m;
long long d[MAXN];
long long c[MAXN];
long long dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> c[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }

    // 前 0 天走完 0 段路，疲劳值为 0。
    dp[0][0] = 0;

    for (int day = 1; day <= m; day++) {
        dp[0][day] = 0; // 还没出发时，可以一直休息。

        for (int city = 1; city <= n; city++) {
            // 选择 1：今天休息，不前进。
            dp[city][day] = min(dp[city][day], dp[city][day - 1]);

            // 选择 2：今天从 city-1 走到 city。
            if (dp[city - 1][day - 1] < INF / 2) {
                dp[city][day] = min(dp[city][day], dp[city - 1][day - 1] + d[city] * c[day]);
            }
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
