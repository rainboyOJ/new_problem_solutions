/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:51
 * update_at: 2026-10-04 22:51
 */
// main.cpp：读入球半径，按题面给定的 π=3.14 计算球体积，保留 2 位小数输出。
#include <cstdio>

typedef long long ll;

const double PI = 3.14; // 题面明确要求取 3.14，不能用 acos(-1) 等高精度 π

int main() {
    double radius; // 球半径，题面说明类型为 double，且不超过 100
    scanf("%lf", &radius);

    double volume = 4.0 / 3.0 * PI * radius * radius * radius; // V = 4/3·π·r³

    printf("%.2f\n", volume); // 保留 2 位小数，不足补 0

    return 0;
}
