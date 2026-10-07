/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 00:46
 * update_at: 2026-10-06 01:18
 */
#include <cstdio>
typedef long long ll;

// 阶乘规模 n<=500，第 n 个卡特兰数约 300 位十进制，用大整数手写高精度。
const ll BASE = 1000000000; // 大整数每段存 9 位十进制，方便输出
ll dig[1005];               // dig[0] 是最低位，dig[len-1] 是最高位
ll n;
int len;                    // 当前大整数的段数

// 大整数乘一个小整数 b
void big_mul(ll b) {
    ll carry = 0;
    for (int i = 0; i < len; i++) {
        ll cur = dig[i] * b + carry;
        dig[i] = cur % BASE;
        carry = cur / BASE;
    }
    while (carry > 0) {
        dig[len] = carry % BASE;
        carry /= BASE;
        len++;
    }
}

// 大整数除以一个小整数 b（保证能整除）
void big_div(ll b) {
    ll rem = 0; // 从高位向低位做竖式除法时的余数
    for (int i = len - 1; i >= 0; i--) {
        ll cur = rem * BASE + dig[i];
        dig[i] = cur / b;
        rem = cur % b;
    }
    while (len > 1 && dig[len - 1] == 0) {
        len--;
    }
}

// 按 10^9 进制逐段输出，除最高段外每段补足 9 位
void big_print() {
    printf("%lld", dig[len - 1]);
    for (int i = len - 2; i >= 0; i--) {
        printf("%09lld", dig[i]);
    }
    printf("\n");
}

int main() {
    scanf("%lld", &n);

    // 卡特兰数递推：C_{k+1} = C_k * 2*(2k+1) / (k+2)，起点 C_0 = 1
    dig[0] = 1;
    len = 1;
    for (ll k = 0; k < n; k++) {
        big_mul(2 * (2 * k + 1));
        big_div(k + 2);
    }
    big_print();

    return 0;
}
