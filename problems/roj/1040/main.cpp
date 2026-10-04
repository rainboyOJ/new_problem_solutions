/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:13
 * update_at: 2026-10-04 23:13
 */
#include <cstdio>
#include <cmath>

typedef long long ll;

double x; // 输入的浮点数，绝对值不超过 10000

int main() {
    scanf("%lf", &x);          // 读入一个浮点数
    x = fabs(x);              // 先取绝对值，避免负数格式化出 -0.00
    printf("%.2f\n", x);       // 保留两位小数，自动四舍五入并补零
    return 0;
}
