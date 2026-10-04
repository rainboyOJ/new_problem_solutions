/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 22:30
 */

#include <cstdio>

// 并联电阻公式：R = 1/(1/r1 + 1/r2) = r1*r2/(r1+r2)，通分后少一次除法
int main() {
    double r1, r2; // 两个电阻的阻值，浮点型
    scanf("%lf%lf", &r1, &r2);
    double r = r1 * r2 / (r1 + r2);
    printf("%.2f\n", r); // 四舍五入并固定保留 2 位小数
    return 0;
}
