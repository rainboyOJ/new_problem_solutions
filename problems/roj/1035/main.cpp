/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:06
 * update_at: 2026-10-04 23:06
 */

#include <cstdio>

typedef long long ll;

ll a1, a2, n; // a1, a2 是等差数列前两项，n 是要求的项数

int main() {
    scanf("%lld %lld %lld", &a1, &a2, &n);
    ll d = a2 - a1;       // 公差：相邻两项的固定增量，可为负或零，无需特判
    ll an = a1 + (n - 1) * d; // 通项公式：第 n 项 = 首项 + (n-1) 个公差
    printf("%lld\n", an);
    return 0;
}
