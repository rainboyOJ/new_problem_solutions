/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:29
 * update_at: 2026-10-04 23:29
 */
#include <cstdio>

// 比较步行与骑车耗时：步行 s/1.2，骑车 s/3 + 50（找车开锁 27 秒 + 停车锁车 23 秒）。
// 两边同乘 6 消去分母：步行 5s，骑车 2s + 300，都成了整数，严格相等也能精确判断。
typedef long long ll;

const ll WALK_X6 = 5;        // 步行 1.2 m/s 的耗时 s/1.2，同乘 6 得 5s
const ll BIKE_X6 = 2;        // 骑车 3 m/s 的耗时 s/3，同乘 6 得 2s
const ll BIKE_OVERHEAD_X6 = 300; // 固定开销 50 秒，同乘 6 得 300

ll distance; // 这次办事要行走的距离，单位米

int main() {
    scanf("%lld", &distance);
    ll walk_x6 = WALK_X6 * distance;                 // 步行总耗时放大 6 倍
    ll bike_x6 = BIKE_X6 * distance + BIKE_OVERHEAD_X6; // 骑车总耗时放大 6 倍
    if (bike_x6 < walk_x6)
        printf("Bike\n");
    else if (bike_x6 == walk_x6) // 同乘正数不改大小关系，相等即题面的 All，临界距离为 100
        printf("All\n");
    else
        printf("Walk\n");
    return 0;
}
