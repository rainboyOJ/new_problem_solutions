#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000;
const int MAXN = 1005;

int n, k;
int dp[2][MAXN];
int prefix_sum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int now = i & 1;
        int pre = now ^ 1;

        memset(dp[now], 0, sizeof(dp[now]));
        prefix_sum[0] = dp[pre][0];
        for (int j = 1; j <= k; j++) {
            prefix_sum[j] = prefix_sum[j - 1] + dp[pre][j];
            if (prefix_sum[j] >= MOD) {
                prefix_sum[j] -= MOD;
            }
        }

        for (int j = 0; j <= k; j++) {
            // 把数字 i 插入前 i-1 个数字形成的排列中，
            // 新增的逆序对数可以是 0..i-1。
            int left = j - (i - 1);
            if (left <= 0) {
                dp[now][j] = prefix_sum[j];
            } else {
                dp[now][j] = prefix_sum[j] - prefix_sum[left - 1];
                if (dp[now][j] < 0) {
                    dp[now][j] += MOD;
                }
            }
        }
    }

    cout << dp[n & 1][k] << '\n';
    return 0;
}
