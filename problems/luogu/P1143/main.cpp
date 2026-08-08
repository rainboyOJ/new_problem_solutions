/**
 * P1143 进制转换
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const char DIGITS[] = "0123456789ABCDEF";

int main() {
    int src_base, dst_base;
    char num[40];
    scanf("%d%s%d", &src_base, num, &dst_base);
    // 任意进制 → 十进制
    int val = 0;
    for (int i = 0; num[i]; ++i) {
        char c = num[i];
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        val = val * src_base + d;
    }
    // 十进制 → 目标进制
    char ans[40];
    int len = 0;
    if (val == 0) ans[len++] = '0';
    while (val) {
        ans[len++] = DIGITS[val % dst_base];
        val /= dst_base;
    }
    for (int i = len - 1; i >= 0; --i) putchar(ans[i]);
    putchar('\n');
    return 0;
}
