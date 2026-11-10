/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:06
 * update_at: 2026-11-11 00:06
 */
#include <algorithm>
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

    // 小球下落到小车车顶高度所需时间 t1
    double t1 = 0.0;
    if (H > K) {
        t1 = sqrt((H - K) / 5.0);
    }

    // 小球下落到地面所需时间 t2
    double t2 = sqrt(H / 5.0);

    // 小车在有效时间区间 [t1, t2] 内扫过的水平空间范围 [left_bound, right_bound]
    // 此时小球水平位置处于该范围内即可被小车接住
    double left_bound = S1 - V * t2;
    double right_bound = S1 + L - V * t1;

    // 转换为离散小球下标的有效区间
    int i_min = static_cast<int>(ceil(left_bound - EPS));
    int i_max = static_cast<int>(floor(right_bound + EPS));

    // 与小球实际存在范围 [0, n - 1] 取交集
    i_min = max(0, i_min);
    i_max = min(n - 1, i_max);

    int ans = 0;
    if (i_min <= i_max) {
        ans = i_max - i_min + 1;
    }

    cout << ans << "\n";

    return 0;
}
