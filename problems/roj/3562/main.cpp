/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:05
 * update_at: 2026-10-06 14:05
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m;
// dp[i][j] 表示传 i 次后球在 j 号同学手中的方案数
ll dp[35][35];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    dp[0][0] = 1; // 初始球在小蛮（0 号）手中

    for (ll i = 1; i <= m; i++) {
        for (ll j = 0; j < n; j++) {
            ll left = (j - 1 + n) % n;  // j 的左邻居
            ll right = (j + 1) % n;     // j 的右邻居
            dp[i][j] = dp[i - 1][left] + dp[i - 1][right];
        }
    }

    cout << dp[m][0] << "\n";
    return 0;
}
