/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:23
 * update_at: 2026-10-04 23:23
 */

// 判断整数 n 能否同时被 3 和 5 整除：3 与 5 互质，等价于判断 n 能否被 lcm(3,5)=15 整除。
#include <cstdio>

typedef long long ll;

ll n; // 待判定的整数，范围 (-1000000, 1000000)，含负数与 0

int main() {
    scanf("%lld", &n);
    if (n % 15 == 0) printf("YES\n"); // 负数取余为 0 时同样表示整除，0 也是 15 的倍数
    else             printf("NO\n");
    return 0;
}
