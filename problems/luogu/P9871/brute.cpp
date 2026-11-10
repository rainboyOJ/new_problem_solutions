/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:35
 * update_at: 2026-11-10 23:35
 */

// brute.cpp：小数据 O(n^2) 线性动态规划暴力
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

struct Challenge {
    ll l, r, v;
};

void solve() {
    ll n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<Challenge> cs;
    for (int i = 0; i < m; ++i) {
        ll x, y, v;
        cin >> x >> y >> v;
        ll l = x - y + 1;
        ll r = x;
        if (y <= k) {
            cs.push_back({l, r, v});
        }
    }

    // dp[i] 表示第 i 天不打卡时的最大收益
    vector<ll> dp(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        // 第 i 天不打卡：直接继承第 i-1 天
        dp[i] = dp[i - 1];

        // 枚举上一次不打卡的天数 j
        for (int j = max(0LL, i - k - 1); j < i; ++j) {
            // 区间 [j+1, i-1] 全部打卡
            ll run_len = (i - 1) - j;
            ll cost = run_len * d;
            ll reward = 0;
            for (const auto& c : cs) {
                if (c.l >= j + 1 && c.r <= i - 1) {
                    reward += c.v;
                }
            }
            dp[i] = max(dp[i], dp[j] - cost + reward);
        }
    }

    // 最后第 n 天可能打卡，相当于增加一个虚拟的第 n+1 天不打卡
    ll ans = dp[n];
    for (int j = max(0LL, n - k); j <= n; ++j) {
        ll run_len = n - j;
        ll cost = run_len * d;
        ll reward = 0;
        for (const auto& c : cs) {
            if (c.l >= j + 1 && c.r <= n) {
                reward += c.v;
            }
        }
        ans = max(ans, dp[j] - cost + reward);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_case_id, t;
    if (!(cin >> test_case_id >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
