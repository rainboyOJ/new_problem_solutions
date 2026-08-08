#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXN = 5005;

int n;
long long L;
long long c[MAXN], sum[MAXN];
long long dp[MAXN];

long long X(int i) {
    return sum[i] + i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据朴素 DP。
    // 枚举最后一个箱子从哪里开始。
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            long long t = X(i) - X(j) - L - 1;
            dp[i] = min(dp[i], dp[j] + t * t);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
