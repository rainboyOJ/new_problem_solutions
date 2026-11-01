/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 09:14
 * update_at: 2026-11-01 09:14
 */
// brute.cpp：小数据暴力 DP，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAX_MONEY = 205;

int n, m;
long long x[MAXN], y[MAXN]; // 小预算也允许输入很大的价格
int dp[MAX_MONEY], next_dp[MAX_MONEY]; // 精确花费对应的最大颗数，-1 为不可达

long long cost_of_count(int id, int cnt) {
    int pairs = cnt / 2;
    long long cost = pairs * (x[id] + y[id]);
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
        dp[j] = -1;
    }
    dp[0] = 0;

    // 逐种糖果枚举买几颗。m 很小时，每种糖果最多买 m 颗即可覆盖所有可能。
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            next_dp[j] = dp[j];
        }

        for (int money = 0; money <= m; money++) {
            if (dp[money] < 0) {
                continue;
            }
            for (int cnt = 1; cnt <= m; cnt++) {
                long long cost = cost_of_count(i, cnt);
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
