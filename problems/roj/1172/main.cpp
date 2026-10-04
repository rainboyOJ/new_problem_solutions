/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */

// 高精度阶乘：数组一位存一个十进制数字，每次乘 i 后统一进位。
#include <cstdio>

typedef long long ll;

const int MAXD = 40000; // 10000! 有 35660 位，开 40000 位足够

int a[MAXD]; // a[0] 是当前位数，a[1..a[0]] 从低位到高位存十进制数字
ll n;        // 题目数据用 ll

int main() {
    scanf("%lld", &n);

    a[0] = 1;
    a[1] = 1; // 初始值为 1，n = 0 时结果就是 1
    for (ll i = 2; i <= n; ++i) {
        // 先逐位乘 i，暂不处理进位
        for (int j = 1; j <= a[0]; ++j)
            a[j] = a[j] * i;
        // 统一进位：超过 10 的部分向高位推进
        for (int j = 1; j <= a[0]; ++j) {
            if (a[j] >= 10) {
                if (j == a[0])
                    a[a[0] + 1] = 0; // 最高位进位时位数加一
                a[j + 1] += a[j] / 10;
                a[j] %= 10;
                if (j == a[0])
                    ++a[0];
            }
        }
    }

    // 从最高位到最低位输出
    for (int j = a[0]; j >= 1; --j)
        printf("%d", a[j]);
    printf("\n");
    return 0;
}
