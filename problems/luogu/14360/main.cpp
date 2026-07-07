#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXV = 5000;
const int MAXN = 5005;

int n;
int a[MAXN];
int dp[MAXV + 1];   // dp[s] 表示前缀木棍中选出若干根，总和恰好为 s 的方案数，只记录 s <= 5000
int pow2[MAXN];     // pow2[i] = 2^i

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    // 预处理 2 的幂：前 i 根木棍的全部子集数是 2^i。
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = 1LL * pow2[i - 1] * 2 % MOD;
    }

    dp[0] = 1; // 空集方案
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int x = a[i];

        // 枚举第 i 根作为“选中集合中下标最大的木棍”。
        // 前 i-1 根的全部子集数。
        int total = pow2[i - 1];

        // 前 i-1 根中，子集和 <= x 的方案数。
        int leq = 0;
        for (int s = 0; s <= x; s++) {
            leq += dp[s];
            if (leq >= MOD) leq -= MOD;
        }

        // 若前面选出的木棍总和 > x，则加上当前木棍 x 后满足 sum > 2 * x。
        int greater = (total - leq + MOD) % MOD;
        ans += greater;
        ans %= MOD;

        // 把第 i 根木棍加入前缀 0/1 背包。
        // 超过 5000 的和不再细分，后续用 total - 前缀和统一统计。
        for (int s = MAXV; s >= x; s--) {
            dp[s] += dp[s - x];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
