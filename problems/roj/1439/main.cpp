/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:08
 * update_at: 2026-10-05 01:08
 */

// 最优路线一定是三段：A ->X(在AB上)-> Y(在CD上)-> D。
// 固定下车点 X 时，总时间关于上车点参数 s 是凸函数，可以内层三分；
// T(t,s) 联合凸，对 s 取最小后 F(t) 仍凸，外层再对下车点参数 t 三分。
// 嵌套实数三分，O(log^2(1/eps)) 求最小时间。

#include <cstdio>
#include <cmath>

typedef long long ll;

double ax, ay, bx, by; // 线段 AB 两端坐标（A 是起点）
double cx, cy, dx, dy; // 线段 CD 两端坐标（D 是终点）
double P, Q, R;        // 分别是 AB 上、CD 上、平面上的移动速度

const int ROUND = 100; // 三分固定迭代轮数，(2/3)^100 远小于所需精度

// 两点间欧氏距离
double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// 走 A -> X(t) -> Y(s) -> D 的总时间
// t, s 分别是 X 在 AB 上、Y 在 CD 上的参数（0 是线段起点，1 是终点）
double total_time(double t, double s) {
    double px = ax + t * (bx - ax); // 下车点 X 的坐标
    double py = ay + t * (by - ay);
    double qx = cx + s * (dx - cx); // 上车点 Y 的坐标
    double qy = cy + s * (dy - cy);
    return dist(ax, ay, px, py) / P
         + dist(px, py, qx, qy) / R
         + dist(qx, qy, dx, dy) / Q;
}

// 固定下车点参数 t，对上车点参数 s 三分求最短时间
double inner_min(double t) {
    double lo = 0.0, hi = 1.0;
    for (int i = 1; i <= ROUND; ++i) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (total_time(t, m1) < total_time(t, m2))
            hi = m2;
        else
            lo = m1;
    }
    return total_time(t, (lo + hi) / 2);
}

// 外层对下车点参数 t 三分，求全程最短时间
double outer_min() {
    double lo = 0.0, hi = 1.0;
    for (int i = 1; i <= ROUND; ++i) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (inner_min(m1) < inner_min(m2))
            hi = m2;
        else
            lo = m1;
    }
    return inner_min((lo + hi) / 2);
}

int main() {
    scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
    scanf("%lf %lf %lf %lf", &cx, &cy, &dx, &dy);
    scanf("%lf %lf %lf", &P, &Q, &R);
    printf("%.2f\n", outer_min());
    return 0;
}
