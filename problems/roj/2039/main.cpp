/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:11
 * update_at: 2026-10-06 10:11
 */
// main.cpp：模拟竖式长除法，把分数 N/D 化成小数并标记循环节。
#include <cstdio>

typedef long long ll;

const int MAXD = 100005;

int seen[MAXD];    // seen[r] = 余数 r 第一次出现时已写出的小数位数（-1 表示还没出现）
char digits[MAXD]; // 小数点后依次写出的每一位数字
ll cnt;            // 已写出的小数位数

ll n, d;

int main() {
    scanf("%lld %lld", &n, &d);
    for (ll i = 0; i < d; i++) seen[i] = -1;

    ll r = n % d; // 长除法当前余数，余数决定之后的所有商位
    ll k = -1;    // 循环节起点：余数重复时等于它第一次出现的位置，-1 表示除尽
    while (r != 0) {
        if (seen[r] != -1) { // 这个余数出现过，之后每一步都会重复
            k = seen[r];
            break;
        }
        seen[r] = cnt;      // 登记余数出现时已写出的位数
        r = r * 10;
        digits[cnt++] = '0' + r / d; // 本位商
        r = r % d;
    }

    // 组装完整输出串：整数部分 + '.' + 小数部分（循环节加括号）
    char ans[MAXD + 30];
    ll len = snprintf(ans, sizeof(ans), "%lld.", n / d);
    if (k == -1) {
        if (cnt == 0) ans[len++] = '0'; // 整数情形必须写成 x.0
        for (ll i = 0; i < cnt; i++) ans[len++] = digits[i];
    } else {
        for (ll i = 0; i < k; i++) ans[len++] = digits[i]; // 不循环部分
        ans[len++] = '(';
        for (ll i = k; i < cnt; i++) ans[len++] = digits[i]; // 循环节
        ans[len++] = ')';
    }
    ans[len] = '\0';

    // 每 76 个字符一行输出（换行符不占 76 个字符的名额）
    for (ll i = 0; i < len; i++) {
        putchar(ans[i]);
        if ((i + 1) % 76 == 0) putchar('\n');
    }
    putchar('\n');
    return 0;
}
