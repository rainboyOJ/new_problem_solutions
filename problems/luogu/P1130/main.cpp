#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const long long INF = (1LL << 60);

int n, m;
int cost_days[MAXN][MAXN]; // cost_days[i][j]：第 i 组做第 j 步所需天数
long long dp[MAXN];        // 当前处理到某一步时，dp[i] 表示在第 i 组的最小代价
long long ndp[MAXN];

int prev_group(int x) {
    if (x == 1) {
        return m;
    }
    return x - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost_days[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        dp[i] = cost_days[i][1];
    }

    for (int step = 2; step <= n; step++) {
        for (int group = 1; group <= m; group++) {
            ndp[group] = min(dp[group], dp[prev_group(group)]) + cost_days[group][step];
        }
        for (int group = 1; group <= m; group++) {
            dp[group] = ndp[group];
        }
    }

    long long ans = INF;
    for (int i = 1; i <= m; i++) {
        ans = min(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
