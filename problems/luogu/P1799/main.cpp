#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];
int dp[MAXN]; // dp[i]：把 a[i] 作为最后一个“在自己位置上的数”时，最多能有多少个这样的数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] <= i) {
            dp[i] = 1;
        }

        for (int j = 1; j < i; j++) {
            // 让 a[j] 和 a[i] 都成为匹配点时，
            // 中间必须有足够多的元素来填满位置差。
            if (dp[j] > 0 && a[j] < a[i] && i - j >= a[i] - a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
