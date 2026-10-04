/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:43
 * update_at: 2026-10-04 22:43
 */
// main.cpp：读入一个浮点数，四舍五入保留 3 位小数输出。
#include <cstdio>

int main() {
    double x; // 题面说单精度，双精度读取不会损失信息，且覆盖其全部范围
    scanf("%lf", &x);
    printf("%.3f\n", x); // %.3f 一次完成四舍五入、补零和负号输出
    return 0;
}
