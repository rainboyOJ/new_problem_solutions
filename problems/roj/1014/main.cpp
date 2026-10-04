/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 22:30
 */
// main.cpp：读入圆的半径，按题面给定的圆周率输出直径、周长、面积，各保留 4 位小数。
#include <cstdio>

double r; // 圆的半径

int main() {
    scanf("%lf", &r);

    double pi = 3.14159;               // 题面钦定的圆周率，不能用 math 的高精度常量
    double diameter = 2 * r;           // 直径 d = 2r
    double circumference = 2 * pi * r; // 周长 C = 2πr
    double area = pi * r * r;          // 面积 S = πr²

    printf("%.4f %.4f %.4f\n", diameter, circumference, area);
    return 0;
}
