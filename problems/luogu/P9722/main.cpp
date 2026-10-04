/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:53
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 坐标上界：题目中所有坐标都在 [1,1e9]，故 M 恒为 1e9。
// 本地用小 M 压力测试时可加编译选项 -DPROBLEM_M=8 覆盖。
#ifndef PROBLEM_M
#define PROBLEM_M 1000000000LL
#endif
const ll MX = PROBLEM_M;          // 坐标最大值 M
const ll MOD = 998244353;
const int MAXN = 100005;
const ll INF = MX + 1;            // 严格大于任何可能的 x2

int n;
ll rx1[MAXN], ry1[MAXN], rx2[MAXN], ry2[MAXN];

// sum_{i=l}^{r} i
inline __int128 sumB(ll l, ll r) {
    if (l > r) return 0;
    return (__int128)(l + r) * (r - l + 1) / 2;
}

// sum_{i=1}^{t} i^2
inline __int128 sumB2(ll t) {
    if (t <= 0) return 0;
    return (__int128)t * (t + 1) * (2 * t + 1) / 6;
}

// ===============================================================
// 第一部分：三条竖线 x=a1<a2<a3
//
// S^-(b) = {i : x2_i < b}，S^+(b) = {i : x1_i > b}。
// 三条竖线能盖住第 i 个矩形，当且仅当 min(a1,a2) <= x1_i 且 max(a2,a3) >= x2_i。
// 固定 a2=b：a1 必须 <= min{x1_i : i∈S^-}，a3 必须 >= max{x2_i : i∈S^+}。
// 记 f_-(b)、f_+(b) 为 a1、a3 的合法个数，则方案数为 f_-(b)*f_+(b)：
//   f_-(b) = b-1                                        (S^- 为空)
//          = max(0, min_{S^-}x2 - max_{S^-}x1 + 1)       (否则)
//   f_+(b) = M-b                                        (S^+ 为空)
//          = max(0, min_{S^+}x2 - max_{S^+}x1 + 1)       (否则)
//
// S^- 的成员只在 b=x2_i+1 变化，S^+ 只在 b=x1_i 变化；因此以
// {1, M+1} ∪ {x1_i} ∪ {x2_i+1} 为断点分块，块内 f_-、f_+ 的「是否为空」
// 与取值都是常数，统计四类乘积和即可。
// ===============================================================
ll sx1[MAXN], sx2[MAXN];    // 升序的 x1 / x2
ll preMaxX1[MAXN];          // 按 x2 升序后 x1 的前缀最大值
ll preMinX2[MAXN];          // 按 x1 降序后 x2 的前缀最小值
ll bp[2 * MAXN + 5];        // 断点
pair<ll, int> pr[MAXN];     // 排序临时数组

ll case1() {
    for (int i = 0; i < n; ++i) {
        sx1[i] = rx1[i];
        sx2[i] = rx2[i];
    }
    sort(sx1, sx1 + n);
    sort(sx2, sx2 + n);

    // 按 (x2,x1) 升序：前 i+1 个恰是 x2 最小的 i+1 个矩形，记其最大 x1
    for (int i = 0; i < n; ++i) pr[i] = make_pair(rx2[i], rx1[i]);
    sort(pr, pr + n);
    ll cur = 0;
    for (int i = 0; i < n; ++i) {
        if (pr[i].second > cur) cur = pr[i].second;
        preMaxX1[i] = cur;
    }

    // 按 x1 降序：前 i+1 个恰是 x1 最大的 i+1 个矩形，记其最小 x2
    for (int i = 0; i < n; ++i) pr[i] = make_pair(rx1[i], rx2[i]);
    sort(pr, pr + n);
    cur = INF;
    for (int i = n - 1, c = 0; i >= 0; --i, ++c) {
        if (pr[i].second < cur) cur = pr[i].second;
        preMinX2[c] = cur;
    }

    // 断点：S^- 在 x2_i+1 变化，S^+ 在 x1_i 变化
    int bn = 0;
    bp[bn++] = 1;
    bp[bn++] = MX + 1;
    for (int i = 0; i < n; ++i) {
        bp[bn++] = rx1[i];
        bp[bn++] = rx2[i] + 1;
    }
    sort(bp, bp + bn);
    bn = (int)(unique(bp, bp + bn) - bp);

    __int128 tot = 0;
    for (int k = 0; k + 1 < bn; ++k) {
        ll lo = bp[k], hi = bp[k + 1] - 1;
        if (lo > MX) break;
        ll len = hi - lo + 1;
        int i1 = (int)(lower_bound(sx2, sx2 + n, lo) - sx2);       // x2 < lo 的个数
        int cp1 = n - (int)(upper_bound(sx1, sx1 + n, lo) - sx1);  // x1 > lo 的个数
        bool em = (i1 == 0), ep = (cp1 == 0);
        ll cm = 0, cp = 0;
        if (!em) {
            cm = sx2[0] - preMaxX1[i1 - 1] + 1;
            if (cm < 0) cm = 0;
        }
        if (!ep) {
            cp = preMinX2[cp1 - 1] - sx1[n - 1] + 1;
            if (cp < 0) cp = 0;
        }
        __int128 s;
        if (em && ep) {
            // sum (b-1)(M-b) = -(sum b^2) + (M+1)(sum b) - M*len
            s = sumB2(lo - 1) - sumB2(hi)
                + (__int128)(MX + 1) * sumB(lo, hi)
                - (__int128)MX * len;
        } else if (!em && ep) {
            // f_- = cm, f_+ = M-b
            s = (__int128)cm * sumB(MX - hi, MX - lo);
        } else if (em && !ep) {
            // f_- = b-1, f_+ = cp
            s = (__int128)cp * sumB(lo - 1, hi - 1);
        } else {
            s = (__int128)cm * cp * len;
        }
        tot += s;
    }
    return (ll)(tot % MOD);
}

// ===============================================================
// 第二部分：一条横线 y=h，两条竖线 x=a1<a2
//
// U_h = {i : h 不在 [y1_i, y2_i] 内}，即横线没碰到的矩形集合。
// 这两条竖线必须横穿 U_h 中所有矩形，方案数 g(U_h) 只依赖 U：
//   L = max_{i∈U} x1_i，R = min_{i∈U} x2_i。
//   * a2 >= L：只需 a1,a2 <= R，贡献 sum_{a=L}^{R}(M-a)。
//   * a2 <= L-1：记 Q(a)=min{x2_i : i∈U, x1_i>a}，a1 必须 <= Q(a)，
//     贡献 (Q(a)-L+1)^+，对 a=1..min(R,L-1) 求和。
//   U 为空时两条竖线任选，g = C(M,2)。
// 用 (S-c)^+ = S - min(S,c) 去掉正部：
//   H = Sum(A,+INF) - Sum(A,L-1)，其中 Sum(A,x) = sum_{a=1}^{A} min(Q(a),x)。
//
// Sum 用按 x1 取值离散化的线段树维护：
//   叶 j 的权 w_j 表示 a ∈ [v_{j-1}, v_j-1]（v_0=1），
//   叶值 c_j = min{x2_i : x1_i=v_j, i∈U}（无则 INF）。
//   节点维护 mn（子树最小 c）、sw（子树权和）、
//   sl = sum_{k∈左子} w_k * min(左子内后缀min(k..mid), mn[右子])，
//   pushup 时 queryCap 只走一条路径，故 pushup 为 O(log)。
// 随 h 扫描：矩形在 h∈[1,y1-1] ∪ [y2+1,M] 时属于 U，
// 用 multiset 维护每个叶子的激活 x2，插入/删除后单点修改线段树。
// ===============================================================
int m;                        // 不同 x1 值个数
ll vs[MAXN];                  // 去重升序的 x1
int gid[MAXN];                // 每个矩形所在的叶编号
multiset<ll> ms[MAXN];        // 每个叶子当前激活的 x2
ll tmn[4 * MAXN], tsw[4 * MAXN], tsl[4 * MAXN];
vector<pair<int, int> > ev;   // (h, 事件)：正数插入，负数删除

// sum_{k=l}^{r} w_k * min( 后缀min(k..r), y )（对节点整段调用）
ll queryCap(int p, int l, int r, ll y) {
    if (y <= tmn[p]) return tsw[p] * y;
    if (l == r) return tsw[p] * tmn[p];
    int mid = (l + r) >> 1, lc = p << 1, rc = p << 1 | 1;
    if (y <= tmn[rc]) return queryCap(lc, l, mid, y) + y * tsw[rc];
    return queryCap(rc, mid + 1, r, y) + tsl[p];
}

void pushup(int p, int l, int r) {
    int mid = (l + r) >> 1, lc = p << 1, rc = p << 1 | 1;
    tmn[p] = min(tmn[lc], tmn[rc]);
    tsw[p] = tsw[lc] + tsw[rc];
    tsl[p] = queryCap(lc, l, mid, tmn[rc]);
}

void build(int p, int l, int r) {
    tsl[p] = 0;
    tmn[p] = INF;
    if (l == r) {
        ll prev = (l == 1 ? 1 : vs[l - 1]);
        tsw[p] = vs[l] - prev;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p, l, r);
}

void update(int p, int l, int r, int pos, ll val) {
    if (l == r) { tmn[p] = val; return; }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(p << 1, l, mid, pos, val);
    else update(p << 1 | 1, mid + 1, r, pos, val);
    pushup(p, l, r);
}

ll rangeMin(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INF;
    if (ql <= l && r <= qr) return tmn[p];
    int mid = (l + r) >> 1;
    return min(rangeMin(p << 1, l, mid, ql, qr),
               rangeMin(p << 1 | 1, mid + 1, r, ql, qr));
}

// 从右到左扫 [ql,qr]：返回 sum w_j * min(该点右侧部分的最小 c, ctx)，
// 并把 ctx 更新为已扫过部分的最小 c。右侧必须先算，故拆成两条语句。
ll rangePsi(int p, int l, int r, int ql, int qr, ll &ctx) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) {
        ll res = queryCap(p, l, r, ctx);
        if (tmn[p] < ctx) ctx = tmn[p];
        return res;
    }
    int mid = (l + r) >> 1;
    ll res = rangePsi(p << 1 | 1, mid + 1, r, ql, qr, ctx);
    res += rangePsi(p << 1, l, mid, ql, qr, ctx);
    return res;
}

// Sum(A,x) = sum_{a=1}^{A} min(Q(a), x)
ll resultQuery(ll A, ll x) {
    if (A < 1) return 0;
    if (A > vs[m] - 1) A = vs[m] - 1;   // 右侧 j>k 的段用 S 一次算完
    int k = (int)(upper_bound(vs + 1, vs + 1 + m, A) - (vs + 1));  // v_j <= A 的个数
    if (k == 0) return A * min(tmn[1], x);
    ll pw = A - vs[k] + 1;                                   // 第 k+1 段被截断的长度
    ll S = (k + 1 <= m) ? rangeMin(1, 1, m, k + 1, m) : INF; // 右侧激活部分最小值
    ll ctx = min(S, x);
    ll res = rangePsi(1, 1, m, 1, k, ctx);
    res += pw * min(S, x);
    return res;
}

// 当前 U 对应的 g(U)，结果对 MOD 取模
ll gValue() {
    if (tmn[1] >= INF) return MX % MOD * ((MX - 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD; // C(M,2)
    int p = 1, l = 1, r = m;
    while (l < r) {                                  // 找最右的激活叶（得 L）
        int mid = (l + r) >> 1;
        if (tmn[p << 1 | 1] < INF) { p = p << 1 | 1; l = mid + 1; }
        else { p = p << 1; r = mid; }
    }
    ll Lv = vs[l], Rv = tmn[1];
    ll A = min(Rv, Lv - 1);
    __int128 H = 0;
    if (A >= 1) H = resultQuery(A, INF) - resultQuery(A, Lv - 1);
    __int128 E = 0;
    if (Rv >= Lv) E = sumB(MX - Rv, MX - Lv);
    return (ll)((H + E) % MOD);
}

void insertRect(int i) {
    int g = gid[i];
    ms[g].insert(rx2[i]);
    update(1, 1, m, g, *ms[g].begin());
}

void removeRect(int i) {
    int g = gid[i];
    ms[g].erase(ms[g].find(rx2[i]));
    update(1, 1, m, g, ms[g].empty() ? INF : *ms[g].begin());
}

// 第二部分总贡献：所有 h 的 g(U_h) 之和
ll case2() {
    // 离散化 x1
    for (int i = 0; i < n; ++i) vs[i + 1] = rx1[i];
    sort(vs + 1, vs + 1 + n);
    m = (int)(unique(vs + 1, vs + 1 + n) - (vs + 1));
    for (int i = 0; i < n; ++i) {
        gid[i] = (int)(lower_bound(vs + 1, vs + 1 + m, rx1[i]) - vs);
        ms[gid[i]].clear();
    }
    build(1, 1, m);

    // 事件：h=1 先插入 y1>=2 的；h=y1 删除；h=y2+1 插入
    ev.clear();
    for (int i = 0; i < n; ++i) {
        if (ry1[i] >= 2) ev.push_back(make_pair(1, i + 1));
        if (ry2[i] + 1 <= MX) ev.push_back(make_pair(ry2[i] + 1, i + 1));
        if (ry1[i] >= 2) ev.push_back(make_pair(ry1[i], -(i + 1)));
    }
    sort(ev.begin(), ev.end());

    ll res = 0;
    ll cur = 1;      // 当前已经算过的 h 区间起点
    size_t ptr = 0;
    while (ptr < ev.size()) {
        ll h = ev[ptr].first;
        if (h > cur) {
            res = (res + (h - cur) % MOD * gValue()) % MOD;
            cur = h;
        }
        while (ptr < ev.size() && ev[ptr].first == h) {
            int id = ev[ptr].second;
            if (id > 0) insertRect(id - 1);
            else removeRect(-id - 1);
            ++ptr;
        }
    }
    if (cur <= MX) res = (res + (MX - cur + 1) % MOD * gValue()) % MOD;
    return res;
}

void read_data() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> rx1[i] >> ry1[i] >> rx2[i] >> ry2[i];
        ll ans = (case1() + case2()) % MOD;   // 三条竖线 / 一横两竖
        for (int i = 0; i < n; ++i) {         // 转置后即三条横线 / 一竖两横
            swap(rx1[i], ry1[i]);
            swap(rx2[i], ry2[i]);
        }
        ans = (ans + case1() + case2()) % MOD;
        cout << ans << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    read_data();
    return 0;
}
