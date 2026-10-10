/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 周长：沿一个坐标扫描，线段树维护截面上「被盖住的极大区间个数」。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Rect {
    ll start, end; // 沿扫描方向的起点 / 终点
    ll lo, hi;     // 垂直于扫描方向的区间 [lo, hi]
};

struct Event {
    ll pos;
    ll lo, hi;
    ll val;
};

std::vector<ll> COVER;    // 每个节点被整段盖住的次数：只记在最高的大节点上，不下传
std::vector<ll> SEGMENT;  // 该节点内部「被盖住的极大区间」个数
std::vector<ll> LEFT_ON;  // 最左元区间是否被盖住
std::vector<ll> RIGHT_ON; // 最右元区间是否被盖住

ll leaves;

// 按压缩坐标建一棵空树，返回元区间（相邻两个坐标之间）的个数
ll build(std::vector<ll>& coords) {
    leaves = (ll)coords.size() - 1;
    ll size = 4 * leaves + 4;
    COVER.assign(size, 0);
    SEGMENT.assign(size, 0);
    LEFT_ON.assign(size, 0);
    RIGHT_ON.assign(size, 0);
    return leaves;
}

// 由两个孩子的覆盖信息重算 node 的区间个数与左右端标志
void pull(ll node, ll nl, ll nr) {
    if (COVER[node]) { // 整段被盖住，内部必然只剩一个极大区间
        SEGMENT[node] = 1;
        LEFT_ON[node] = RIGHT_ON[node] = 1;
    } else if (nl == nr) { // 叶子且没被盖住
        SEGMENT[node] = 0;
        LEFT_ON[node] = RIGHT_ON[node] = 0;
    } else {
        ll left = node << 1, right = node << 1 | 1;
        // 两孩子在交界处都被盖住时，它们其实属于同一个极大区间，要减去这一次重复
        SEGMENT[node] = SEGMENT[left] + SEGMENT[right] - (RIGHT_ON[left] & LEFT_ON[right]);
        LEFT_ON[node] = LEFT_ON[left];
        RIGHT_ON[node] = RIGHT_ON[right];
    }
}

// 把元区间 [ql, qr] 的覆盖次数加上 val
void update(ll node, ll nl, ll nr, ll ql, ll qr, ll val) {
    if (ql <= nl && nr <= qr) {
        COVER[node] += val;
        pull(node, nl, nr);
        return;
    }
    ll mid = (nl + nr) >> 1;
    if (ql <= mid) update(node << 1, nl, mid, ql, qr, val);
    if (qr > mid) update(node << 1 | 1, mid + 1, nr, ql, qr, val);
    pull(node, nl, nr);
}

bool event_less(const Event& a, const Event& b) {
    if (a.pos != b.pos) return a.pos < b.pos;
    if (a.lo != b.lo) return a.lo < b.lo;
    if (a.hi != b.hi) return a.hi < b.hi;
    return a.val < b.val;
}

// 沿第一个坐标扫描，返回平行于扫描方向的那些边的总长
ll sweep(std::vector<Rect>& rects) {
    std::vector<ll> coords;
    for (size_t i = 0; i < rects.size(); i++) {
        coords.push_back(rects[i].lo);
        coords.push_back(rects[i].hi);
    }
    std::sort(coords.begin(), coords.end());
    coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
    build(coords);
    if (leaves <= 0) return 0; // 连一个元区间都没有，也就没有边

    std::vector<Event> events;
    for (size_t i = 0; i < rects.size(); i++) {
        ll lo = std::lower_bound(coords.begin(), coords.end(), rects[i].lo) - coords.begin();
        ll hi = std::lower_bound(coords.begin(), coords.end(), rects[i].hi) - coords.begin();
        Event e;
        e.pos = rects[i].start; e.lo = lo; e.hi = hi - 1; e.val = 1;  events.push_back(e);
        e.pos = rects[i].end;   e.lo = lo; e.hi = hi - 1; e.val = -1; events.push_back(e);
    }
    std::sort(events.begin(), events.end(), event_less);

    ll total = 0;
    ll last = events[0].pos; // 第一个事件开出空条带，(first, first) 宽度为 0
    for (size_t i = 0; i < events.size(); i++) {
        ll width = events[i].pos - last; // 同一位置上的多个事件之间宽度为 0
        // 截面上每个极大区间贡献上下两条平行于扫描方向的边
        total += 2 * SEGMENT[1] * width;
        last = events[i].pos;
        update(1, 0, leaves - 1, events[i].lo, events[i].hi, events[i].val);
    }
    return total;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回

    std::vector<Rect> rects(n);
    std::vector<Rect> vertical(n);
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        if (x1 > x2) { ll t = x1; x1 = x2; x2 = t; }
        if (y1 > y2) { ll t = y1; y1 = y2; y2 = t; }
        rects[i].start = x1; rects[i].end = x2; rects[i].lo = y1; rects[i].hi = y2;
        // 竖直边的总长 = 把矩形转 90° 后再照同一套扫描线求一次
        vertical[i].start = y1; vertical[i].end = y2; vertical[i].lo = x1; vertical[i].hi = x2;
    }

    printf("%lld\n", sweep(rects) + sweep(vertical));
    return 0;
}
