#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ans = 0;
    // 枚举所有子集 (2^n 种)
    for (int mask = 0; mask < (1 << n); mask++) {
        int m = __builtin_popcount(mask);
        if (m < 3) continue; // 至少需要 3 条边

        long long sum = 0, maxv = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                sum += a[i];
                maxv = max(maxv, (long long)a[i]);
            }
        }
        if (sum > 2 * maxv) ans++;
    }
    cout << ans % MOD << '\n';

    return 0;
}
