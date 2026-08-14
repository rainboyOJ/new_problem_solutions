/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>
#include <iomanip>

int main() {
    int distance = 0; // 路程（米）
    int speed = 0;    // 速度（米/分钟）
    std::cin >> distance >> speed;

    // 步行时间向上取整，再加 10 分钟垃圾分类，就是路上总耗时
    int walk_minutes = (distance + speed - 1) / speed + 10;
    // 08:00 换算成分钟是 480，减去路上耗时得到最晚出门时间
    int leave_minutes = 480 - walk_minutes;
    if (leave_minutes < 0) {
        leave_minutes += 24 * 60; // 早于零点则加一整天，变成前一天的时间
    }

    // 商是小时、余数是分钟；setw(2) 保证不足两位时用 0 补足
    std::cout << std::setfill('0') << std::setw(2) << leave_minutes / 60 << ':'
              << std::setw(2) << leave_minutes % 60 << '\n';
    return 0;
}
