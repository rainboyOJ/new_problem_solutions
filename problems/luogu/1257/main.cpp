/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 13:00
 * update_at: 2026-08-05 13:00
 */
// 分治求最近点对：按 x 排序后递归，合并时只检查距分界线 d 以内的窄条，
// 窄条内按 y 排序后相邻比较（d×d 方块内最多常数个点，鸽巢原理）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

struct Point {
    long long x, y;
};

int n;
Point p[MAXN];    // 按 x 排序后的点
Point tmp[MAXN];  // 窄条内的点（按 y 排序）

bool cmp_x(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool cmp_y(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 两点距离（平方和用 long long 计算，避免 double 精度损失）
double dist(const Point& a, const Point& b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return sqrt((double)(dx * dx + dy * dy));
}

// 分治求 p[l..r] 内的最近点对距离
double solve(int l, int r) {
    if (r - l <= 2) {   // 点数 <= 3：直接暴力枚举
        double d = 1e100;
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++)
                d = min(d, dist(p[i], p[j]));
        return d;
    }

    int mid = (l + r) >> 1;
    double d = min(solve(l, mid), solve(mid + 1, r));

    // 合并：跨界点对若距离 < d，x 差必 < d，只收集距分界线 d 以内的点
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        long long dx = p[i].x - p[mid].x;
        if (dx < 0) dx = -dx;
        if (dx < d) tmp[cnt++] = p[i];
    }

    // 窄条内按 y 排序，每个点只检查 y 差 < d 的后继点
    // 鸽巢原理：候选点在 2d×d 矩形内，每侧内部的点互距 ≥ d，
    // 每侧装不下太多点，每个点 i 最多匹配约 6~7 次后继，不退化
    sort(tmp, tmp + cnt, cmp_y);
    for (int i = 0; i < cnt; i++)
        for (int j = i + 1; j < cnt && tmp[j].y - tmp[i].y < d; j++)
            d = min(d, dist(tmp[i], tmp[j]));

    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;

    sort(p + 1, p + n + 1, cmp_x);
    cout << fixed << setprecision(4) << solve(1, n) << '\n';

    return 0;
}
