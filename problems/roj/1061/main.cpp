/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */
// main.cpp：读入 n 个整数，输出它们的和与均值（均值保留 5 位小数）。
#include <cstdio>

typedef long long ll;

int n;           // 整数个数（题面 1 ≤ n ≤ 10000，int 足够）
double total;    // 累加器；n·max(|a_i|) ≤ 1e8，double 精确表示无问题
double x;        // 当前读入的整数

int main() {
    // 读入 n，再循环 n 次累加
    std::scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        std::scanf("%lf", &x);
        total += x;
    }

    // 平均值 = 总和 / n；按题面要求保留 5 位小数
    std::printf("%.0f %.5f\n", total, total / n);
    return 0;
}