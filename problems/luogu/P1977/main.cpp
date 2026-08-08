#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 1000000000;

int n, k, d, s;
int t[MAXN], z[MAXN];
int dp[MAXN][MAXN]; // dp[i][j]：前 i 辆车已经送走 j 个人的最小花费

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> d >> s;
    for (int i = 1; i <= k; i++) {
        cin >> t[i] >> z[i];
    }

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i - 1][j] == INF) {
                continue;
            }

            // 这辆车一个人也不上。
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);

            // 这辆车上 x 个人。
            for (int x = 1; x <= z[i] && j + x <= n; x++) {
                int cost = dp[i - 1][j] + d + x * t[i];
                dp[i][j + x] = min(dp[i][j + x], cost);
            }
        }
    }

    cout << dp[k][n] << '\n';
    return 0;
}
