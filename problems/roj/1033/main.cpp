/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:00
 * update_at: 2026-10-04 23:00
 */

#include <cstdio>
#include <cmath>

int main() {
    double xa, ya, xb, yb;
    std::scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);  // 一次读四个实数，容忍两行或一行
    double dx = xa - xb;
    double dy = ya - yb;
    double len = std::sqrt(dx * dx + dy * dy);  // 勾股定理求线段长度
    std::printf("%.3f\n", len);                  // 定点格式：四舍五入并补零到 3 位小数
    return 0;
}
