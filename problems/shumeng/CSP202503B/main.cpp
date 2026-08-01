/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> happiness(m + 1, 0);
    for (int i = 1; i <= m; i++) cin >> happiness[i];

    vector<long long> dp(n + 1, -(1LL << 60));
    dp[0] = 0;
    for (int apples = 1; apples <= n; apples++) {
        int limit = min(m, apples);
        for (int today = 1; today <= limit; today++) {
            dp[apples] = max(dp[apples], dp[apples - today] + happiness[today]);
        }
    }
    cout << dp[n] << '\n';
    return 0;
}
