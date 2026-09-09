/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 15:54
 * update_at: 2026-09-06 16:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const double EPS = 1e-9;

int n;
double x[MAXN], v[MAXN];

// 判断时间 T 内所有人能否赶到同一个点：
// 第 i 个人的可达区间是 [x_i - v_i*T, x_i + v_i*T]，
// 所有人能同时到达当且仅当这些区间的交非空。
bool check(double T) {
    double l = -1e18, r = 1e18;
    for (int i = 1; i <= n; i++) {
        l = max(l, x[i] - v[i] * T); // 所有区间左端点的最大值
        r = min(r, x[i] + v[i] * T); // 所有区间右端点的最小值
    }
    return l <= r + EPS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    double minx = 1e18, maxx = -1e18;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        minx = min(minx, x[i]);
        maxx = max(maxx, x[i]);
    }
    for (int i = 1; i <= n; i++) cin >> v[i];

    // 二分答案：时间 T 可行具有单调性。
    double lo = 0, hi = maxx - minx; // 速度至少为 1，时间上界取坐标跨度
    for (int step = 0; step < 100; step++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }

    printf("%.5f\n", lo);
    return 0;
}
