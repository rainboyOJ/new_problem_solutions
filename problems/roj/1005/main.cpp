/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:15
 * update_at: 2026-10-04 22:15
 */
#include <cstdio>

typedef long long ll;

ll x, a, y, b; // x 亿人生活 a 年，或 y 亿人生活 b 年

int main() {
    scanf("%lld%lld%lld%lld", &x, &a, &y, &b);

    // 设初始资源为 S、每年新增 r：S + a*r = x*a，S + b*r = y*b
    // 两式相减消去 S，得到 r = (y*b - x*a)/(b-a)，它正是最大可持续人口
    ll numerator = y * b - x * a;   // 总消耗之差
    ll denominator = b - a;         // 年数之差
    ll answer = numerator / denominator; // 标准程序按整型除法向零截断

    printf("%lld.00\n", answer);
    return 0;
}
