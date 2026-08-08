#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 1005;
const int MAXV = 3005;
const i64 MOD = 1000000007LL;

int n, m;
int a[MAXN];
i64 fact[MAXV], inv_fact[MAXV];

i64 quick_pow(i64 base, i64 exp) {
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

    inv_fact[up] = quick_pow(fact[up], MOD - 2);
    for (int i = up; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }
}

i64 C(int x, int y) {
    if (y < 0 || y > x) {
        return 0;
    }
    return fact[x] * inv_fact[y] % MOD * inv_fact[x - y] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int max_a = 0;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }

    init_comb(n + max_a);

    i64 ans = 0;

    // 容斥：先允许有人没分到东西，再把“至少一个人空着”的方案扣掉。
    // 如果恰好有 t 个人空着，那么只剩 n-t 个同学要接收所有特产。
    // 对于一种数量为 a[i] 的特产，把 a[i] 个相同物品分给 n-t 个不同同学，
    // 允许有人分到 0 个，方案数是 C(a[i] + n-t - 1, n-t - 1)。
    for (int empty_cnt = 0; empty_cnt <= n - 1; empty_cnt++) {
        int used = n - empty_cnt;
        i64 ways = C(n, empty_cnt);

        for (int i = 1; i <= m; i++) {
            ways = ways * C(a[i] + used - 1, used - 1) % MOD;
        }

        if (empty_cnt & 1) {
            ans -= ways;
            if (ans < 0) {
                ans += MOD;
            }
        }
        else {
            ans += ways;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
