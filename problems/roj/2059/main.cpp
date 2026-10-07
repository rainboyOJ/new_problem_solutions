/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:30
 * update_at: 2026-10-06 10:30
 */

// usaco-3.4.3 fence9：数三角形 (0,0),(n,m),(p,0) 内部的整点数。
// Pick 定理 S = I + B/2 - 1，移项并用两倍量避免小数：
//   2S = p * m
//   B  = gcd(n,m) + gcd(|p-n|,m) + p   （三条边上的整点数，顶点重复计数已扣掉）
//   I  = (2S - B + 2) / 2
#include <cstdio>
using namespace std;

typedef long long ll;

ll n, m, p; // 三角形三个顶点 (0,0)、(n,m)、(p,0)

// 欧几里得算法求最大公约数，供统计边界整点数使用
ll gcd_ll(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    scanf("%lld %lld %lld", &n, &m, &p);

    ll area2 = p * m;                                      // 鞋带公式给出的两倍面积
    ll boundary = gcd_ll(n, m) + gcd_ll(p - n < 0 ? n - p : p - n, m) + p; // 三边整点数
    ll interior = (area2 - boundary + 2) / 2;              // Pick 定理求内部整点数

    printf("%lld\n", interior);
    return 0;
}
