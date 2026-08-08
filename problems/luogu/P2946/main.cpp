#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, f;
    cin >> n >> f;

    // dp[r] 表示当前已经选了若干头牛后，余数为 r 的方案数。
    vector<int> dp(f, 0), ndp(f, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        // 先拷贝“不选这头牛”的结果，再把“选这头牛一次”加进去。
        ndp = dp;
        int add = x % f;
        for (int r = 0; r < f; r++) {
            int nr = r + add;
            if (nr >= f) {
                nr -= f;
            }
            ndp[nr] += dp[r];
            if (ndp[nr] >= MOD) {
                ndp[nr] -= MOD;
            }
        }

        dp.swap(ndp);
    }

    // dp[0] 包含空集，题目要求非空子集，所以要减去 1。
    cout << (dp[0] + MOD - 1) % MOD << '\n';

    return 0;
}
