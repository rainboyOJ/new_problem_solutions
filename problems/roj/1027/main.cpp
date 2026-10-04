/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:51
 * update_at: 2026-10-04 22:51
 */

#include <cstdio>

// 题面要求的四行输出对应 printf 的 %f、%.5f、%e、%g，
// 注意题面样例第三行写的是 3 位指数（旧编译器写法），
// 但标准 printf 与评测数据都是指数至少 2 位（如 1.234568e+01），按标准格式输出即可。
int main() {
    double x; // 读入的双精度浮点数
    scanf("%lf", &x);
    printf("%f\n", x);       // 定点小数，默认保留 6 位小数
    printf("%.5f\n", x);     // 定点小数，保留 5 位小数
    printf("%e\n", x);       // 科学计数法，尾数默认保留 6 位小数
    printf("%g\n", x);       // 6 位有效数字，定点/科学计数法自动选择并去尾零
    return 0;
}
