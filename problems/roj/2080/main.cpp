/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:58
 * update_at: 2026-10-06 11:58
 */

// 思路：电线总是连到电网（线段）上离电源最近的点，所以电线总长 g(P) 是 F 个
// "点到线段距离"之和。线段是凸集，凸集上的距离函数是凸函数，凸函数的和仍然凸，
// 并且"固定 x 后对 y 取最小"得到的边缘函数 h(x) 也凸，于是可以嵌套三分：
// 外层对 x 三分（比较的是 h(m1) 与 h(m2)，即整条竖线上的最小值），
// 内层固定 x 对 y 三分求出 h。TERN 轮后区间长 100*(2/3)^T，精度远超一位小数。

#include <cmath>
#include <cstdio>

typedef long long ll;

const double BOUND = 100.0; // 题给坐标范围，最优点必落在 [0,100]^2 内：沿轴投影回去每段距离只会变小
const int TERN = 60;        // 三分轮数：100*(2/3)^60 ≈ 2.7e-9，远小于输出要求的 0.1

const int MAXF = 155;

// 每段电网的两个端点坐标（与坐标轴平行，端点是整数）
double ax[MAXF], ay[MAXF], bx[MAXF], by[MAXF];
ll F; // 电网段数（题面的 F）

// 点 (px, py) 到线段 AB 的距离：投影参数 t 夹回 [0,1] 得到线段上的最近点
double seg_dist(double px, double py, ll i) {
    double dx = bx[i] - ax[i];
    double dy = by[i] - ay[i];
    double length2 = dx * dx + dy * dy;
    if (length2 == 0) { // 退化成点的线段：垂足公式会除零，直接返回点距
        return sqrt((px - ax[i]) * (px - ax[i]) + (py - ay[i]) * (py - ay[i]));
    }
    double t = ((px - ax[i]) * dx + (py - ay[i]) * dy) / length2;
    if (t < 0) t = 0;      // 夹紧到线段内部：这是"点到线段"而非"点到直线"的距离
    if (t > 1) t = 1;
    double qx = ax[i] + t * dx;
    double qy = ay[i] + t * dy;
    return sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));
}

// g(x, y)：电源放在 (x, y) 时需要的电线总长，即到每段电网的距离之和
double total_length(double x, double y) {
    double sum = 0;
    for (ll i = 0; i < F; i++) sum += seg_dist(x, y, i);
    return sum;
}

// 内层三分：固定 x = fx，在 y ∈ [0,100] 上找 g 的最小值，返回最优的 y
// 凸性保证较小内点函数值更小时，最小值点不会在较大内点的右侧
double best_on_line(double fx) {
    double lo = 0, hi = BOUND;
    for (int it = 0; it < TERN; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (total_length(fx, m1) < total_length(fx, m2))
            hi = m2;
        else
            lo = m1;
    }
    return (lo + hi) / 2;
}

// h(x)：固定 x = fx 的整条竖线上电线总长的最小值
double on_line_min(double fx) {
    double y = best_on_line(fx);
    return total_length(fx, y);
}

int main() {
    scanf("%lld", &F);
    for (ll i = 0; i < F; i++) {
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        ax[i] = x1; ay[i] = y1; bx[i] = x2; by[i] = y2;
    }

    // 外层三分：h 是凸的（凸函数的边缘最小化仍凸），比较对象是整条竖线上的最小值
    double lo = 0, hi = BOUND;
    for (int it = 0; it < TERN; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (on_line_min(m1) < on_line_min(m2))
            hi = m2;
        else
            lo = m1;
    }
    double x = (lo + hi) / 2;
    double y = best_on_line(x);

    printf("%.1f %.1f %.1f\n", x, y, total_length(x, y));
    return 0;
}
