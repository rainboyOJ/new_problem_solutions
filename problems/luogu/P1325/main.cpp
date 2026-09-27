/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 17:28
 * update_at: 2026-09-27 17:30
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1005;
const double EPS = 1e-9;

int n;
double d;

struct Interval {
    double l, r; // 能覆盖该小岛的雷达横坐标区间 [l, r]
};
Interval a[MAXN];

// 贪心：按区间右端点从小到大排序
bool cmp(const Interval &x, const Interval &y) {
    return x.r < y.r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        if (y > d) {
            // 小岛到海岸线的距离超过雷达半径，任何雷达都覆盖不到
            ok = false;
        }
        // 雷达放在 p 处能覆盖该岛 <=> |p - x| <= sqrt(d^2 - y^2)
        double half = sqrt(d * d - (double)y * y);
        a[i].l = x - half;
        a[i].r = x + half;
    }

    if (!ok) {
        cout << -1 << "\n";
        return 0;
    }

    sort(a + 1, a + n + 1, cmp);

    int ans = 0;
    double last = -1e18; // 最近一个雷达的位置
    for (int i = 1; i <= n; i++) {
        // 左端点在雷达右侧，说明当前雷达覆盖不到这个区间
        if (a[i].l > last + EPS) {
            ans++;
            last = a[i].r; // 把新雷达放在这个区间的右端点
        }
    }
    cout << ans << "\n";
    return 0;
}
