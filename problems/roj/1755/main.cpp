/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:45
 * update_at: 2026-10-07 21:45
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int u32; // 所有乘积之和都在 mod 2^32 下计算，u32 溢出回绕正好就是取模

const int MAXN = 100000 + 5; // 区域数上限
const int KMAX = 6;          // 单次勘测选取块数 K 的上限

// 一块区域：相对距离 D 与丰富程度 V
// V 用 u32：V <= 1e9，而所有参与计算的量都在 mod 2^32 意义下，统一用 u32 省掉转换
struct Area {
    ll d;
    u32 v;
};
Area a[MAXN]; // 读入后按 D 升序重排，这样 D 的区间查询就变成下标区间查询

// 线段树结点：维护该段 V 的 1..KMAX 次初等对称和，以及段内最小 V 及其位置
struct SegNode {
    u32 e[KMAX + 1]; // e[k] = 段内 V 的 k 次初等对称和（k >= 1；k = 0 恒为 1，不落数组）
    u32 min_v;       // 段内最小的 V
    int min_pos;     // 最小 V 的下标（按 D 排序后的位置，V 互不相同所以唯一）
};
SegNode tree[MAXN << 2];

int n, q; // 区域数、计划数

// 把 b 整段并进 a：a 表示某段的多项式，b 表示另一段，结果写回 a
// 两段的多项式相乘就是「V 集合取并」，系数按截断卷积合并：
//   e_i = a_i + b_i + Σ_{j=1}^{i-1} a_j · b_{i-j}
void merge_poly(u32 a[], const u32 b[]) {
    u32 c[KMAX + 1];
    for (int i = 1; i <= KMAX; i++) {
        u32 s = a[i] + b[i];
        for (int j = 1; j < i; j++) s += a[j] * b[i - j];
        c[i] = s;
    }
    for (int i = 1; i <= KMAX; i++) a[i] = c[i];
}

// 用两个儿子的信息重置结点 u：多项式做合并，最小 V 取较小的一边
void pull(int u) {
    int lc = u << 1, rc = lc | 1;
    if (tree[lc].min_v <= tree[rc].min_v) {
        tree[u].min_v = tree[lc].min_v;
        tree[u].min_pos = tree[lc].min_pos;
    } else {
        tree[u].min_v = tree[rc].min_v;
        tree[u].min_pos = tree[rc].min_pos;
    }
    for (int i = 1; i <= KMAX; i++) tree[u].e[i] = 0;
    merge_poly(tree[u].e, tree[lc].e); // 空多项式（全是 0）依次并上左右儿子
    merge_poly(tree[u].e, tree[rc].e);
}

// 建树：叶子就是一个 V，它的一次初等对称和就是 V 本身
void build(int u, int l, int r) {
    if (l == r) {
        for (int i = 1; i <= KMAX; i++) tree[u].e[i] = 0;
        tree[u].e[1] = a[l].v;
        tree[u].min_v = a[l].v;
        tree[u].min_pos = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pull(u);
}

u32 cur_min_v; // 询问区间内最小的 V
int cur_min_pos; // 它的下标

// 查 [ql, qr] 内最小的 V 及其位置：V 互不相同，所以位置唯一
void query_min(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        if (tree[u].min_v < cur_min_v) {
            cur_min_v = tree[u].min_v;
            cur_min_pos = tree[u].min_pos;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) query_min(u << 1, l, mid, ql, qr);
    if (mid < qr) query_min(u << 1 | 1, mid + 1, r, ql, qr);
}

// 把 [ql, qr] 的整段多项式并进 acc（acc 从「空集」的多项式开始累乘）
void query_poly(int u, int l, int r, int ql, int qr, u32 acc[]) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        merge_poly(acc, tree[u].e);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) query_poly(u << 1, l, mid, ql, qr, acc);
    if (mid < qr) query_poly(u << 1 | 1, mid + 1, r, ql, qr, acc);
}

// 在按 D 升序的数组里找第一个 D >= x 的位置，都小于 x 时返回 n + 1
int first_ge(ll x) {
    int lo = 1, hi = n + 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (a[mid].d < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

// 在按 D 升序的数组里找最后一个 D <= x 的位置，都大于 x 时返回 0
int last_le(ll x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (a[mid].d <= x) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

bool cmp_d(const Area &x, const Area &y) { return x.d < y.d; }

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i].d);
    for (int i = 1; i <= n; i++) scanf("%u", &a[i].v);

    sort(a + 1, a + n + 1, cmp_d);
    build(1, 1, n);

    // fac[k] = k!，因为「有次序地挑 K 块」把每种组合算了 K! 次
    u32 fac[KMAX + 1];
    fac[0] = 1;
    for (int i = 1; i <= KMAX; i++) fac[i] = fac[i - 1] * (u32)i;

    for (int t = 0; t < q; t++) {
        ll L, R;
        int K;
        scanf("%lld %lld %d", &L, &R, &K);

        int l = first_ge(L), r = last_le(R);
        // 可选区域不足 K 块（还要先排除掉 V 最小的那一块，所以至少要 K + 1 块）
        if (l > r || r - l + 1 <= K) {
            printf("0\n");
            continue;
        }

        cur_min_v = 0xFFFFFFFFu;
        cur_min_pos = -1;
        query_min(1, 1, n, l, r);
        u32 min_v = cur_min_v;

        // poly[i] = 区间内 V 的 i 次初等对称和（i = 0..K）
        u32 poly[KMAX + 1];
        for (int i = 0; i <= KMAX; i++) poly[i] = 0;
        query_poly(1, 1, n, l, r, poly);

        // 去掉 V 最小的那一块：整段多项式 U(y) = Π(1 + V_i·y)，
        // 去掉因子 (1 + min_v·y) 等价于乘上它的形式逆 1 - min_v·y + min_v²·y² - ...
        // 于是「去掉最小块后」的 K 次对称和 A_K = Σ_{j=0}^{K} (-min_v)^j · E_{K-j}（E_0 = 1）
        u32 res = 0, pw = 1; // pw = (-min_v)^j
        for (int j = 0; j <= K; j++) {
            u32 ek = (j == K) ? 1 : poly[K - j];
            res += pw * ek;
            pw *= (0u - min_v);
        }

        printf("%u\n", res * fac[K]); // fac[K] 把组合还原成有次序的选取
    }
    return 0;
}
