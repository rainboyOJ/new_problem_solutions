/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 23:43
 */
// roj 1058 求一元二次方程
// 判别式 delta = b^2 - 4ac 的符号决定输出形态，delta > 0 时套求根公式并把两根排序。

#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long ll;

const double DELTA_EPS = 1e-12; // 判别式落在这个范围内视为 0，用于吸收浮点误差
const double ZERO_EPS = 1e-6;   // 根的绝对值小于它时按 0 输出，避免打印出 "-0.00000"

double a, b, c; // 方程 ax^2 + bx + c = 0 的三个系数

// 把 |x| < 1e-6 的根统一成 0：它们本来就显示为 0.00000，顺便去掉 -0.0 的负号
double no_negative_zero(double x) {
    if (fabs(x) < ZERO_EPS) {
        return 0.0;
    }
    return x;
}

void solve() {
    double delta = b * b - 4 * a * c;

    if (delta < -DELTA_EPS) { // 判别式显著为负：无实根
        printf("No answer!\n");
        return;
    }
    if (fabs(delta) < DELTA_EPS) { // 判别式在精度内视为 0：两个相等的实根
        double x = no_negative_zero(-b / (2 * a));
        printf("x1=x2=%.5f\n", x);
        return;
    }

    double root = sqrt(delta);
    double x1 = (-b + root) / (2 * a);
    double x2 = (-b - root) / (2 * a);
    if (x1 > x2) { // 题面要求根小者在先，直接交换保证顺序
        double t = x1;
        x1 = x2;
        x2 = t;
    }
    x1 = no_negative_zero(x1);
    x2 = no_negative_zero(x2);
    printf("x1=%.5f;x2=%.5f\n", x1, x2);
}

int main() {
    scanf("%lf%lf%lf", &a, &b, &c);
    solve();
    return 0;
}
