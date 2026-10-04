/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:00
 * update_at: 2026-10-04 23:00
 */
#include <cstdio>
#include <cmath>

typedef long long ll;

double xa, ya, xb, yb, xc, yc; // 三角形三个顶点的坐标

int main() {
    scanf("%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc);

    // 把顶点 A 平移到原点，两向量叉积的绝对值等于平行四边形面积，一半即三角形面积
    double cross = (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya);
    double area = fabs(cross) / 2.0;

    printf("%.2f\n", area); // 固定两位小数，四舍五入并自动补 0

    return 0;
}
