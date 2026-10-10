/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:20
 * update_at: 2026-10-09 07:37
 */
// ROJ 5074 三角形面积（一本通 2073）：给定三边 a、b、c，用海伦公式求面积，保留 3 位小数。
//   p = (a + b + c) / 2
//   s = sqrt(p * (p - a) * (p - b) * (p - c))
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long long ll;

double a, b, c; // 三边长，题面未给范围，用 double 读入（实测数据均为一位小数）

void solve() {
    if (!(cin >> a >> b >> c)) return;

    double p = (a + b + c) / 2.0;             // 半周长
    double s2 = p * (p - a) * (p - b) * (p - c); // 海伦公式的被开方项

    // 防御：退化/非法输入下 s2 可能算出 -0.0 或极小负数，直接开方会输出 nan；
    // 这里把 <=0 / -0.0 / NaN 一律归零。10 个测试点上该行从未触发（合法三角形恒 s2>0）。
    if (!(s2 > 0.0)) {
        s2 = 0.0;
    }

    cout << fixed << setprecision(3) << sqrt(s2) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
