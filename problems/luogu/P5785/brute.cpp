#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXN = 5005;

int n;
long long s;
long long t[MAXN], c[MAXN];
long long sum_t[MAXN], sum_c[MAXN];
long long dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据朴素 DP。
    // 直接枚举上一批的结束位置。
    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> c[i];
        sum_t[i] = sum_t[i - 1] + t[i];
        sum_c[i] = sum_c[i - 1] + c[i];
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            long long cost = dp[j]
                           + (sum_t[i] - sum_t[j]) * (sum_c[n] - sum_c[j])
                           + s * (sum_c[n] - sum_c[j]);
            dp[i] = min(dp[i], cost);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
