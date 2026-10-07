/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:38
 * update_at: 2026-10-06 01:38
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 10007; // 题面指定的模数

ll a, b, k, n, m;

// 快速幂：求 p^e mod MOD
ll qpow(ll p, ll e) {
    ll ret = 1;
    while (e > 0) {
        if (e & 1)
            ret = ret * p % MOD;
        p = p * p % MOD;
        e >>= 1;
    }
    return ret;
}

int main() {
    cin >> a >> b >> k >> n >> m;

    // 用杨辉三角递推求 C(k, n)：c[j] 表示 C(i, j)，逐行更新
    ll c[1005] = {0};
    c[0] = 1;
    for (ll i = 1; i <= k; i++)
        for (ll j = i; j >= 1; j--)
            c[j] = (c[j] + c[j - 1]) % MOD;

    // 二项式定理：x^n y^m 项的系数 = C(k,n) * a^n * b^m
    ll ans = c[n] * qpow(a, n) % MOD * qpow(b, m) % MOD;
    cout << ans << endl;
    return 0;
}
