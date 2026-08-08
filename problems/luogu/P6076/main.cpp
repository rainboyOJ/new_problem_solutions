#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXV = 405;
const i64 MOD = 1000000007LL;

int n, m, c;
i64 fact[MAXV], inv_fact[MAXV];
i64 row_coef[MAXV], col_coef[MAXV], color_coef[MAXV];

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

i64 C(int x, int y) {
    if (y < 0 || y > x) {
        return 0;
    }
    return fact[x] * inv_fact[y] % MOD * inv_fact[x - y] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c;

    int up = max(n, max(m, c));
    init_comb(up);

    // row_coef[r] 表示恰好保留 r 行时的容斥系数：
    // (-1)^(n-r) * C(n,r)
    for (int r = 0; r <= n; r++) {
        row_coef[r] = C(n, r);
        if ((n - r) & 1) {
            row_coef[r] = (MOD - row_coef[r]) % MOD;
        }
    }

    for (int s = 0; s <= m; s++) {
        col_coef[s] = C(m, s);
        if ((m - s) & 1) {
            col_coef[s] = (MOD - col_coef[s]) % MOD;
        }
    }

    // avail 表示可用符号数：0(不染色) + 若干种没有被禁掉的颜色
    // 即 avail = 1..c+1
    for (int avail = 1; avail <= c + 1; avail++) {
        int miss = c + 1 - avail;
        color_coef[avail] = C(c, miss);
        if (miss & 1) {
            color_coef[avail] = (MOD - color_coef[avail]) % MOD;
        }
    }

    i64 ans = 0;

    // 三重容斥：
    // 1. 删掉若干空行
    // 2. 删掉若干空列
    // 3. 删掉若干没有出现的颜色
    //
    // 剩余 r 行 s 列时，每个格子有 avail 种选法：
    // - 不染色
    // - 染成剩下的 avail-1 种颜色之一
    //
    // 所以贡献是 avail^(r*s)
    for (int avail = 1; avail <= c + 1; avail++) {
        i64 sum_rc = 0;

        i64 pow_row = 1; // avail^r
        for (int r = 0; r <= n; r++) {
            i64 pow_cell = 1; // (avail^r)^s = avail^(r*s)
            for (int s = 0; s <= m; s++) {
                i64 add = row_coef[r] * col_coef[s] % MOD * pow_cell % MOD;
                sum_rc += add;
                if (sum_rc >= MOD) {
                    sum_rc -= MOD;
                }
                pow_cell = pow_cell * pow_row % MOD;
            }
            pow_row = pow_row * avail % MOD;
        }

        ans += color_coef[avail] * sum_rc % MOD;
        ans %= MOD;
    }

    cout << ans << '\n';

    return 0;
}
