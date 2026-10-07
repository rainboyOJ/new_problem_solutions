// problem: 1714 地壳运动
// 做法: 参数化最小生成树（最小乘积生成树）。每条边的代价是 u*k1 + v*k2，一棵生成树 T 的
//       代价只由两个整数分量 (a_T, b_T) = (Σu, Σv) 决定。对所有生成树取 min(k1·a + k2·b)，
//       最小值一定在「全部生成树点的左下凸壳」顶点上取得；凸壳用「对法向做 MST」的分治补齐，
//       查询时在凸链（凸序列）上二分取最小。
// 复杂度: O(H·M log M + Q log H)，其中 H 为凸壳顶点数（本题数据下 ≤ 6），空间 O(N + M)。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128 lll;  // 边权与叉积用 128 位精确计算，全程无浮点参与排序

const int MAXM = 25005;

int N, M, Q;

struct Edge {
    int x, y;   // 端点
    ll u, v;    // 两个方向上的长度分量
};

Edge egs[MAXM];
ll K1, K2;      // 当前 MST oracle 的方向（整数，非负且不同时为 0）

// 按 k1*u + k2*v 升序；并列时按 (u,v) 升序，使极端方向 (1,0)/(0,1) 取到支配角点
static bool cmpEdge(const Edge &a, const Edge &b) {
    lll ca = (lll)a.u * K1 + (lll)a.v * K2;
    lll cb = (lll)b.u * K1 + (lll)b.v * K2;
    if (ca != cb) return ca < cb;
    if (a.u != b.u) return a.u < b.u;
    if (a.v != b.v) return a.v < b.v;
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

int fa[64];

static int find(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

// oracle：以 (d1,d2) 为边权方向做 Kruskal，返回该 MST 的 (Σu, Σv)
static pair<ll, ll> mst(ll d1, ll d2) {
    K1 = d1;
    K2 = d2;
    sort(egs, egs + M, cmpEdge);
    for (int i = 1; i <= N; i++) fa[i] = i;
    ll su = 0, sv = 0;
    int cnt = 0;
    for (int i = 0; i < M && cnt < N - 1; i++) {
        int ra = find(egs[i].x), rb = find(egs[i].y);
        if (ra != rb) {
            fa[ra] = rb;
            su += egs[i].u;
            sv += egs[i].v;
            cnt++;
        }
    }
    return make_pair(su, sv);
}

// 凸壳分治：l 在左上（a 小 b 大）、r 在右下（a 大 b 小），补出两者之间的凸壳点
static void divide(const pair<ll, ll> &l, const pair<ll, ll> &r,
                   vector<pair<ll, ll> > &out) {
    if (l.first >= r.first) return;              // a 区间已空
    ll d1 = l.second - r.second;                 // 弦的法向（两分量均为正）
    ll d2 = r.first - l.first;
    pair<ll, ll> mid = mst(d1, d2);
    // 叉积 (r-l) × (mid-l)：< 0 表示 mid 严格在弦下方，是新的凸壳顶点
    lll cr = (lll)(r.first - l.first) * (mid.second - l.second) -
             (lll)(r.second - l.second) * (mid.first - l.first);
    if (cr >= 0) return;                         // 弦下方没有候选点
    if (!(l.first < mid.first && mid.first < r.first)) return;  // 区间守卫
    divide(l, mid, out);
    out.push_back(mid);
    divide(mid, r, out);
}

int main() {
    if (scanf("%d %d %d", &N, &M, &Q) != 3) return 1;
    for (int i = 0; i < M; i++)
        if (scanf("%d %d %lld %lld", &egs[i].x, &egs[i].y, &egs[i].u, &egs[i].v) != 4) return 1;

    // ---------- 枚举左下凸壳 ----------
    pair<ll, ll> L = mst(1, 0);   // 最小 Σu
    pair<ll, ll> R = mst(0, 1);   // 最小 Σv
    vector<pair<ll, ll> > pts;
    pts.push_back(L);
    divide(L, R, pts);
    if (R != L) pts.push_back(R);

    // 按 a 升序去重，只保留 b 严格递减的 Pareto 最小点
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<pair<ll, ll> > hull;
    for (size_t i = 0; i < pts.size(); i++)
        if (hull.empty() || pts[i].second < hull.back().second) hull.push_back(pts[i]);

    int H = (int)hull.size();
    // 查询：k1·a + k2·b 在凸链上是凸序列（a 递增、b 递减且斜率递增），
    // 用长双精度二分求最小值所在下标，答案即该点代价。
    for (int q = 0; q < Q; q++) {
        long double k1, k2;
        if (scanf("%Lf %Lf", &k1, &k2) != 2) return 1;
        int lo = 0, hi = H - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            long double f0 = k1 * (long double)hull[mid].first + k2 * (long double)hull[mid].second;
            long double f1 = k1 * (long double)hull[mid + 1].first + k2 * (long double)hull[mid + 1].second;
            if (f0 <= f1) hi = mid;
            else lo = mid + 1;
        }
        long double ans = k1 * (long double)hull[lo].first + k2 * (long double)hull[lo].second;
        printf("%.3Lf\n", ans);
    }
    return 0;
}
