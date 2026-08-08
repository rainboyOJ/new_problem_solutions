// brute.cpp：小数据暴力 DP，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int INF = 1000000000;

int n, m;
int x[MAXN], y[MAXN];
int dp[205];

int cost_of_count(int id, int cnt) {
    int pairs = cnt / 2;
    int cost = pairs * (x[id] + y[id]);
    if (cnt % 2 == 1) {
        cost += x[id];
    }
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int j = 1; j <= m; j++) {
        dp[j] = -INF;
    }
    dp[0] = 0;

    // 逐种糖果枚举买几颗。m 很小时，每种糖果最多买 m 颗即可覆盖所有可能。
    for (int i = 1; i <= n; i++) {
        int next_dp[205];
        for (int j = 0; j <= m; j++) {
            next_dp[j] = dp[j];
        }

        for (int money = 0; money <= m; money++) {
            if (dp[money] < 0) {
                continue;
            }
            for (int cnt = 1; cnt <= m; cnt++) {
                int cost = cost_of_count(i, cnt);
                if (money + cost > m) {
                    break;
                }
                next_dp[money + cost] = max(next_dp[money + cost], dp[money] + cnt);
            }
        }

        for (int j = 0; j <= m; j++) {
            dp[j] = next_dp[j];
        }
    }

    int ans = 0;
    for (int j = 0; j <= m; j++) {
        ans = max(ans, dp[j]);
    }

    cout << ans << '\n';
    return 0;
}
