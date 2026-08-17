/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:59
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double a;
    cin >> n >> a;

    // 统计落在圆内(含边界)的点的个数
    int inside = 0;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        // 半径 a 的圆内条件：x^2 + y^2 <= a^2，加小量吸收浮点误差
        if (x * x + y * y <= a * a + 1e-12) inside++;
    }

    // 蒙特卡洛估计：pi ≈ 4 * m / n，保留 6 位小数
    cout << fixed << setprecision(6) << 4.0 * inside / n << '\n';
    return 0;
}
