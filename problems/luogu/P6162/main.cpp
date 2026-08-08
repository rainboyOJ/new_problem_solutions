#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 1000000 + 5;
const i64 MOD = 998244353LL;

int n, k;
int group_cnt;
i64 fact[MAXN], inv_fact[MAXN];

i64 quick_pow(i64 base, int exp) {
    i64 ans = 1;
    base %= MOD;

    while (exp > 0) {
        if (exp & 1) {
            ans = ans * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }

    return ans;
}

void init_comb(int up) {
    fact[0] = 1;
    for (int i = 1; i <= up; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv_fact[up] = quick_pow(fact[up], (int)MOD - 2);
    for (int i = up; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    group_cnt = n - k;

    init_comb(group_cnt);

    // 原题答案 = 第二类 Stirling 数 S(n, n-k)
    // 用满射计数的容斥公式：
    // S(n,m) = 1 / m! * sum_{i=0}^{m} (-1)^i C(m,i) (m-i)^n
    //        = sum_{i=0}^{m} (-1)^i (m-i)^n / (i! (m-i)!)
    i64 ans = 0;
    for (int i = 0; i <= group_cnt; i++) {
        int remain = group_cnt - i;
        i64 term = quick_pow(remain, n);
        term = term * inv_fact[i] % MOD * inv_fact[remain] % MOD;

        if (i & 1) {
            ans -= term;
            if (ans < 0) {
                ans += MOD;
            }
        }
        else {
            ans += term;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
