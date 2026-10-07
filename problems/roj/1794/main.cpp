/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:26
 * update_at: 2026-10-08 03:47
 */
// 1794《分数》
// 标记集合按极大连续段分解，长度 c 的一段贡献 c(c+1)/2 - 段内数字和。
// 于是 dpL / dpR 是两条斜率优化 DP；"强制标记 P"的最优值 markBest[P] 用 CDQ 分治 + 凸包求。
// 每组询问 (P,X) 的答案 = max(dpL[P-1] + dpR[P+1], markBest[P] - X + T[P])。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 300005;
const ll NEG = LLONG_MIN / 4; // 不可达哨兵：绝对值足够大，参与加减也不会溢出

int n, m;
ll T[MAXN];          // 原序列 T[1..n]
ll pre[MAXN];        // pre[i] = T[1] + ... + T[i]
ll dpL[MAXN];        // dpL[i]：只考虑前缀 1..i 时的最大得分（dpL[0] = 0）
ll dpR[MAXN];        // dpR[i]：只考虑后缀 i..n 时的最大得分（dpR[n+1] = 0）
ll leftPart[MAXN];   // 覆盖 P 的区间 [a,b] 中左端 a 的贡献
ll rightPart[MAXN];  // 覆盖 P 的区间 [a,b] 中右端 b 的贡献
ll markBest[MAXN];   // markBest[P]：原序列中强制标记位置 P 时的最大得分
ll cdqTmp[MAXN];     // CDQ 分治右半边的中间值，避免在递归函数里开大数组

// 直线 y = k*x + b
struct Line {
    ll k, b;
};

// 上凸包：查询 max(k*x+b)，插入的斜率必须严格递增
struct Hull {
    Line ln[MAXN];
    int sz;

    void clear() { sz = 0; }

    // 插入直线 y = kx + b；同斜率只保留截距更大的一条
    void add(ll k, ll b) {
        if (sz > 0 && ln[sz - 1].k == k) {
            if (ln[sz - 1].b >= b) return;
            --sz;
        }
        while (sz >= 2) {
            Line p = ln[sz - 2]; // 斜率最小的一条
            Line o = ln[sz - 1]; // 可能变冗余的中间线
            Line q;              // 新插入的线，斜率最大
            q.k = k;
            q.b = b;
            // 中间线 o 的最优区间为空 <=> 交点 x(p,o) >= 交点 x(o,q)
            __int128 lhs = (__int128)(p.b - o.b) * (q.k - o.k);
            __int128 rhs = (__int128)(o.b - q.b) * (o.k - p.k);
            if (lhs >= rhs) --sz;
            else break;
        }
        ln[sz].k = k;
        ln[sz].b = b;
        ++sz;
    }

    ll val(int i, ll x) const { return ln[i].k * x + ln[i].b; }

    // 任意 x 的二分查询：凸包上取值随下标单峰
    ll query(ll x) const {
        int lo = 0, hi = sz - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (val(mid, x) <= val(mid + 1, x)) lo = mid + 1;
            else hi = mid;
        }
        return val(lo, x);
    }
} hull;

// 自然数快读：输入只含非负整数，跳过非数字字符即可
ll readInt() {
    int ch = getchar();
    while (ch != EOF && (ch < '0' || ch > '9')) ch = getchar();
    ll v = 0;
    while (ch >= '0' && ch <= '9') {
        v = v * 10 + (ch - '0');
        ch = getchar();
    }
    return v;
}

// 前缀 DP：dpL[i] = max(dpL[i-1], max_{m<i} { dpL[m-1] + C(i-m) - (pre[i]-pre[m]) })
// 其中 C(len) = len(len+1)/2，m 表示区间左端的前一个位置（m=0 表示从 1 开始）
void buildDpL() {
    hull.clear();
    for (int i = 1; i <= n; ++i) {
        ll m = i - 1;
        ll prevBest = (m == 0 ? 0 : dpL[m - 1]); // m = 0 时左边是空前缀
        ll c = prevBest + pre[m] + m * (m - 1) / 2;
        hull.add(m, c); // 直线 y = m*x + c
        ll cand = (ll)i * (i + 1) / 2 - pre[i] + hull.query(-(ll)i);
        dpL[i] = max(dpL[i - 1], cand);
    }
}

// 后缀 DP（对称）：dpR[i] = max(dpR[i+1], max_{j>i} { dpR[j+1] + C(j-i) - (pre[j-1]-pre[i-1]) })
// j 表示区间右端的后一个位置（j = n+1 表示到 n 结束）
void buildDpR() {
    hull.clear();
    dpR[n + 1] = 0;
    dpR[n + 2] = 0;
    for (int i = n; i >= 1; --i) {
        ll j = i + 1;
        ll e = dpR[j + 1] - pre[j - 1] + j * (j + 1) / 2;
        hull.add(-j, e); // 直线 y = -j*x + e，查询 x = i
        ll cand = pre[i - 1] + (ll)i * (i - 1) / 2 + hull.query(i);
        dpR[i] = max(dpR[i + 1], cand);
    }
}

// CDQ 分治：markBest[P] = max{ leftPart[a] + rightPart[b] - a*b : a <= P <= b }
void cdq(int lo, int hi) {
    if (lo > hi) return;
    if (lo == hi) {
        // 只跨自己的区间 [lo, lo]
        ll v = leftPart[lo] + rightPart[lo] - (ll)lo * lo;
        markBest[lo] = max(markBest[lo], v);
        return;
    }
    int mid = (lo + hi) >> 1;

    // 情形一：P ∈ [lo, mid]。a <= P 需要保证，而 b >= mid+1 自动满足 b >= P。
    // 先对每个 a 查出右半边最优的 b，再对 a 取前缀最大值，一次覆盖左半边所有 P。
    hull.clear();
    for (int b = hi; b >= mid + 1; --b) hull.add(-(ll)b, rightPart[b]); // 斜率 -b 递增
    {
        int ptr = 0;
        ll best = NEG;
        for (int a = lo; a <= mid; ++a) { // 查询 x = a 递增，最优下标单调右移
            while (ptr + 1 < hull.sz && hull.val(ptr + 1, a) >= hull.val(ptr, a)) ++ptr;
            ll v = leftPart[a] + hull.val(ptr, a);
            if (v > best) best = v;
            if (best > markBest[a]) markBest[a] = best;
        }
    }

    // 情形二：P ∈ [mid+1, hi]。b >= P 需要保证，而 a <= mid 自动满足 a <= P。
    hull.clear();
    for (int a = mid; a >= lo; --a) hull.add(-(ll)a, leftPart[a]); // 斜率 -a 递增
    {
        int ptr = 0;
        for (int b = mid + 1; b <= hi; ++b) { // 查询 x = b 递增
            while (ptr + 1 < hull.sz && hull.val(ptr + 1, b) >= hull.val(ptr, b)) ++ptr;
            cdqTmp[b] = rightPart[b] + hull.val(ptr, b);
        }
        ll suf = NEG;
        for (int b = hi; b >= mid + 1; --b) { // P 可取 [P, hi] 内任意 b
            if (cdqTmp[b] > suf) suf = cdqTmp[b];
            if (suf > markBest[b]) markBest[b] = suf;
        }
    }

    cdq(lo, mid);
    cdq(mid + 1, hi);
}

int main() {
    n = (int)readInt();
    for (int i = 1; i <= n; ++i) {
        T[i] = readInt();
        pre[i] = pre[i - 1] + T[i];
    }

    buildDpL();
    buildDpR();

    // dpL[A-2] + f(A,B) + dpR[B+2] = leftPart[A] + rightPart[B] - A*B
    for (int a = 1; a <= n; ++a) {
        ll dl = (a >= 2 ? dpL[a - 2] : 0); // a <= 2 时区间左边是空前缀
        leftPart[a] = dl + pre[a - 1] + ((ll)a * a - 3LL * a) / 2;
    }
    for (int b = 1; b <= n; ++b) {
        rightPart[b] = dpR[b + 2] - pre[b] + ((ll)b * b + 3LL * b + 2) / 2;
    }
    for (int p = 1; p <= n; ++p) markBest[p] = NEG;
    cdq(1, n);

    m = (int)readInt();
    string out;
    out.reserve((size_t)m * 15);
    for (int i = 0; i < m; ++i) {
        ll p = readInt();
        ll x = readInt();
        ll noCover = dpL[p - 1] + dpR[p + 1]; // P 不标记：值改成什么都无所谓
        ll withCover = markBest[p] - x + T[p]; // P 标记：整段和多了 x - T[p]，收益等量减少
        ll ans = max(noCover, withCover);
        if (ans < 0) ans = 0; // 全部不标记也能得 0 分
        out += to_string(ans);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
