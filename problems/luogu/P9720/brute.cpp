/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:45
 */
// brute.cpp：小数据暴力解，把每一步传送都看成一个选择来递归枚举。
// 第 dep 层选择这一次传送走哪个方向：0 = 公园 -> 地图，1 = 地图 -> 公园
// （只有当前点确实在地图上时，方向 1 才合法）。
//
// 枚举出从 s、从 t 出发各自能到达的所有 (点, 传送次数)，再挑两个点：
//   传送次数之和 <= n 时，答案为 两点距离 + k * 总传送次数。
// 因为任意一段走路都可以视为“两边各自传送结束后剩下的那段直线”。
// 序列数量是 2^n，只适合 n 很小的对拍数据。
#include <bits/stdc++.h>
using namespace std;

const long double INF = 1e30L;
const int MAXP = 5000; // n <= 10 时每侧最多 2^11 个端点，足够

struct Point {
    long double x, y;
};

Point operator+(Point a, Point b) { Point c; c.x = a.x + b.x; c.y = a.y + b.y; return c; }
Point operator-(Point a, Point b) { Point c; c.x = a.x - b.x; c.y = a.y - b.y; return c; }
Point operator*(long double t, Point a) { Point c; c.x = t * a.x; c.y = t * a.y; return c; }

long double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

Point park[5]; // 公园的四个角
Point mp[5];   // 地图的四个角
Point s, t;
int k, n;

long double dist(Point a, Point b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

// 公园 -> 地图：把 p 在公园正交基下分解，再用地图的正交基还原。
Point to_map(Point p) {
    Point o1 = park[1], e1 = park[4] - park[1], e2 = park[2] - park[1];
    Point o2 = mp[1],   f1 = mp[4] - mp[1],     f2 = mp[2] - mp[1];
    long double c1 = dot(p - o1, e1) / dot(e1, e1);
    long double c2 = dot(p - o1, e2) / dot(e2, e2);
    return o2 + c1 * f1 + c2 * f2;
}

// 地图 -> 公园：把 q 在地图正交基下分解，再用公园的正交基还原。
Point to_park(Point q) {
    Point o1 = park[1], e1 = park[4] - park[1], e2 = park[2] - park[1];
    Point o2 = mp[1],   f1 = mp[4] - mp[1],     f2 = mp[2] - mp[1];
    long double c1 = dot(q - o2, f1) / dot(f1, f1);
    long double c2 = dot(q - o2, f2) / dot(f2, f2);
    return o1 + c1 * e1 + c2 * e2;
}

// p 是否在地图上（含边界）：系数落在 [0, 1] 内即可。
bool in_map(Point p) {
    Point o2 = mp[1], f1 = mp[4] - mp[1], f2 = mp[2] - mp[1];
    long double c1 = dot(p - o2, f1) / dot(f1, f1);
    long double c2 = dot(p - o2, f2) / dot(f2, f2);
    long double eps = 1e-9L;
    return c1 >= -eps && c1 <= 1 + eps && c2 >= -eps && c2 <= 1 + eps;
}

Point rp[2][MAXP]; // 两个起点各自的端点
int rd[2][MAXP];   // 到达该端点的传送次数
int rcnt[2];

// 收集从 start 出发、最多用 n 次传送能到达的所有端点。
void collect(Point start, int id) {
    Point layer[MAXP]; // 当前层（恰好用了 step 次传送）的点
    int ln = 1;
    layer[0] = start;
    rcnt[id] = 0;
    rp[id][rcnt[id]] = start;
    rd[id][rcnt[id]] = 0;
    rcnt[id]++;

    for (int step = 1; step <= n; step++) {
        Point nl[MAXP];
        int nn = 0;
        for (int i = 0; i < ln; i++) {
            Point p = layer[i];
            // 选择 0：公园 -> 地图，任何位置都合法
            Point q = to_map(p);
            nl[nn++] = q;
            rp[id][rcnt[id]] = q;
            rd[id][rcnt[id]] = step;
            rcnt[id]++;
            // 选择 1：地图 -> 公园，只有点在地图上时才合法
            if (in_map(p)) {
                Point w = to_park(p);
                nl[nn++] = w;
                rp[id][rcnt[id]] = w;
                rd[id][rcnt[id]] = step;
                rcnt[id]++;
            }
        }
        for (int i = 0; i < nn; i++) layer[i] = nl[i];
        ln = nn;
    }
}

void solve() {
    for (int i = 1; i <= 4; i++) {
        cin >> park[i].x >> park[i].y;
    }
    for (int i = 1; i <= 4; i++) {
        cin >> mp[i].x >> mp[i].y;
    }
    cin >> s.x >> s.y >> t.x >> t.y;
    cin >> k >> n;

    collect(s, 0);
    collect(t, 1);

    long double ans = dist(s, t); // 一次也不传送
    for (int i = 0; i < rcnt[0]; i++) {
        for (int j = 0; j < rcnt[1]; j++) {
            int used = rd[0][i] + rd[1][j];
            if (used > n) continue;
            long double cost = dist(rp[0][i], rp[1][j]) + (long double)k * used;
            if (cost < ans) ans = cost;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
