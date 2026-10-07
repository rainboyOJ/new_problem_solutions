/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:29
 * update_at: 2026-10-06 01:30
 */
#include <cstdio>
#include <utility>
using namespace std;

typedef long long ll;

ll n, m; // n 为求和上界，m 为取模数

// 快速倍增：返回 (F(k) mod m, F(k+1) mod m)，每层用半规模的一对值翻倍得到整规模
pair<ll, ll> fib_pair(ll k) {
    if (k == 0) {
        return make_pair(0LL, 1 % m); // k = 0 时 (F(0), F(1)) = (0, 1)，m = 1 时归零
    }
    pair<ll, ll> half = fib_pair(k >> 1);
    ll a = half.first;  // F(k/2)
    ll b = half.second; // F(k/2 + 1)
    // F(2t) = F(t) * (2F(t+1) - F(t))，先取模再乘，避免 2b - a 为负
    ll c = a * (((2 * b - a) % m + m) % m) % m;
    // F(2t+1) = F(t)^2 + F(t+1)^2，两项分开取模防止相加溢出
    ll d = ((a * a) % m + (b * b) % m) % m;
    if (k & 1) {
        return make_pair(d, (c + d) % m); // 奇数再走一步
    }
    return make_pair(c, d);
}

int main() {
    scanf("%lld %lld", &n, &m);

    pair<ll, ll> p = fib_pair(n);
    ll fn = p.first;    // F(n)
    ll fn1 = p.second;  // F(n+1)
    ll fn2 = (fn + fn1) % m;   // F(n+2)
    ll fn3 = (fn1 + fn2) % m;  // F(n+3)

    // 恒等式 T(n) = sum(i * F(i)) = n * F(n+2) - F(n+3) + 2 (mod m)
    ll ans = ((n % m) * fn2 % m - fn3 + 2) % m;
    ans = (ans + m) % m; // 加法结果可能为负，修正到 [0, m)
    printf("%lld\n", ans);
    return 0;
}
