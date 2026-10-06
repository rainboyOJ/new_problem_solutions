/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:00
 * update_at: 2026-10-06 16:00
 */
#include <cstdio>

typedef long long ll;

int main() {
    ll a, b; // 两种金币的面值，互素，最大 1e9，乘积约 1e18 需要 ll
    scanf("%lld %lld", &a, &b);
    // Frobenius 数：互素两币值凑不出的最大价值是 a*b - a - b
    printf("%lld\n", a * b - a - b);
    return 0;
}
