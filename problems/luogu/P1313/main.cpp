/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:27
 * update_at: 2026-11-11 00:27
 */
#include <iostream>

using namespace std;

using ll = long long;
const int MOD = 10007;

// 杨辉三角组合数表
int c[1005][1005];

// 快速幂计算 base^exp % MOD
ll quick_pow(ll base, ll exp) {
    ll ans = 1 % MOD;
    base %= MOD;

    while (exp > 0) {
        if (exp & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }

    return ans;
}

// 预处理组合数 C(i, j)
void init_comb(int limit) {
    for (int i = 0; i <= limit; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    int k, n, m;
    if (!(cin >> a >> b >> k >> n >> m)) return 0;

    init_comb(k);

    ll comb_kn = c[k][n];
    ll a_pow_n = quick_pow(a, n);
    ll b_pow_m = quick_pow(b, m);

    ll ans = comb_kn * a_pow_n % MOD * b_pow_m % MOD;

    cout << ans << "\n";

    return 0;
}
