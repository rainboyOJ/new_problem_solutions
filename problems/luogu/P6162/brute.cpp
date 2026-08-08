#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 998244353LL;

int n, k;
vector<i64> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    dp.assign(k + 1, 0);
    dp[0] = 1;

    // 直接按题意做 DP：
    // dp[j] = 处理完前若干个格子，恰好填了 j 个格子的方案数
    //
    // 处理第 i 个格子时：
    // 1. 不填，方案数不变
    // 2. 填一个数。若之前已经填了 j-1 个互不相同的数，
    //    那么 1..i 中还剩 i-(j-1) = i-j+1 个数可选。
    for (int i = 1; i <= n - 1; i++) {
        for (int j = min(i, k); j >= 1; j--) {
            dp[j] = (dp[j] + 1LL * (i - j + 1) * dp[j - 1]) % MOD;
        }
    }

    cout << dp[k] << '\n';

    return 0;
}
