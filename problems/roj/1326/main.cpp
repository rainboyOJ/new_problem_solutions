/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:49
 * update_at: 2026-10-05 09:49
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll b, p, k;

// 快速幂：返回 b^p mod k，所有中间乘积都对 k 取模
ll qpow(ll base, ll power, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while (power > 0) {
        if (power & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        power >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> b >> p >> k;
    ll ans = qpow(b, p, k);
    cout << b << "^" << p << " mod " << k << "=" << ans << "\n";
    return 0;
}
