/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:11
 * update_at: 2026-10-05 04:11
 */

// 大整数加法：两个不超过 200 位的非负整数相加（输入可能带前导 0）。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 205;

char sa[MAXN], sb[MAXN]; // 两个大整数的字符串形式
int a[MAXN], b[MAXN], c[MAXN]; // a、b 按位存数字（低位在前），c 存结果
ll la, lb, lc; // 三个数的长度

int main() {
    scanf("%s%s", sa, sb);
    la = strlen(sa);
    lb = strlen(sb);

    // 逆序逐位转成数字，低位存在下标 0
    for (ll i = 0; i < la; i++) a[i] = sa[la - 1 - i] - '0';
    for (ll i = 0; i < lb; i++) b[i] = sb[lb - 1 - i] - '0';

    // 竖式加法：从低位到高位逐位相加，carry 进位只可能是 0 或 1
    ll carry = 0;
    ll len = la > lb ? la : lb;
    for (ll i = 0; i < len; i++) {
        ll s = carry;
        if (i < la) s += a[i];
        if (i < lb) s += b[i];
        c[i] = s % 10;
        carry = s / 10;
    }
    lc = len;
    if (carry) { // 最高位还有进位，位数多一位
        c[lc] = 1;
        lc++;
    }

    // 去掉结果的前导 0（注意全 0 结果要留一个 0）
    while (lc > 1 && c[lc - 1] == 0) lc--;

    // 逆序输出即为正确书写顺序
    for (ll i = lc - 1; i >= 0; i--) printf("%d", c[i]);
    printf("\n");
    return 0;
}
