/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:57
 * update_at: 2026-10-04 23:57
 */
// main.cpp：闭区间 [m, n] 内奇数求和。
// 关键观察：[m,n] 内的奇数构成公差为 2 的等差数列，故可用闭式求和。
// 端点收缩：m 偶则 +1 得首项，n 偶则 -1 得末项；其余原样保留。

#include <cstdio>

typedef long long ll;

ll m, n;       // 输入的两个端点
ll first;      // 区间内第一个奇数（首项）
ll last;       // 区间内最后一个奇数（末项）
ll cnt;        // 奇数项数，等差数列项数；区间内无奇数时自然为 0
ll sum;        // 等差数列求和结果

int main() {
    scanf("%lld %lld", &m, &n);
    first = (m & 1) ? m : m + 1;          // m 偶则右移一位得到第一个奇数
    last  = (n & 1) ? n : n - 1;          // n 偶则左移一位得到最后一个奇数
    cnt   = (last - first) / 2 + 1;       // 项数公式；(last<first) 时也为 0
    sum   = (first + last) * cnt / 2;     // 等差数列求和：first+last 恒偶，整除无损
    printf("%lld\n", sum);
    return 0;
}