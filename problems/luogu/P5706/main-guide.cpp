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
    double total_ml = 0; // 饮料总量（毫升）
    int student_count = 0; // 同学人数
    std::cin >> total_ml >> student_count;

    // 每人分到的饮料 = 总量 ÷ 人数，保留 3 位小数
    std::cout << std::fixed << std::setprecision(3) << total_ml / student_count << '\n';
    // 每名同学需要 2 个杯子（fixed 只影响浮点数，整数仍原样输出）
    std::cout << student_count * 2 << '\n';
    return 0;
}
