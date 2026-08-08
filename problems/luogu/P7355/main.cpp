#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 1000000007LL;

int T;
i64 n, m;

// 计算 base^exp mod MOD。
i64 quick_pow(i64 base, i64 exp) {
    i64 ans = 1;
    base %= MOD;

    while (exp > 0) {
        if (exp & 1LL) {
            ans = ans * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1LL;
    }

    return ans;
}

// 计算 1 + ratio + ratio^2 + ... + ratio^m。
// 这里要特别处理 ratio ≡ 1 (mod MOD) 的情况，此时分母没有逆元。
i64 geometric_sum(i64 ratio, i64 m) {
    ratio %= MOD;
    if (ratio < 0) {
        ratio += MOD;
    }

    if (ratio == 1) {
        return (m + 1) % MOD;
    }

    i64 up = (quick_pow(ratio, m + 1) - 1 + MOD) % MOD;
    i64 down = (ratio - 1 + MOD) % MOD;
    i64 inv_down = quick_pow(down, MOD - 2);
    return up * inv_down % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;

        // 对固定长度 k：
        // 1. 序列总数是 n^k；
        // 2. 不同元素个数之和，可以按“每种道具是否出现过”来统计。
        //    固定一种道具，它出现在序列中的方案数是 n^k - (n-1)^k。
        //    一共 n 种道具，所以不同元素个数总和是
        //    n * (n^k - (n-1)^k)。
        //
        // 因而长度为 k 的所有序列的权值和为：
        // n^k + n * (n^k - (n-1)^k)
        // = (n+1) * n^k - n * (n-1)^k
        //
        // 再把 k = 0..m 全部加起来，就是两段等比数列。
        i64 sum_pow_n = geometric_sum(n, m);
        i64 sum_pow_n_minus_1 = geometric_sum(n - 1, m);

        i64 ans = (n + 1) % MOD * sum_pow_n % MOD;
        ans = (ans - (n % MOD) * sum_pow_n_minus_1 % MOD + MOD) % MOD;

        cout << ans << '\n';
    }

    return 0;
}
