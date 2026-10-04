/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:05
 * update_at: 2026-10-05 00:05
 */

#include <cstdio>

typedef long long ll;

ll k;      // 正整数的个数
ll cnt1;   // 1 出现的次数
ll cnt5;   // 5 出现的次数
ll cnt10;  // 10 出现的次数

int main() {
    scanf("%lld", &k);
    for (ll i = 1; i <= k; ++i) {
        ll x;
        scanf("%lld", &x);
        // 只统计三个目标值，其余数（如样例中的 8）一律忽略
        if (x == 1) cnt1++;
        if (x == 5) cnt5++;
        if (x == 10) cnt10++;
    }
    // 按 1、5、10 的固定顺序分三行输出
    printf("%lld\n%lld\n%lld\n", cnt1, cnt5, cnt10);
    return 0;
}
