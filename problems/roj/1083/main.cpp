/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:33
 */

#include <cstdio>

typedef long long ll;

// 星期表按 Monday 开头存放：下标 r-1 对应"过 r 天"后的星期
// r = 0 时下标 -1，week[-1] 在 C++ 中不合法，所以单独特判成 Sunday
const char *week[6] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

ll a, b; // 题目输入：底数 a，指数 b

int main() {
    scanf("%lld %lld", &a, &b);

    // 快速幂求 a^b mod 7：把 b 按二进制位拆开，边乘边取模，中间值不会膨胀
    ll r = 1 % 7; // 注意 b 可能为 0 的写法习惯；本题 b>=1，1%7=1
    ll base = a % 7;
    while (b > 0) {
        if (b & 1) r = r * base % 7;
        base = base * base % 7;
        b >>= 1;
    }

    if (r == 0)
        printf("Sunday\n"); // a^b 是 7 的整数倍，正好过了整数个星期
    else
        printf("%s\n", week[r - 1]);
    return 0;
}
