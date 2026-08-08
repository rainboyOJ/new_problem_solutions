/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Point {
    int x, y, z;
};

int n;
Point pts[MAXN];

// 按高度 z 升序排序
bool cmp(const Point &a, const Point &b) {
    return a.z < b.z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
    }

    sort(pts, pts + n, cmp);

    double ans = 0.0;
    for (int i = 0; i < n - 1; i++) {
        double dx = pts[i].x - pts[i + 1].x;
        double dy = pts[i].y - pts[i + 1].y;
        double dz = pts[i].z - pts[i + 1].z;
        ans += sqrt(dx * dx + dy * dy + dz * dz);
    }

    cout << fixed << setprecision(3) << ans << "\n";

    return 0;
}
