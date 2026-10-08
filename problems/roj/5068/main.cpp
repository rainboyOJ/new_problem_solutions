/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:08
 * update_at: 2026-10-09 02:08
 */
// main.cpp：读入圆的半径，输出直径、周长、面积，各保留 4 位小数（一本通 2067 / ROJ 5068）。
//
// π 的取值是本题唯一的坑：题面没有写出 π，但同题源（一本通 1014、洛谷 B2014、
// OpenJudge 1.3-09）的官方题面都约定 π = 3.14159，且本题 10 个测试点正是用它生成的。
//   r = 3.0 时：2 × 3.14159 × 3 = 18.84954 → 18.8495；
//   若改用 M_PI / acos(-1)（真 π）得 18.8496，与 .out 不符 —— 实测换真 π 会挂 7 个点。
// 所以这里必须写死符号常量 3.14159，不能用 <cmath> 里的高精度常量。
#include <cstdio>

typedef long long ll; // 本题输入是实数，按项目规范保留 ll 别名

double r; // 圆的半径（题面未声明范围；同题源为 0 < r <= 10000）

// 按 d = 2r、c = 2πr、s = πr² 求出三个量并输出，数与数之间一个空格。
void solve() {
    if (scanf("%lf", &r) != 1) return; // 单组输入：一行一个实数半径

    const double PI = 3.14159; // 题源约定的圆周率，承重常量，勿改
    double d = 2.0 * r;        // 直径 d = 2r
    double c = 2.0 * PI * r;   // 周长 c = 2πr
    double s = PI * r * r;     // 面积 s = πr²

    printf("%.4f %.4f %.4f\n", d, c, s); // 各保留 4 位小数，末尾一个换行、无行尾空格
}

int main() {
    solve();
    return 0;
}
