/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:30
 * update_at: 2026-10-05 23:30
 */

// main.cpp：求 A^B 的所有正约数之和 mod 9901。
// 关键点：A^B 的约数和 = ∏(1+p+...+p^{eB})；等比和用倍增递推求，
// 只靠乘加，避开 p≡1 (mod 9901) 时 p-1 不可逆、除法公式失效的陷阱。

#include <cstdio>
using namespace std;

typedef long long ll;

const ll MOD = 9901; // 题目模数（素数，但 p-1 未必可逆，不能依赖除法公式）

ll A, B;

// 快速幂：返回 base^exp mod MOD
ll power_mod(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// 倍增法求等比和 S(p,n)=1+p+...+p^n (mod MOD)，只用乘加
ll geometric(ll p, ll n) {
    if (n == 0) {
        return 1 % MOD;
    }
    ll m = n >> 1;
    if (n & 1) {
        // n = 2m+1：S(n) = S(m) * (1 + p^{m+1})
        return geometric(p, m) * (1 + power_mod(p, m + 1)) % MOD;
    }
    // n = 2m：S(n) = S(m-1) * (1 + p^m) + p^{2m}
    return (geometric(p, m - 1) * (1 + power_mod(p, m)) + power_mod(p, 2 * m)) % MOD;
}

void solve() {
    scanf("%lld %lld", &A, &B);

    if (B == 0 || A == 1) { // A^B = 1，唯一约数是 1
        printf("1\n");
        return;
    }
    if (A == 0) { // 0 的正整数次幂是 0
        printf("0\n");
        return;
    }

    ll ans = 1;
    ll rest = A; // 剩余待分解部分
    for (ll d = 2; d * d <= rest; d++) {
        if (rest % d != 0) {
            continue;
        }
        ll e = 0; // 质因子 d 的指数
        while (rest % d == 0) {
            rest /= d;
            e++;
        }
        ans = ans * geometric(d, e * B) % MOD;
    }
    if (rest > 1) { // 残留的是大于 sqrt(A) 的素因子，指数必为 1
        ans = ans * geometric(rest, B) % MOD;
    }
    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
