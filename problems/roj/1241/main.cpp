/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:30
 * update_at: 2026-10-05 06:30
 */
#include <cstdio>

// 用秦九韶（Horner）形式计算 f(x)，只需常数次乘加，避免高次幂的浮点误差放大
double f(double x) {
    return ((((x - 15) * x + 85) * x - 225) * x + 274) * x - 121;
}

int main() {
    // 题面保证 f(1.5) > 0 > f(2.4)，且区间内有唯一根，直接以此为初始区间
    double left = 1.5, right = 2.4;

    // 终止条件写在区间宽度上：每轮减半，40 轮后区间宽 < 1e-12，
    // 取中点误差 <= 5e-13，远小于 6 位小数要求的 5e-7
    const double EPS = 1e-12;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (f(mid) > 0)
            left = mid; // f(mid) > 0：中点在根左侧，保留右半区间
        else
            right = mid; // f(mid) <= 0：中点越过根，保留左半区间
    }

    printf("%.6f\n", (left + right) / 2);
    return 0;
}
