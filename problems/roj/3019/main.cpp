/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

typedef long long ll;

ll n; // 小岛数目
ll d; // 雷达检测范围（半径）

struct Interval {
    double l; // 能覆盖该岛的雷达位置左端点 x - sqrt(d^2 - y^2)
    double r; // 能覆盖该岛的雷达位置右端点 x + sqrt(d^2 - y^2)
};

Interval seg[MAXN]; // seg[i] 为第 i 个小岛对应的一维可选雷达位置区间

// 区间选点贪心：按右端点从小到大排序。
bool cmp(const Interval &a, const Interval &b) {
    return a.r < b.r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;

    bool impossible = false; // 是否存在纵坐标超过 d、任何雷达都够不着的小岛
    for (ll i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        if (y > d) {
            impossible = true;
            continue;
        }
        double rest = d * d - y * y; // 先存成 double，避免二次开方前出现类型不匹配
        double t = sqrt(rest);       // 雷达位置允许相对 x 偏移的最大距离
        seg[i].l = x - t;
        seg[i].r = x + t;
    }

    if (impossible) {
        cout << -1 << "\n";
        return 0;
    }

    sort(seg + 1, seg + n + 1, cmp);

    ll ans = 0;
    double pos = -1e18; // 上一个已放置雷达的位置，初始为负无穷
    for (ll i = 1; i <= n; i++) {
        if (seg[i].l > pos) { // 当前区间与已有雷达不相交，必须新放一个
            ans++;
            pos = seg[i].r; // 贪心放在右端点，能覆盖后续最多的区间
        }
    }

    cout << ans << "\n";
    return 0;
}
