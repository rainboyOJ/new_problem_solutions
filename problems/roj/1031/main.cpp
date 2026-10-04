/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:00
 * update_at: 2026-10-04 23:00
 */
#include <cstdio>

typedef long long ll;

ll n; // 输入的数（题面是三位数，逐段公式对更长输入与负数也成立）

int main() {
    scanf("%lld", &n);
    // "反向"直译成三段公式：个位段 n%10、十位段 (n/10)%10、剩余高位段 n/100
    // 逐段打印天然保留前导零（100 -> 001）
    // C 的 /、% 向零截断，负数时三段各带负号（-444 -> -4-4-4），无需额外处理
    printf("%lld%lld%lld\n", n % 10, (n / 10) % 10, n / 100);
    return 0;
}
