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

ll qpow(ll a, ll b) {
    ll res = 1 % MOD;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return qpow(x, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    int k, n, m;
    if (!(cin >> a >> b >> k >> n >> m)) return 0;

    // 用阶乘与逆元直接算组合数 C(k, n)
    ll num = 1;
    ll den = 1;
    for (int i = 1; i <= n; ++i) {
        num = num * (k - i + 1) % MOD;
        den = den * i % MOD;
    }
    ll comb = num * inv(den) % MOD;

    ll ans = comb * qpow(a, n) % MOD * qpow(b, m) % MOD;
    cout << ans << "\n";

    return 0;
}
