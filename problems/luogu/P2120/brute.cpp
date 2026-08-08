#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXN = 5005;

long long x[MAXN], p[MAXN], c[MAXN];
long long sum_p[MAXN], sum_px[MAXN];
long long dp[MAXN];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据朴素 DP。
    // 直接枚举上一个建仓库的位置。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> p[i] >> c[i];
        sum_p[i] = sum_p[i - 1] + p[i];
        sum_px[i] = sum_px[i - 1] + p[i] * x[i];
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            long long cost = dp[j]
                           + c[i]
                           + x[i] * (sum_p[i] - sum_p[j])
                           - (sum_px[i] - sum_px[j]);
            dp[i] = min(dp[i], cost);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
