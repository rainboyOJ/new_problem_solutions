/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:43
 * update_at: 2026-10-04 22:43
 */
#include <cstdio>

double x; // 读入的双精度浮点数

int main() {
    scanf("%lf", &x);
    // %.12f 按 x 的精确二进制值四舍五入到 12 位小数，小数位不足自动补 0，负号自动保留
    printf("%.12f\n", x);
    return 0;
}
