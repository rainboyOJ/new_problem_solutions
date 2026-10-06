/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:16
 * update_at: 2026-10-06 12:16
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll x0_val, y0_val; // 题目输入：gcd 目标与 lcm 目标（避免 y0 与 math.h 的贝塞尔函数冲突）

// 返回 k 的不同质因子个数 ω(k)
int distinct_primes(ll k) {
    int cnt = 0;
    for (ll d = 2; d * d <= k; ++d) {
        if (k % d == 0) {
            ++cnt;          // 发现一个质因子，只计一次
            while (k % d == 0) k /= d; // 把 d 的整段幂除尽
        }
    }
    return cnt + (k > 1);   // 剩余部分若大于 1 是一个大质因子
}

int main() {
    scanf("%lld %lld", &x0_val, &y0_val);

    // gcd 必须整除 lcm，否则不存在这样的正整数对
    if (y0_val % x0_val != 0) {
        printf("0\n");
        return 0;
    }

    ll k = y0_val / x0_val;
    // 令 P=x0*a, Q=x0*b，则 ab=k 且 gcd(a,b)=1。
    // 互质要求 k 的每个质因子幂整段给 a 或 b，共 2^ω(k) 个有序对。
    printf("%d\n", 1 << distinct_primes(k));
    return 0;
}
