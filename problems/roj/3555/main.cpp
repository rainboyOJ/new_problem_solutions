/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:51
 * update_at: 2026-10-06 13:51
 */
#include <cstdio>

typedef long long ll;

const int MAXL = 70; // n=200 时 2^201-2 约有 61 位十进制，开 70 位足够
const int BASE = 10; // 每位存一个十进制数字

int len;         // 高精度数的位数
int dig[MAXL];   // dig[i] 表示 10^i 位上的数字

// 高精度乘 2：直接按位翻倍再处理进位
void mul2() {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int cur = dig[i] * 2 + carry;
        dig[i] = cur % BASE;
        carry = cur / BASE;
    }
    if (carry > 0) {
        dig[len] = carry;
        len++;
    }
}

int main() {
    ll n; // 盘子的种类数
    scanf("%lld", &n);

    // 答案为 2^(n+1) - 2：先存数字 1，再乘 n+1 次 2
    dig[0] = 1;
    len = 1;
    for (ll i = 0; i <= n; i++) mul2();

    // 减 2（结果保证非负，因为 n >= 1 时 2^(n+1) >= 4）
    dig[0] -= 2;
    for (int i = 0; i < len; i++) {
        if (dig[i] < 0) {
            dig[i] += BASE;
            dig[i + 1] -= 1;
        }
    }
    while (len > 1 && dig[len - 1] == 0) len--; // 去掉前导零

    for (int i = len - 1; i >= 0; i--) printf("%d", dig[i]);
    printf("\n");
    return 0;
}
