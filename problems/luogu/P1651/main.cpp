#include <bits/stdc++.h>
using namespace std;

const int MAXS = 500005;
const int NEG_INF = -1000000000;

int n;
int h[55];
int dp[MAXS], ndp[MAXS];
int sum_h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sum_h += h[i];
    }

    for (int i = 0; i <= sum_h; i++) {
        dp[i] = NEG_INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int d = 0; d <= sum_h; d++) {
            ndp[d] = dp[d];
        }

        for (int d = 0; d <= sum_h; d++) {
            if (dp[d] == NEG_INF) {
                continue;
            }

            // 把当前木块放到较高的塔上，差值增大。
            ndp[d + h[i]] = max(ndp[d + h[i]], dp[d]);

            // 把当前木块放到较低的塔上。
            int new_diff = abs(d - h[i]);
            int new_low = dp[d] + min(d, h[i]);
            ndp[new_diff] = max(ndp[new_diff], new_low);
        }

        for (int d = 0; d <= sum_h; d++) {
            dp[d] = ndp[d];
        }
    }

    cout << dp[0] << '\n';
    return 0;
}
