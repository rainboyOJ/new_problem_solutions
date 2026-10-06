/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:11
 * update_at: 2026-10-06 18:11
 */
#include <cstdio>

typedef long long ll;

ll a, b;   // 题目给出的两个正整数，2 <= a, b <= 2*10^9
ll gx, gy; // 保存 exgcd 求出的一组解：a*gx + b*gy = gcd(a, b)

// 扩展欧几里得：解 a*x + b*y = gcd(a, b)，结果存入 gx, gy，返回 gcd
// 递归基例：b = 0 时 gcd = a，一组解是 (1, 0)
// 回代：设子问题 b*x' + (a%b)*y' = g 已解出，代入 a%b = a - (a/b)*b
//       整理得 a*y' + b*(x' - (a/b)*y') = g，即 x = y', y = x' - (a/b)*y'
ll exgcd(ll a, ll b) {
    if (b == 0) {
        gx = 1;
        gy = 0;
        return a;
    }
    ll g = exgcd(b, a % b);
    ll x = gy;
    ll y = gx - (a / b) * gy;
    gx = x;
    gy = y;
    return g;
}

int main() {
    scanf("%lld %lld", &a, &b);
    exgcd(a, b);
    // 方程 ax ≡ 1 (mod b) 等价于 ax + by = 1，保证有解即 gcd(a,b) = 1
    // 解集是公差为 b 的等差数列，特解 gx 对 b 取模即最小正整数解
    // 因为 b >= 2 且 gx*1 ≡ 1，gx mod b 不会等于 0，无需特判
    ll ans = gx % b;
    if (ans <= 0) ans += b; // C++ 取模可能得 0 或负数，兜底修正
    printf("%lld\n", ans);
    return 0;
}
