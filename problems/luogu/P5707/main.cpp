/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int s, v; // 距离（米），速度（米/分钟）
    cin >> s >> v;
    // 步行时间向上取整，加上垃圾分类 10 分钟
    int walk_time = (s + v - 1) / v + 10;
    // 08:00 对应第 480 分钟，减去所需时间得到最晚出门时间
    int latest = 480 - walk_time;
    if (latest < 0) {
        latest += 24 * 60; // 跨天时加一天的总分钟数
    }
    int hh = latest / 60; // 小时
    int mm = latest % 60; // 分钟
    printf("%02d:%02d\n", hh, mm);
    return 0;
}
