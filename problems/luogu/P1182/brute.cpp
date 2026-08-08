// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = (1LL << 60);

int n, m;
long long a[MAXN], prefix_sum[MAXN];
long long dp[MAXN][MAXN];

long long range_sum(int l, int r) {
    return prefix_sum[r] - prefix_sum[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= m; k++) {
            for (int p = 0; p < i; p++) {
                if (dp[p][k - 1] == INF) {
                    continue;
                }
                dp[i][k] = min(dp[i][k], max(dp[p][k - 1], range_sum(p + 1, i)));
            }
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
