/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    double a, b, c; // 三角形三边长度
    std::cin >> a >> b >> c;
    // 海伦公式：先算半周长 p，再求面积
    double p = (a + b + c) / 2;
    double area = std::sqrt(p * (p - a) * (p - b) * (p - c));
    // 题面要求保留 1 位小数，用 fixed 固定小数位数输出
    std::cout << std::fixed << std::setprecision(1) << area << '\n';
    return 0;
}
