/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 15:54
 * update_at: 2026-09-06 16:00
 */
// brute.cpp：小数据暴力解，枚举全部候选聚会点，精确求出 f(p) 的最小值。
// f(p) = max_i |x_i - p| / v_i 是凸函数，最小值出现在两个 V 形的交点、
// 区间端点或某个 x_i 处，因此枚举这些候选点即可得到精确最小值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
double x[MAXN], v[MAXN];

// 计算在点 p 聚会时，最晚到达的时间。
double f(double p) {
    double t = 0;
    for (int i = 1; i <= n; i++) {
        t = max(t, fabs(x[i] - p) / v[i]);
    }
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++) cin >> v[i];

    double minx = x[1], maxx = x[1];
    for (int i = 2; i <= n; i++) {
        minx = min(minx, x[i]);
        maxx = max(maxx, x[i]);
    }

    vector<double> cand; // 候选聚会点
    cand.push_back(minx);
    cand.push_back(maxx);
    for (int i = 1; i <= n; i++) cand.push_back(x[i]);

    // 枚举每对 V 形函数的交点，三种位置关系各解一次方程。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // 两人同侧（p 在两者同一边）：p = (v_j x_i - v_i x_j) / (v_j - v_i)
            if (fabs(v[j] - v[i]) > 1e-12) {
                cand.push_back((v[j] * x[i] - v[i] * x[j]) / (v[j] - v[i]));
            }
            // 两人异侧（p 在两者之间）：p = (v_j x_i + v_i x_j) / (v_i + v_j)
            cand.push_back((v[j] * x[i] + v[i] * x[j]) / (v[i] + v[j]));
        }
    }

    double ans = 1e18;
    for (double p : cand) {
        if (p < minx || p > maxx) continue; // 最优聚点一定在坐标范围内
        ans = min(ans, f(p));
    }

    printf("%.5f\n", ans);
    return 0;
}
