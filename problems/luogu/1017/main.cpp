/**
 * P1017 [NOIP2000 提高组] 进制转换
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const char DIGITS[] = "0123456789ABCDEFGHIJ";

int main() {
    int n, base;
    scanf("%d%d", &n, &base);
    printf("%d=", n);
    char ans[40];
    int len = 0;
    if (n == 0) ans[len++] = '0';
    while (n) {
        int r = n % base;         // C++ 中 n % 负数 可能为负
        if (r < 0) r -= base;     // 调整余数为非负
        n = (n - r) / base;       // 重新计算商
        ans[len++] = DIGITS[r];
    }
    for (int i = len - 1; i >= 0; --i) putchar(ans[i]);
    printf("(base%d)\n", base);
    return 0;
}
