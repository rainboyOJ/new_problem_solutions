/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 19:14
 * update_at: 2026-10-05 00:49
 */
#include <cstdio>

typedef long long ll; // 题目数据统一用 long long，规模大时也足够

// 题面：求 x^0 + x^1 + ... + x^n，结果保留两位小数输出
// 思路：维护前缀积 p = x^k，从 p = 1 起步，每步 p *= x 再把 p 加进 sum
// 这样只需 n 次乘法，复杂度 O(n)
int main() {
    double x;   // x 在 float 范围内
    ll n;       // n <= 10^6，用 long long 安全
    if (scanf("%lf %lld", &x, &n) != 2) return 0;

    double sum = 0.0; // 部分和 S_k，按低次到高次的顺序累加
    double p = 1.0;   // 前缀积，初始为 x^0
    for (ll i = 0; i <= n; ++i) {
        sum += p;     // 把当前的 x^i 加进答案
        p *= x;       // 递推得到下一个前缀积 x^(i+1)
    }

    // 保留两位小数输出
    printf("%.2f\n", sum);
    return 0;
}
