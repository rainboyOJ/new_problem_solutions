#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据直接在完整图上做 m 轮 DP，用来帮助理解和辅助对拍。

const int MOD = 998244353;

int n, m, k;
bool ban_edge[205][205];
int dp[205], ndp[205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            ban_edge[a][b] = true;
        }
    }

    dp[1] = 1;

    for (int step = 1; step <= m; step++) {
        for (int i = 1; i <= n; i++) {
            ndp[i] = 0;
        }

        for (int u = 1; u <= n; u++) {
            if (dp[u] == 0) {
                continue;
            }
            for (int v = 1; v <= n; v++) {
                if (u == v || ban_edge[u][v]) {
                    continue;
                }
                ndp[v] += dp[u];
                if (ndp[v] >= MOD) {
                    ndp[v] -= MOD;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            dp[i] = ndp[i];
        }
    }

    cout << dp[1] << '\n';
    return 0;
}
