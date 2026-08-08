#include <bits/stdc++.h>
using namespace std;

static int a[255];
static int dp[255][255];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[i][i] = a[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, a[i]);
    }

    // dp[l][r] 表示区间 [l, r] 能整体合成的最大值，0 表示不能整体合成。
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                if (dp[l][k] == 0 || dp[l][k] != dp[k + 1][r]) {
                    continue;
                }
                dp[l][r] = max(dp[l][r], dp[l][k] + 1);
            }
            ans = max(ans, dp[l][r]);
        }
    }

    cout << ans << '\n';
    return 0;
}
