#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2, 0));

    // dp[l][r] 表示当前只剩区间 [l, r] 这些零食时，后续能获得的最大收益。
    for (int len = 1; len <= n; ++len) {
        int day = n - len + 1;
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            if (l == r) {
                dp[l][r] = a[l] * day;
                continue;
            }
            dp[l][r] = max(
                dp[l + 1][r] + a[l] * day,
                dp[l][r - 1] + a[r] * day
            );
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}
