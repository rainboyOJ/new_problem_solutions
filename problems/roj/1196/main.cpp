/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:18
 * update_at: 2026-10-05 05:18
 */

#include <cstdio>
typedef long long ll;

// 终点（最后一步的落点）总在最高的一行上，且该行被踩的格子是一段连续区间，落点是区间端点。
// fresh  ：本行只有落点这一格，向北/东/西都是新格子，共 3 种走法；
// walked ：本行已横走过一段，落点是端点，只剩向北 + 唯一一侧横走，共 2 种走法。
ll fresh;  // 走 k 步后落点在「本行只有一格」状态的方案数
ll walked; // 走 k 步后落点在「本行已横走成一段」状态的方案数

int main() {
    ll n; // 允许行走的步数，n <= 20
    scanf("%lld", &n);
    // 初值：还没走时只有起点，本行只有它自己
    fresh = 1;
    walked = 0;
    for (ll i = 1; i <= n; i++) {
        // 向北都踏入全新一行（两类都变 fresh）；fresh 有 2 种横走、walked 只剩 1 种，横走都变 walked
        ll nf = fresh + walked;   // 3 种走法里 1 种向北变 fresh：a' = a + b
        ll nw = 2 * fresh + walked; // 2 种横走变 walked：b' = 2a + b
        fresh = nf;
        walked = nw;
    }
    printf("%lld\n", fresh + walked);
    return 0;
}
