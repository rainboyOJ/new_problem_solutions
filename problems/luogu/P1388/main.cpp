#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, k;
int a[MAXN];
int sum[MAXN];
long long dp[MAXN][MAXN][MAXN];

int range_sum(int l, int r) {
    return sum[r] - sum[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    memset(dp, -1, sizeof(dp));

    // dp[l][r][t] 表示区间 [l,r] 内恰好放 t 个乘号时的最大值。
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            // 不放乘号时，整个区间只能全部用加号连接。
            dp[l][r][0] = range_sum(l, r);

            for (int t = 1; t < len; t++) {
                long long best = -1;

                // 最后一次运算可能是加号，也可能是乘号。
                // 枚举最后运算左右两边的区间和乘号数量。
                for (int mid = l; mid < r; mid++) {
                    int left_len = mid - l + 1;
                    int right_len = r - mid;

                    // 最后一次运算是加号：左右乘号数量之和为 t。
                    for (int x = 0; x <= t; x++) {
                        int y = t - x;
                        if (x >= left_len || y >= right_len) {
                            continue;
                        }
                        if (dp[l][mid][x] == -1 || dp[mid + 1][r][y] == -1) {
                            continue;
                        }
                        best = max(best, dp[l][mid][x] + dp[mid + 1][r][y]);
                    }

                    // 最后一次运算是乘号：当前这个乘号占 1 个。
                    for (int x = 0; x <= t - 1; x++) {
                        int y = t - 1 - x;
                        if (x >= left_len || y >= right_len) {
                            continue;
                        }
                        if (dp[l][mid][x] == -1 || dp[mid + 1][r][y] == -1) {
                            continue;
                        }
                        best = max(best, dp[l][mid][x] * dp[mid + 1][r][y]);
                    }
                }

                dp[l][r][t] = best;
            }
        }
    }

    cout << dp[1][n][k] << '\n';
    return 0;
}
