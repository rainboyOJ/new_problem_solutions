#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接枚举每个格子的所有前驱，复杂度 O(nr)，只适合小数据。

const int MAXN = 305;
const int NEG_INF = -1000000000;

int n, l, r;
int a[MAXN];
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> l >> r;
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
        dp[i] = NEG_INF;
    }
    dp[0] = 0;

    int ans = NEG_INF;
    for (int i = 1; i <= n; i++) {
        for (int j = max(0, i - r); j <= i - l; j++) {
            if (dp[j] != NEG_INF) {
                dp[i] = max(dp[i], dp[j] + a[i]);
            }
        }
        if (i + r > n) {
            ans = max(ans, dp[i]);
        }
    }

    cout << ans << '\n';

    return 0;
}
