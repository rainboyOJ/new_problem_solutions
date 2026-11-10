/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:43
 * update_at: 2026-11-11 00:43
 */
// brute.cpp：小规模暴力 O(n^2) 转移二分验证基准
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3fLL;

int n, d;
long long k;
long long x[5005];
long long s[5005];
long long dp[5005];

bool check(long long g) {
    long long L = max(1LL, d - g);
    long long R = d + g;

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = -INF;
        for (int j = 0; j < i; ++j) {
            long long dis = x[i] - x[j];
            if (dis >= L && dis <= R) {
                if (dp[j] != -INF) {
                    dp[i] = max(dp[i], dp[j] + s[i]);
                }
            }
        }
        if (dp[i] >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> d >> k)) return 0;

    long long sum_pos = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> s[i];
        if (s[i] > 0) sum_pos += s[i];
    }

    if (sum_pos < k) {
        cout << -1 << "\n";
        return 0;
    }

    long long left = 0, right = max(x[n], static_cast<long long>(d));
    long long ans = -1;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
