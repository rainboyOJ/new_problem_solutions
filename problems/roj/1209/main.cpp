/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:37
 */

#include <cstdio>
#include <algorithm>

typedef long long ll;

// 当前累加和保存为分数 a / b，始终保持最简形式
ll a = 0, b = 1;

// 计算最大公约数，用于约分
ll my_gcd(ll x, ll y) {
    if (y == 0) return x;
    return my_gcd(y, x % y);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ll p, q;
        scanf("%lld/%lld", &p, &q);
        // 通分相加：a/b + p/q = (a*q + b*p) / (b*q)
        a = a * q + b * p;
        b = b * q;
        // 立即约分，保持最简
        ll g = my_gcd(a, b);
        a /= g;
        b /= g;
    }
    if (b == 1)
        printf("%lld\n", a); // 分母为 1 时只输出整数
    else
        printf("%lld/%lld\n", a, b);
    return 0;
}
