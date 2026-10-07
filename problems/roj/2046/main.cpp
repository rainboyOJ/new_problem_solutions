/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:29
 * update_at: 2026-10-06 10:30
 */
#include <cstdio>

typedef long long ll;

// D 表：D[n] = n! (n < 5) 去掉末尾 0 后的个位，作为递归出口
ll d5[5] = { 1, 1, 2, 6, 4 };

// p2[k % 4] = 2^k 的个位（2 的个位按 2,4,8,6 循环）
ll p2[4] = { 6, 2, 4, 8 };

// d(n) 求 n! 去掉全部末尾 0 后的个位：
// 把每个 5 的倍数提出一个因子 5 与偶数配成 10 消掉，
// 剩余部分是 (n/5)! 继续递归，同时补上被配对消耗的偶数，即乘 2^(n/5) 的个位。
ll d(ll n) {
    if (n < 5) return d5[n];
    ll q = n / 5, r = n % 5;
    return d(q) * d5[r] % 10 * p2[q % 4] % 10;
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%lld\n", d(n));
    return 0;
}
