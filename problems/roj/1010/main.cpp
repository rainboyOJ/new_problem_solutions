/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:22
 * update_at: 2026-10-04 22:22
 */

#include <cstdio>

typedef long long ll;

// 题目数据：分子 a、分母 b（b != 0），范围不大，但按习惯用 ll
ll a, b;

int main() {
    scanf("%lld %lld", &a, &b);
    // 1.0 * a / b：真除法得到双精度浮点商（不能整除，整除会把小数部分截断）
    double x = 1.0 * a / b;
    // %.9f：固定保留 9 位小数，自动完成四舍五入、补零和负号输出，无需任何分支
    printf("%.9f\n", x);
    return 0;
}
