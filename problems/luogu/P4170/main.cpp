#include <bits/stdc++.h>
using namespace std;

static int dp[55][55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    // dp[l][r] 表示把目标子串 s[l..r] 涂出来的最少次数。
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            dp[l][r] = dp[l + 1][r] + 1;
            for (int k = l + 1; k <= r; ++k) {
                if (s[k] != s[l]) {
                    continue;
                }
                int left = (k == l + 1 ? 0 : dp[l + 1][k - 1]);
                dp[l][r] = min(dp[l][r], left + dp[k][r]);
            }
        }
    }

    cout << dp[0][n - 1] << '\n';
    return 0;
}
