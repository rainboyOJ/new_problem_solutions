#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

static long long dp[105][105];
static long long next_dp[105][105];
static long long cover_sum[105][105];
static int bad_prefix[105][105];
static char grid[105][105];

bool ok(int row, int l, int r) {
    return bad_prefix[row][r] - bad_prefix[row][l - 1] == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> rows(n + 1);
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        rows[i] = s;
    }
    for (int i = 1; i <= n; ++i) {
        string s = rows[n - i + 1];
        for (int j = 1; j <= m; ++j) {
            grid[i][j] = s[j - 1];
            bad_prefix[i][j] = bad_prefix[i][j - 1] + (grid[i][j] == 'X');
        }
    }

    // 第 0 层地基固定是整段 [1, m]。
    dp[1][m] = 1;
    long long ans = 1; // 什么都不放也算一种。

    for (int row = 1; row <= n; ++row) {
        for (int l = 1; l <= m; ++l) {
            for (int r = m; r >= 1; --r) {
                long long val = dp[l][r];
                if (l > 1) {
                    val = (val + cover_sum[l - 1][r]) % MOD;
                }
                if (r < m) {
                    val = (val + cover_sum[l][r + 1]) % MOD;
                }
                if (l > 1 && r < m) {
                    val = (val - cover_sum[l - 1][r + 1] + MOD) % MOD;
                }
                cover_sum[l][r] = val;
            }
        }

        for (int l = 1; l <= m; ++l) {
            for (int r = l; r <= m; ++r) {
                if (!ok(row, l, r)) {
                    next_dp[l][r] = 0;
                    continue;
                }
                next_dp[l][r] = cover_sum[l][r];
                ans = (ans + next_dp[l][r]) % MOD;
            }
        }

        for (int l = 1; l <= m; ++l) {
            for (int r = 1; r <= m; ++r) {
                dp[l][r] = next_dp[l][r];
                next_dp[l][r] = 0;
                cover_sum[l][r] = 0;
            }
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}
