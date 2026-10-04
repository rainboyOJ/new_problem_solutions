/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:10
 * update_at: 2026-10-05 00:10
 */

#include <cstdio>

typedef long long ll;

ll budget[13];  // budget[i] = 第 i 个月的预算（i 从 1 到 12）
ll hand;        // 手中零钱（不足百元的部分）
ll saved;       // 存在妈妈那里的钱，始终是整百

int main() {
    for (ll month = 1; month <= 12; ++month) {
        scanf("%lld", &budget[month]);
    }

    for (ll month = 1; month <= 12; ++month) {
        // 月初领 300 元，实际花销恰好等于预算
        hand += 300 - budget[month];

        // 钱不够花：这个月就是第一个破产月，直接输出并结束
        if (hand < 0) {
            printf("%lld\n", -month);
            return 0;
        }

        // 预计月末还有 >=100 就把整百存进妈妈那里；不足百元时该式自动为 0
        saved += hand / 100 * 100;
        hand %= 100;
    }

    // 年末妈妈把存款加上 20% 还回来，用整数运算避免浮点误差
    printf("%lld\n", hand + saved * 6 / 5);
    return 0;
}
