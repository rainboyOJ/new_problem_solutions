/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:06
 * update_at: 2026-10-04 23:06
 */
// main.cpp：计算 2^n（0 <= n < 31），输出整数结果。
// 关键点：1 << n 就是 1 后面跟 n 个 0 的二进制数，恰好等于 2^n。

#include <cstdio>

typedef long long ll; // 题目数据用 ll；本题 n < 31，ll 也足够表达 2^30

int main() {
    ll n;
    scanf("%lld", &n); // 读入单个整数 n
    printf("%lld\n", (ll)1 << n); // 左移 n 位得到 2^n，整数运算无浮点误差
    return 0;
}