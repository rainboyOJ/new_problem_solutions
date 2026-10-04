/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:11
 * update_at: 2026-10-05 00:11
 */

// main.cpp：每个屋顶独立往返一次，累加航行时间与上下船时间，最后向上取整。
// 总时间 = Σ (2 * 距离 / 50 + 1.5 * 人数)，距离 = sqrt(x^2 + y^2)。

#include <cmath>
#include <cstdio>

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    double total = 0.0; // 累计所有屋顶救援总时间（分钟，含小数）
    for (int i = 0; i < n; ++i) {
        double x, y;
        int c; // 该屋顶人数
        scanf("%lf %lf %d", &x, &y, &c);
        double dist = std::sqrt(x * x + y * y); // 大本营到屋顶的欧氏距离（米）
        double sail = dist / 50.0;              // 单程航行时间（分钟），速度 50 米/分钟
        total += 2.0 * sail + 1.5 * c;          // 往返航行 + 上船 1 分钟/人 + 下船 0.5 分钟/人
    }
    // 向上取整：用 ceil 处理一般情况；当 total 几乎正整数时 ceil 仍给出正确整数值
    ll ans = (ll)std::ceil(total - 1e-9);
    printf("%lld\n", ans);
    return 0;
}