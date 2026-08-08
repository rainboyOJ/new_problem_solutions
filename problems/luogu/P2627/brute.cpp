#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举最后一个不选的位置 j，复杂度 O(nk)，只适合小数据。

const int MAXN = 305;

int n, k;
long long e[MAXN];
long long prefix_sum[MAXN];
long long dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
        prefix_sum[i] = prefix_sum[i - 1] + e[i];
    }

    for (int i = 1; i <= n; i++) {
        long long best = 0;
        for (int j = max(0, i - k); j <= i; j++) {
            long long left_best = 0;
            if (j > 0) {
                left_best = dp[j - 1];
            }
            long long value = left_best + prefix_sum[i] - prefix_sum[j];
            if (j == max(0, i - k) || value > best) {
                best = value;
            }
        }
        dp[i] = best;
    }

    cout << dp[n] << '\n';

    return 0;
}
