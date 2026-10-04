/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:19
 * update_at: 2026-10-05 06:24
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef long long ll;

const double EPS = 1e-5; // 判根阈值：|f(x)| ≤ 1e-5 即认为是根

double a, b, c, d; // 一元三次方程 ax^3 + bx^2 + cx + d = 0 的系数

// 秦九韶形式求多项式在 x 处的取值
inline double f(double x) {
    return ((a * x + b) * x + c) * x + d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> d;

    double x = -100.0; // 从区间左端点开始，以 0.01 为步长向右扫描
    for (ll i = 0; i < 3; ++i) { // 依次找出三个根
        while (x - 100.0 <= EPS) {
            if (fabs(f(x)) <= EPS) {
                break; // 命中一个网格点根
            }
            x += 0.01;
        }
        double root = round(x * 100.0) / 100.0; // 把浮点误差拉回两位小数网格点
        if (i > 0) {
            cout << ' ';
        }
        cout << fixed << setprecision(2) << root;
        x += 0.01; // 跳过当前根所在网格点，继续寻找下一个根
    }
    cout << '\n';

    return 0;
}
