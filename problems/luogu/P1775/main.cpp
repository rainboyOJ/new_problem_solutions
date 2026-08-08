#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1), sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // dp[l][r] 表示把区间 [l, r] 合并成一堆的最小代价
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            int seg_sum = sum[r] - sum[l - 1];
            for (int k = l; k < r; ++k) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + seg_sum);
            }
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}
