#include <bits/stdc++.h>
using namespace std;

const int MOD = 19650827;

static int h[1005];
static int dp[1005][1005][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    for (int i = 1; i <= n; ++i) {
        dp[i][i][0] = 1;
    }

    // dp[l][r][0/1]：已经构成目标区间 [l, r]，
    // 且最后插入的人在左端/右端时的方案数。
    for (int len = 1; len < n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            if (dp[l][r][0]) {
                if (l > 1 && h[l - 1] < h[l]) {
                    dp[l - 1][r][0] = (dp[l - 1][r][0] + dp[l][r][0]) % MOD;
                }
                if (r < n && h[r + 1] > h[l]) {
                    dp[l][r + 1][1] = (dp[l][r + 1][1] + dp[l][r][0]) % MOD;
                }
            }

            if (dp[l][r][1]) {
                if (l > 1 && h[l - 1] < h[r]) {
                    dp[l - 1][r][0] = (dp[l - 1][r][0] + dp[l][r][1]) % MOD;
                }
                if (r < n && h[r + 1] > h[r]) {
                    dp[l][r + 1][1] = (dp[l][r + 1][1] + dp[l][r][1]) % MOD;
                }
            }
        }
    }

    cout << (dp[1][n][0] + dp[1][n][1]) % MOD << '\n';
    return 0;
}
