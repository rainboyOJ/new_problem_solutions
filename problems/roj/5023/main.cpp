/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:08
 * update_at: 2026-10-08 22:08
 */
#include <cstdio>

typedef long long ll;

ll m, n; // 题面输入的两个正整数

// 辗转相除法（欧几里得算法）求 gcd(a, b)，迭代版，无递归深度风险。
// 依据：gcd(a, b) = gcd(b, a mod b)；每步余数严格小于除数且非负，
// 序列严格下降，必在有限步收敛到 0，此时除数就是最大公约数。
ll gcd_euclid(ll a, ll b) {
    while (b != 0) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    scanf("%lld %lld", &m, &n);
    // gcd 关于两个参数是对称的（公约数集合本身对称），故无需先把 m 归一成 m >= n：
    // m < n 时首轮 a % b == a，循环自动完成一次交换。
    printf("%lld\n", gcd_euclid(m, n));
    return 0;
}
