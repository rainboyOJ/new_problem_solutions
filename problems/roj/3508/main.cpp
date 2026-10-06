/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:33
 * update_at: 2026-10-06 12:33
 */

#include <cstdio>

typedef long long ll;

// f(x) = a*x^3 + b*x^2 + c*x + d
double A, B, C, D;

// 计算多项式在 x 处的值（秦九韶）
double calc(double x) {
    return ((A * x + B) * x + C) * x + D;
}

int main() {
    scanf("%lf %lf %lf %lf", &A, &B, &C, &D);
    double last = 0;
    bool has_last = false; // 是否已经找到过一个根，用于间隔去重
    // 在 [-100,100] 上每 0.5 采样一次，两根之差 >= 1 保证每个小区间内至多一个根
    for (double x = -100.0; x < 100.0; x += 0.5) {
        double y1 = calc(x), y2 = calc(x + 0.5);
        if (y1 * y2 > 0) continue; // 同号，此区间无根
        // 二分变号区间 [x, x+0.5]，迭代足够多次把根逼到两位小数精度内
        double l = x, r = x + 0.5;
        for (int i = 1; i <= 100; ++i) {
            double mid = (l + r) / 2;
            if (calc(l) * calc(mid) <= 0)
                r = mid;
            else
                l = mid;
        }
        double root = (l + r) / 2;
        // 根间距 >= 1，与上一个根距离过近说明是同一个根，不重复输出
        if (has_last && root - last < 0.5) continue;
        printf("%.2f ", root);
        last = root;
        has_last = true;
    }
    printf("\n");
    return 0;
}
