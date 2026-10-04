/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 22:30
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double x, a, b, c, d; // x 与多项式系数 a、b、c、d

// 计算三次多项式 f(x) = ax^3 + bx^2 + cx + d 的值
double poly_value() {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> x >> a >> b >> c >> d; // 题面首个实数是 x
    cout.setf(ios::fixed);
    cout << setprecision(7) << poly_value() << "\n";
    return 0;
}
