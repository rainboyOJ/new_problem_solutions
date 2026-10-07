/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:04
 * update_at: 2026-10-06 01:04
 */

#include <cstdio>

using namespace std;

typedef long long ll;

const ll MOD = 200907;

ll T, a, b, c, k;

// 快速幂：返回 base^exp mod MOD
ll qpow(ll base, ll exp) {
    ll res = 1 % MOD;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld %lld %lld %lld", &a, &b, &c, &k);
        ll ans;
        if (2 * b == a + c) { // 等差数列
            ll d = b - a;
            // 通项 a+(k-1)d，模意义下运算
            ans = ((a % MOD) + (((k - 1) % MOD) * (d % MOD)) % MOD) % MOD;
        } else { // 等比数列，题面保证 r 为整数
            ll r = b / a;
            ans = ((a % MOD) * qpow(r, k - 1)) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
