/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:50
 * update_at: 2026-10-05 03:50
 */
// main.cpp：用格雷戈里级数在 x=1/sqrt(3) 处求 arctan(x)，乘 6 得 π 的近似值。

#include <cstdio>
#include <cmath>

typedef long long ll;

const double EPS = 1e-6; // 最后一项绝对值小于该阈值就停止累加

// 用交错级数求 arctan(x)：分子每步乘 -x^2 递推，分母取奇数
double arctanx(double x) {
    double term = x;   // 当前项的分子 x^(2k+1)，符号并入因子 -x^2
    double total = 0;  // 部分和
    double up = -x * x; // 相邻两项分子的比值 -x^2
    for (ll i = 1; ; i += 2) {
        if (fabs(term / i) < EPS) // 整项（含分母系数）小于阈值，停止
            break;
        total += term / i;
        term *= up; // 下一项分子：升幂同时变号
    }
    return total;
}

int main() {
    printf("%.10f\n", 6 * arctanx(1 / sqrt(3.0)));
    return 0;
}
