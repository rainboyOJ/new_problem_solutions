/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:42
 * update_at: 2026-10-06 18:42
 */

// 青蛙的约会：解同余方程 (m-n)*t ≡ (y-x) (mod L)，取最小非负解。
#include <cstdio>

typedef long long ll;

// 非负的辗转相除求 gcd。
ll gcd_ll(ll a, ll b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// 返回 nonnegative 的 a 在模 mod 下的逆元，调用前保证 gcd(a, mod) = 1。
ll mod_inverse(ll a, ll mod) {
    ll r0 = a, r1 = mod; // 辗转相除的两个余数
    ll s0 = 1, s1 = 0;   // 维护 a * s ≡ r (mod mod) 的系数
    while (r1 != 0) {
        ll q = r0 / r1;
        ll r2 = r0 - q * r1; // 先算新余数，再更新旧余数
        r0 = r1;
        r1 = r2;
        ll s2 = s0 - q * s1;
        s0 = s1;
        s1 = s2;
    }
    s0 %= mod;
    if (s0 < 0) {
        s0 += mod;
    }
    return s0;
}

int main() {
    ll x, y, m, n, L;
    if (scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L) != 5) {
        return 0;
    }

    // 把相遇条件 x + m*t ≡ y + n*t (mod L) 移项成 a*t ≡ b (mod L)。
    ll a = m - n;
    ll b = y - x;
    ll g = gcd_ll(a, L); // gcd(0, L) = L，步长相同的情形自动判无解

    if (b % g != 0) { // 右边不是 g 的倍数，方程无整数解
        printf("Impossible\n");
        return 0;
    }

    // 约去公因子，此时 a/g 与 M 互质，系数可逆。
    ll mod = L / g;
    ll a_reduced = a / g;
    ll b_reduced = b / g;
    // 规约到 [0, mod) 内，方便后续求逆元和取答案。
    a_reduced %= mod;
    if (a_reduced < 0) {
        a_reduced += mod;
    }
    b_reduced %= mod;
    if (b_reduced < 0) {
        b_reduced += mod;
    }

    ll inv = mod_inverse(a_reduced, mod);
    ll answer = b_reduced * inv % mod; // 最小非负解即最少跳跃次数
    printf("%lld\n", answer);
    return 0;
}
