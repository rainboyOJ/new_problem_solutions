/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:44
 * update_at: 2026-10-05 03:44
 */
#include <cstdio>
#include <cmath>

typedef long long ll;

// sigma(n)：n 的真因数和（不含 n 本身的因子之和）
// 因因子成对出现：d 是因子则 n/d 也是，所以只枚举 d<=sqrt(n)；
// 每对 (d, n/d) 各收一次；1 单独计入；n 为完全平方数时 sqrt(n) 是自己的搭档，
// d*d==n 时只算一次。
ll sigma(ll n) {
    if (n == 1) return 0;
    ll s = 1; // 1 必为真因子
    ll r = (ll) sqrt((long double) n); // sqrt 取下整用于 d<=r 枚举
    for (ll d = 2; d <= r; ++d) {
        if (n % d == 0) {
            s += d;
            if (d * d != n) s += n / d; // d* d != n 保证完全平方数只收一次
        }
    }
    return s;
}

int main() {
    // 题目无输入；a 从 2 起递增枚举，第一次命中 sigma(sigma(a))==a 且 sigma(a)!=a 即最小解
    for (ll a = 2; ; ++a) {
        ll b = sigma(a);
        if (b != a && sigma(b) == a) {
            printf("%lld %lld\n", a, b);
            break;
        }
    }
    return 0;
}