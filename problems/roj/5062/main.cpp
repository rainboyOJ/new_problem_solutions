/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 19:46
 * update_at: 2026-10-08 19:46
 */
// main.cpp：题面【输入】为（无），直接用题图标注的数据算梯形面积。
// 题图：梯形上底 a = 15、下底 b = 25；阴影三角形以 a 为底，顶点落在下底所在的直线上，
// 所以它的高就等于梯形的高 h。由 (1/2) * a * h = 150 解出 h，再套梯形面积公式。
#include <cstdio>

const double A = 15.0;       // 梯形上底（题图标注 15）
const double B = 25.0;       // 梯形下底（题图标注 25）
const double SHADED = 150.0; // 阴影三角形面积

void solve() {
    double h = SHADED * 2.0 / A;  // 阴影三角形的高，等于梯形的高
    double s = (A + B) * h / 2.0; // 梯形面积
    printf("%.2f\n", s);          // 保留两位小数，与评测数据逐字节一致
}

int main() {
    solve();
    return 0;
}
