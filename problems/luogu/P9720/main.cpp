/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:45
 */
// main.cpp：P9720 [EC Final 2022] Map 正解。
//
// 核心结论：最优路线一定可以写成
//   从 s 连续做 a 次“公园 -> 地图”传送到达 s'；
//   从 t 连续做 b 次“公园 -> 地图”传送到达 t'；
//   再从 s' 沿直线走到 t'，其中 a + b <= n。
//
// 为什么只用“公园 -> 地图”这一个方向：
//   1) 走路放在传送中间不如挪到最后。地图比公园小，把中间那段路挪到
//      最后走只会更短（题解中有完整证明）。
//   2) “地图 -> 公园”之后再“公园 -> 地图”会原样回到出发点，白花 2k 秒，
//      所以最优序列里不会出现这种反复。
//
// 于是只要枚举 a、b，每次“公园 -> 地图”就是这个相似变换的逆，
// 直接把点按固定比例收缩，复杂度 O(n^2)。
#include <bits/stdc++.h>
using namespace std;

const long double INF = 1e30L;

// 二维点 / 向量
struct Point {
    long double x, y;
};

Point operator+(Point a, Point b) { Point c; c.x = a.x + b.x; c.y = a.y + b.y; return c; }
Point operator-(Point a, Point b) { Point c; c.x = a.x - b.x; c.y = a.y - b.y; return c; }
Point operator*(long double t, Point a) { Point c; c.x = t * a.x; c.y = t * a.y; return c; }

// 点积
long double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

Point park[5]; // 公园的四个角，下标 1..4
Point mp[5];   // 地图的四个角，下标 1..4
Point s, t;    // 起点、终点，均在公园内
int k, n;      // 每次传送耗时、传送次数上限

long double dist(Point a, Point b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

// 公园中的点 p 传送到地图上的对应点，即题面中的 f^{-1}。
// 公园、地图都是矩形，所以 park[1] 出发的两条边 park[4]-park[1] 与
// park[2]-park[1] 相互垂直：先把 p 在这组正交基下分解，再用地图的
// 对应两条边还原即可。第 i 个地图角对应第 i 个公园角，故基向量也一一对应。
Point park_to_map(Point p) {
    Point o1 = park[1], e1 = park[4] - park[1], e2 = park[2] - park[1];
    Point o2 = mp[1],   f1 = mp[4] - mp[1],     f2 = mp[2] - mp[1];
    long double c1 = dot(p - o1, e1) / dot(e1, e1);
    long double c2 = dot(p - o1, e2) / dot(e2, e2);
    return o2 + c1 * f1 + c2 * f2;
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

    long double ans = INF;
    Point u = s;                                    // 对 s 做 a 次传送
    for (int a = 0; a <= n; a++) {
        Point v = t;                                // 对 t 做 b 次传送
        for (int b = 0; a + b <= n; b++) {
            long double cost = dist(u, v) + (long double)k * (a + b);
            if (cost < ans) ans = cost;
            v = park_to_map(v);
        }
        u = park_to_map(u);
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
