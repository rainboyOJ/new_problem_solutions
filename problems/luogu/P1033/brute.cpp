/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:06
 * update_at: 2026-11-11 00:06
 */
// brute.cpp：逐个枚举小球进行判定
#include <cmath>
#include <iostream>

using namespace std;

const double EPS = 1e-4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double H, S1, V, L, K;
    int n;
    if (!(cin >> H >> S1 >> V >> L >> K >> n)) return 0;

    double t1 = 0.0;
    if (H > K) {
        t1 = sqrt((H - K) / 5.0);
    }
    double t2 = sqrt(H / 5.0);

    double left_bound = S1 - V * t2 - EPS;
    double right_bound = S1 + L - V * t1 + EPS;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (i >= left_bound && i <= right_bound) {
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}
