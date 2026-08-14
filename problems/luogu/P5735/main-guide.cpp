/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>
#include <cmath>
#include <iomanip>

// 计算两点之间的欧氏距离（勾股定理）
double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    // 三角形周长等于三条边的和
    double perimeter = dist(x1, y1, x2, y2)
                     + dist(x2, y2, x3, y3)
                     + dist(x3, y3, x1, y1);

    std::cout << std::fixed << std::setprecision(2) << perimeter;
    return 0;
}
