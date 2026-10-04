/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:06
 * update_at: 2026-10-05 04:06
 */
#include <cstdio>

typedef long long ll;

ll n; // 题目给的整数
ll k; // 要取从右往左数第 k 个数字（个位是第 1 个）

int main() {
    scanf("%lld %lld", &n, &k);
    // 第 k 位 = 先整除 10^(k-1) 砍掉低 k-1 位，再对 10 取余取出新的末位
    ll p = 1; // p 表示位权 10^(k-1)，用循环连乘算出
    for (ll i = 1; i <= k - 1; i++)
        p = p * 10;
    printf("%lld\n", (n / p) % 10);
    return 0;
}
