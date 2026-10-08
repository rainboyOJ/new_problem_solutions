/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:24
 * update_at: 2026-10-08 22:26
 */
#include <cstdio>

typedef long long ll;

// 求 n 个 1992 的乘积的末两位：同余定理 (a*b) mod 100 = ((a mod 100)*(b mod 100)) mod 100
ll last_two_digits(ll n) {
    ll res = 1;                 // 乘法单位元（n = 0 时输出 1，该边界题面未定义、数据未覆盖）
    for (ll i = 1; i <= n; ++i) {
        res = res * 1992 % 100; // 步步取模，中间结果恒小于 100 * 1992，不会溢出
    }
    return res;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }
    // 真实数据按整数输出，不补前导零（n = 111 的答案文件是 "8" 而非 "08"）
    printf("%lld\n", last_two_digits(n));
    return 0;
}
