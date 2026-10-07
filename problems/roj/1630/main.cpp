/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:22
 * update_at: 2026-10-05 23:22
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

// 手写高精度：以 10^9 为一位，低位在前。
// 本题 A,B 最多 10^10000，约 1112 个 10^9 进制位，开 1200 足够。
const int BASE = 1000000000;
const int MAXL = 1200;

struct Big {
    int len;        // 有效位数（以 10^9 为一位，至少为 1）
    int a[MAXL];    // a[0] 是最低 9 位，依次向高位存
};

Big ga; // 第一个大数
Big gb; // 第二个大数

// 去掉高位多余的 0，零统一表示为 len = 1 且 a[0] = 0
void big_trim(Big &x) {
    while (x.len > 1 && x.a[x.len - 1] == 0) {
        x.len--;
    }
}

// 读入一个十进制大整数串，从低位开始每 9 个数字打包成一位
void big_read(Big &x) {
    string s;
    cin >> s;
    for (int i = 0; i < MAXL; i++) {
        x.a[i] = 0;
    }
    x.len = 0;
    int n = s.size();
    for (int end = n; end > 0; end -= 9) {
        int start = end - 9;
        if (start < 0) {
            start = 0;
        }
        int value = 0;
        for (int i = start; i < end; i++) {
            value = value * 10 + (s[i] - '0');
        }
        x.a[x.len] = value;
        x.len++;
    }
    big_trim(x);
}

bool big_is_zero(const Big &x) {
    return x.len == 1 && x.a[0] == 0;
}

// 十进制大数看最低位即可判断奇偶
bool big_is_even(const Big &x) {
    return x.a[0] % 2 == 0;
}

// x /= 2，从高位向低位处理，余数借给下一位
void big_div2(Big &x) {
    int carry = 0;
    for (int i = x.len - 1; i >= 0; i--) {
        int cur = x.a[i] + carry * BASE;
        x.a[i] = cur / 2;
        carry = cur % 2;
    }
    big_trim(x);
}

// x *= 2，从低位向高位进位
void big_mul2(Big &x) {
    int carry = 0;
    for (int i = 0; i < x.len; i++) {
        int cur = x.a[i] * 2 + carry;
        x.a[i] = cur % BASE;
        carry = cur / BASE;
    }
    if (carry > 0) {
        x.a[x.len] = carry;
        x.len++;
    }
}

// 返回 -1 / 0 / 1 表示 x < y / x == y / x > y
int big_cmp(const Big &x, const Big &y) {
    if (x.len != y.len) {
        return x.len < y.len ? -1 : 1;
    }
    for (int i = x.len - 1; i >= 0; i--) {
        if (x.a[i] != y.a[i]) {
            return x.a[i] < y.a[i] ? -1 : 1;
        }
    }
    return 0;
}

// x -= y，调用前保证 x >= y
void big_sub(Big &x, const Big &y) {
    int borrow = 0;
    for (int i = 0; i < x.len; i++) {
        int yv = (i < y.len) ? y.a[i] : 0;
        int cur = x.a[i] - yv - borrow;
        if (cur < 0) {
            cur += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        x.a[i] = cur;
    }
    big_trim(x);
}

void big_swap(Big &x, Big &y) {
    Big tmp = x;
    x = y;
    y = tmp;
}

// 高位直接输出，其余每位补足 9 位前导零
void big_print(const Big &x) {
    printf("%d", x.a[x.len - 1]);
    for (int i = x.len - 2; i >= 0; i--) {
        printf("%09d", x.a[i]);
    }
    printf("\n");
}

// Stein 二进制 GCD：只用去尾零（除 2）、比较和减法，避免高精度大数除法取模。
void solve() {
    big_read(ga);
    big_read(gb);
    if (big_is_zero(ga)) {
        big_print(gb);
        return;
    }
    if (big_is_zero(gb)) {
        big_print(ga);
        return;
    }

    int shift = 0; // 两数公共因子 2 的个数，最后再补回
    while (big_is_even(ga) && big_is_even(gb)) {
        big_div2(ga);
        big_div2(gb);
        shift++;
    }
    while (big_is_even(ga)) {
        big_div2(ga);
    }
    while (big_is_even(gb)) {
        big_div2(gb);
    }

    // 此后 ga 恒为奇数；每轮把 gb 去尾零到奇数，再用大减小
    while (!big_is_zero(gb)) {
        while (big_is_even(gb)) {
            big_div2(gb);
        }
        if (big_cmp(ga, gb) > 0) {
            big_swap(ga, gb);
        }
        big_sub(gb, ga);
    }

    while (shift > 0) {
        big_mul2(ga);
        shift--;
    }
    big_print(ga);
}

int main() {
    solve();
    return 0;
}
