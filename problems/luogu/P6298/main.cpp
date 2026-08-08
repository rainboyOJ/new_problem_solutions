#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXM = 1000000 + 5;
const i64 MOD = 1000000007LL;

int n, m, k;
int a[MAXM];
int freq[MAXM];
int divisible_cnt[MAXM];
i64 fact[MAXM], inv_fact[MAXM];
i64 exact_ans[MAXM];

i64 quick_pow(i64 base, i64 exp) {
    i64 ans = 1 % MOD;
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

    inv_fact[up] = quick_pow(fact[up], MOD - 2);
    for (int i = up; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }
}

i64 C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }

    init_comb(n);

    for (int d = 1; d <= m; d++) {
        for (int x = d; x <= m; x += d) {
            divisible_cnt[d] += freq[x];
        }
    }

    // ways[d] = gcd 是 d 的倍数的方案数
    // exact[d] = gcd 恰好等于 d 的方案数
    for (int d = m; d >= 1; d--) {
        i64 ways = C(divisible_cnt[d], k);
        i64 sub = 0;
        for (int x = d + d; x <= m; x += d) {
            sub += exact_ans[x];
            if (sub >= MOD) {
                sub -= MOD;
            }
        }

        exact_ans[d] = (ways - sub) % MOD;
        if (exact_ans[d] < 0) {
            exact_ans[d] += MOD;
        }
    }

    for (int d = 1; d <= m; d++) {
        cout << exact_ans[d];
        if (d == m) {
            cout << '\n';
        }
        else {
            cout << ' ';
        }
    }

    return 0;
}
