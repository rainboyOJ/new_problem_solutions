#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long a[MAXN];
long long dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dp[1] = a[1];
    long long ans = dp[1];

    for (int i = 2; i <= n; i++) {
        // dp[i] 表示“必须以第 i 天结尾”的最大连续利润。
        dp[i] = max(a[i], dp[i - 1] + a[i]);
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
