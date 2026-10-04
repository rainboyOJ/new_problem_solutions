/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:54
 * update_at: 2026-10-05 06:54
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double EPS = 1e-12; // 二分终止精度，远超三位小数输出要求

double L, n, C;  // 木棍原长、温度变化、热膨胀系数

// 输入为一个浮点数序列，直接读入即可。
void read_input() {
    cin >> L >> n >> C;
}

// 核心：弧长 L' = (1+n*C)*L 固定，弦长 = L 固定，圆心角 θ 唯一。
// 由 r = L'/θ 与 L = 2*r*sin(θ/2) 消去 r，得到方程 2*L'*sin(θ/2)/θ = L。
// 左端在 (0,π] 严格递减，且 g(0+) = L' ≥ L，g(π) < L，故可二分 θ。
void solve() {
    double expanded = (1.0 + n * C) * L; // 受热后的弧长 L'

    double lo = 0.0, hi = 3.15; // 上界略大于 π 即可
    while (hi - lo > EPS) {
        double mid = (lo + hi) / 2.0;
        double chord = 2.0 * expanded * sin(mid / 2.0) / mid; // 当前 θ 对应的弦长
        if (chord > L) {
            lo = mid; // 弦偏长 => 还不够弯 => 角度调大
        } else {
            hi = mid; // 弦偏短/相等 => 角度调小
        }
    }

    double theta = hi;            // 最终圆心角
    double radius = expanded / theta; // 半径 r = L'/θ
    double h = radius * (1.0 - cos(theta / 2.0)); // 弓形高 = r - r*cos(θ/2)

    cout << fixed << setprecision(3) << h << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
