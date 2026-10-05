/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:19
 * update_at: 2026-10-06 01:19
 */
#include <cstdio>

typedef long long ll;

ll n; // 输入的整数，是两个不同质数的乘积

// 试除找到较小的质因数，返回较大的那个质数
ll solve(ll x) {
    for (ll d = 2; d * d <= x; ++d) { // 较小质因数不超过 sqrt(x)
        if (x % d == 0) {
            return x / d; // d 是小质因数，x/d 是大质因数
        }
    }
    return x; // 兜底，理论上不会发生
}

int main() {
    scanf("%lld", &n);
    printf("%lld\n", solve(n));
    return 0;
}
