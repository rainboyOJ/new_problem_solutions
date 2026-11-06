/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// POJ 1995 Raising Modulo Numbers：快速幂
// 输出 (A1^B1 + A2^B2 + ... + AH^BH) mod M
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算 a^b mod mod
ll qpow(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll Z;
    cin >> Z;
    while (Z--) {
        ll M, H;
        cin >> M >> H;
        ll sum = 0;
        for (ll i = 1; i <= H; i++) {
            ll A, B;
            cin >> A >> B;
            sum = (sum + qpow(A, B, M)) % M;
        }
        cout << sum << '\n';
    }

    return 0;
}
