/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 亚特兰蒂斯：矩形面积并，按 x 扫描竖边，线段树维护被覆盖的 y 总长度。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Rect {
    double x1, y1, x2, y2;
};

struct Edge {
    double x;
    ll ql, qr;   // 基本段区间 [ql, qr]
    ll delta;    // 左边界 +1、右边界 -1
};

std::vector<double> ys;      // 离散化后的 y 坐标
std::vector<ll> cover_cnt;   // 结点被整段覆盖的次数
std::vector<double> cover_len; // 结点内被覆盖的总长度

bool edge_less(const Edge& a, const Edge& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.ql != b.ql) return a.ql < b.ql;
    if (a.qr != b.qr) return a.qr < b.qr;
    return a.delta < b.delta;
}

// 把基本段区间 [ql, qr] 的覆盖次数加 delta，再回填本结点的覆盖长度
void cover(ll node, ll nl, ll nr, ll ql, ll qr, ll delta) {
    if (ql <= nl && nr <= qr) { // 整段落在同一条竖边的跨度里
        cover_cnt[node] += delta;
    } else {
        ll mid = (nl + nr) >> 1;
        if (ql <= mid) cover(node << 1, nl, mid, ql, qr, delta);
        if (qr > mid) cover(node << 1 | 1, mid + 1, nr, ql, qr, delta);
    }
    if (cover_cnt[node]) { // 被完整覆盖：整段都算
        cover_len[node] = ys[nr + 1] - ys[nl];
    } else if (nl == nr) {
        cover_len[node] = 0.0;
    } else {
        cover_len[node] = cover_len[node << 1] + cover_len[node << 1 | 1];
    }
}

double union_area(std::vector<Rect>& rects) {
    ys.clear();
    for (size_t i = 0; i < rects.size(); i++) {
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
    }
    std::sort(ys.begin(), ys.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

    ll seg_cnt = (ll)ys.size() - 1; // 基本段个数：第 i 段是 [ys[i], ys[i+1]]
    cover_cnt.assign(4 * seg_cnt + 4, 0);
    cover_len.assign(4 * seg_cnt + 4, 0.0);

    std::vector<Edge> edges;
    for (size_t i = 0; i < rects.size(); i++) {
        ll r1 = std::lower_bound(ys.begin(), ys.end(), rects[i].y1) - ys.begin();
        ll r2 = std::lower_bound(ys.begin(), ys.end(), rects[i].y2) - ys.begin();
        Edge e;
        e.x = rects[i].x1; e.ql = r1; e.qr = r2 - 1; e.delta = 1;  edges.push_back(e);
        e.x = rects[i].x2; e.ql = r1; e.qr = r2 - 1; e.delta = -1; edges.push_back(e);
    }
    std::sort(edges.begin(), edges.end(), edge_less);

    double area = 0.0;
    double prev_x = edges[0].x;
    for (size_t i = 0; i < edges.size(); i++) {
        area += cover_len[1] * (edges[i].x - prev_x); // 区间 [prev_x, x) 用移动前的覆盖长度
        cover(1, 0, seg_cnt - 1, edges[i].ql, edges[i].qr, edges[i].delta);
        prev_x = edges[i].x;
    }
    return area;
}

int main() {
    ll n;
    ll case_id = 0;
    while (scanf("%lld", &n) == 1 && n != 0) {
        case_id++;
        std::vector<Rect> rects(n);
        for (ll i = 0; i < n; i++) {
            scanf("%lf %lf %lf %lf", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
        }
        double area = union_area(rects);
        printf("Test case #%lld\nTotal explored area: %.2f\n\n", case_id, area);
    }
    return 0;
}
