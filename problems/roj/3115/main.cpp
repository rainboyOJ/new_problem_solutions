/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 窗口里的星星：扫描 x，线段树按「窗口底位置」维护覆盖亮度的最大值。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Star {
    ll x, y, c;
};

struct Event {
    ll x;
    ll sign; // 进入窗口 +1、离开 -1
    ll c;
    ll l, r; // 窗口底区间 [l, r]
};

std::vector<ll> MX;   // 线段树节点：该区间内窗口底的覆盖亮度最大值
std::vector<ll> LAZY; // 线段树节点：还没下传的区间加标记

bool event_less(const Event& a, const Event& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.sign > b.sign; // x 相同先加后减
}

// 把窗口底区间 [l, r] 上每个位置的覆盖亮度加 delta
void range_add(ll node, ll lo, ll hi, ll l, ll r, ll delta) {
    if (r < lo || hi < l) return;
    if (l <= lo && hi <= r) {
        MX[node] += delta;
        LAZY[node] += delta;
        return;
    }
    if (LAZY[node]) { // 下传标记
        MX[node * 2] += LAZY[node];
        LAZY[node * 2] += LAZY[node];
        MX[node * 2 + 1] += LAZY[node];
        LAZY[node * 2 + 1] += LAZY[node];
        LAZY[node] = 0;
    }
    ll mid = (lo + hi) >> 1;
    range_add(node * 2, lo, mid, l, r, delta);
    range_add(node * 2 + 1, mid + 1, hi, l, r, delta);
    MX[node] = (MX[node * 2] > MX[node * 2 + 1] ? MX[node * 2] : MX[node * 2 + 1]) + LAZY[node];
}

int main() {
    ll n;
    while (scanf("%lld", &n) == 1) {
        ll width, height;
        scanf("%lld %lld", &width, &height);

        std::vector<Star> stars(n);
        std::vector<ll> points;
        for (ll i = 0; i < n; i++) {
            scanf("%lld %lld %lld", &stars[i].x, &stars[i].y, &stars[i].c);
            // 覆盖亮度只在区间端点 y-height+1 和 y 处变化
            points.push_back(stars[i].y - height + 1);
            points.push_back(stars[i].y);
        }
        std::sort(points.begin(), points.end());
        points.erase(std::unique(points.begin(), points.end()), points.end());
        ll m = (ll)points.size();

        if (m == 0) {
            printf("0\n");
            continue;
        }

        std::vector<Event> events;
        for (ll i = 0; i < n; i++) {
            ll l = std::lower_bound(points.begin(), points.end(), stars[i].y - height + 1) - points.begin();
            ll r = std::lower_bound(points.begin(), points.end(), stars[i].y) - points.begin();
            Event e;
            e.x = stars[i].x;       e.sign = 1;  e.c = stars[i].c; e.l = l; e.r = r; events.push_back(e);
            e.x = stars[i].x + width; e.sign = -1; e.c = stars[i].c; e.l = l; e.r = r; events.push_back(e);
        }
        std::sort(events.begin(), events.end(), event_less);

        MX.assign(4 * m + 4, 0);
        LAZY.assign(4 * m + 4, 0);
        ll ans = 0;
        ll i = 0;
        ll total = 2 * n;
        while (i < total) {
            ll x = events[i].x;
            while (i < total && events[i].x == x) { // 同一条竖线：整列一起扫进/扫出
                range_add(1, 0, m - 1, events[i].l, events[i].r, events[i].sign * events[i].c);
                i++;
            }
            // 扫到下一条竖线前，窗口左右可停在任意位置
            if (MX[1] > ans) ans = MX[1];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
