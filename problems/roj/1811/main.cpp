/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:55
 * update_at: 2026-10-08 04:55
 */
// 一本通 1811《多项式相乘》
// 题意：展开 (x+a_1)(x+a_2)...(x+a_n)，按题面写法统计展开式总长 t，输出 t mod 10000。
//   n=2: x^2+x(a_1+a_2)+a_1a_2        长度 16
//   n=3: x^3+x^2(a_1+a_2+a_3)+x(a_1a_2+a_1a_3+a_2a_3)+a_1a_2a_3  长度 40（题面样例）
// 计长规则：x/a/(/)/+ 各 1；指数的每个数字 1；下标的每个数字 1。'^' 不计长；
//   x^1 只写 x；常数项不写 x、不带括号。
//
// 记 d(i) 为 i 的十进制位数，D = sum_{i=1}^{n} d(i)。展开化简后总长满足闭形式：
//   t(n) = 2^{n-1} * (n + D) + 2^n + 3n + D - 4
// 于是只需快速幂求 2^{n-1}、2^n mod 10000，并按十进制位数分段求 D，整体 O(log n)。
#include <cstdio>

typedef long long ll;

const int MOD = 10000; // 题面要求对 10000 取余

// 快速幂：底数 b、指数 e，返回 b^e mod m
ll power_mod(ll b, ll e, ll m)
{
    ll result = 1 % m;
    b %= m;
    while (e > 0) {
        if (e & 1LL) {
            result = result * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return result;
}

// 按十进制位数分段统计 D = sum_{i=1}^{n} d(i) mod MOD
// 第 len 位数的区间是 [10^{len-1}, 10^len - 1]，与 [1, n] 取交集后整段相加
ll digit_length_sum(ll n)
{
    ll sum_len = 0;
    ll low = 1;                                  // 当前位数段的起点
    for (int len = 1; len <= 18 && low <= n; len++) {
        ll high = low * 10 - 1;                  // 该位数段的终点（可能超过 n）
        if (high > n) {
            high = n;
        }
        ll cnt = high - low + 1;                 // 这一段落在 [1, n] 内的整数个数
        sum_len = (sum_len + cnt % MOD * len) % MOD;
        low = high + 1;
    }
    return sum_len;
}

int main()
{
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    ll digit_sum = digit_length_sum(n);          // D mod MOD
    ll n_mod = n % MOD;
    ll p_half = power_mod(2, n - 1, MOD);        // 2^{n-1} mod MOD（n >= 1，指数非负）
    ll p_full = power_mod(2, n, MOD);            // 2^n mod MOD

    // t(n) = 2^{n-1}(n + D) + 2^n + 3n + D - 4，逐项在模 10000 下累加
    ll answer = p_half * ((n_mod + digit_sum) % MOD) % MOD;
    answer = (answer + p_full) % MOD;
    answer = (answer + 3 * n_mod) % MOD;
    answer = (answer + digit_sum) % MOD;
    answer = (answer - 4 + MOD) % MOD;           // 结尾的 -4，加 MOD 防负数

    printf("%lld\n", answer);
    return 0;
}
