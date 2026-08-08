#include <bits/stdc++.h>
using namespace std;

static long long a[105];
static long long dp[105][105];
static int n;

long long score(int l, int r) {
    if (l == r) {
        return a[l];
    }
    return 1LL * abs(a[l] - a[r]) * (r - l + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            for (int k = l; k <= r; ++k) {
                long long right_part = (k == r ? 0 : dp[k + 1][r]);
                dp[l][r] = max(dp[l][r], score(l, k) + right_part);
            }

            for (int k = l; k <= r; ++k) {
                long long left_part = (k == l ? 0 : dp[l][k - 1]);
                dp[l][r] = max(dp[l][r], left_part + score(k, r));
            }
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}
