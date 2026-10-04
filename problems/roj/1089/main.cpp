/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-05 00:41
 */
// main.cpp：把整数 N 的数位顺序反转；负号不参与反转，末尾零反转后的前导零会被自然丢弃。
#include <cstdio>

typedef long long ll;

int main() {
    ll n;
    scanf("%lld", &n);

    // 负号单独摘出来，反转只对 |n| 的数位做，最后拼回去。
    ll sign = (n < 0) ? -1 : 1;
    ll v = (n < 0) ? -n : n;

    // 数位反转：r = r * 10 + v % 10，再把 v 砍掉最低位；末位 0 自然不会进入 r。
    ll r = 0;
    while (v > 0) {
        r = r * 10 + v % 10;
        v /= 10;
    }

    // N == 0 时循环没跑，r 仍是 0，正好符合题面"原数为零则结果为零"。
    printf("%lld\n", sign * r);
    return 0;
}
