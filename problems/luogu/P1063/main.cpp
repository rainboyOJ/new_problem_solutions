#include <bits/stdc++.h>
using namespace std;

static long long a[205];
static long long dp[205][205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    long long ans = 0;

    // 区间 [l, r] 表示一段链上的珠子，端点标签是 a[l] ... a[r+1]。
    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= 2 * n - 1; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r] + a[l] * a[k + 1] * a[r + 1]);
            }
            if (len == n) {
                ans = max(ans, dp[l][r]);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
