#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    vector<int> a(n);
    int max_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }

    int limit = k * max_a;
    vector<int> dp(limit + 1, INF);
    dp[0] = 0;

    // 完全背包：每种面值的邮票可以使用无限次。
    for (int v : a) {
        for (int x = v; x <= limit; x++) {
            dp[x] = min(dp[x], dp[x - v] + 1);
        }
    }

    int answer = 0;
    for (int x = 1; x <= limit; x++) {
        if (dp[x] <= k) {
            answer = x;
        } else {
            break;
        }
    }

    cout << answer << '\n';

    return 0;
}
