/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:11
 * update_at: 2026-10-06 13:11
 */

#include <cstdio>

typedef long long ll;

const ll MONTHLY_ALLOWANCE = 300; // 妈妈每月月初给的零花钱
const ll DEPOSIT_LINE = 100;      // 月末结余达到这个数才把整百存出去
const ll BONUS_RATE = 5;          // 年末利息 20% = 1/5，本金是 100 的倍数，整除即可

ll budget[13]; // budget[m] 表示第 m 个月的预算

int main() {
    for (int m = 1; m <= 12; m++) {
        scanf("%lld", &budget[m]);
    }

    ll hand = 0;  // 津津手中现金
    ll saved = 0; // 存在妈妈那里的本金（年末前取不出）

    for (int m = 1; m <= 12; m++) {
        hand += MONTHLY_ALLOWANCE; // 月初先拿到零花钱
        if (hand < budget[m]) {    // 手里的钱不够这个月的原定预算
            printf("%d\n", -m);    // 输出第一个出问题的月份
            return 0;
        }
        hand -= budget[m]; // 按预算花完，得到月末结余

        ll deposit = hand / DEPOSIT_LINE * DEPOSIT_LINE; // 结余不足 100 时整除结果为 0，自动不存
        hand -= deposit;
        saved += deposit;
    }

    // 年末：妈妈还回本金加 20% 利息，再加上自己手里的现金
    printf("%lld\n", hand + saved + saved / BONUS_RATE);
    return 0;
}
