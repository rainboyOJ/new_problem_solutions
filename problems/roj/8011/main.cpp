/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:51
 * update_at: 2026-10-06 16:51
 */

// 比赛从 11 月 11 日 11:11 开始，把起止时刻都换算成绝对分钟数后相减。

#include <cstdio>

typedef long long ll;

ll day, hour, minute; // 结束时刻：11 月第 day 天的 hour 时 minute 分

int main() {
    scanf("%lld %lld %lld", &day, &hour, &minute);
    // to_minute(D,H,M) = 自 11 月 1 日 00:00 起的绝对分钟数
    ll end_min = (day - 1) * 1440 + hour * 60 + minute;
    ll start_min = 10 * 1440 + 11 * 60 + 11; // 起点：11 月 11 日 11:11
    ll spent = end_min - start_min;
    if (spent < 0) // 结束早于开始
        printf("-1\n");
    else
        printf("%lld\n", spent);
    return 0;
}
