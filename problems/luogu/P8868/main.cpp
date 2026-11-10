/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:57
 * update_at: 2026-11-11 00:57
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using u64 = unsigned long long;
const int MAXN = 250005;

int tid, n, q_cnt;
int a[MAXN], b[MAXN];
int stk_a[MAXN], top_a = 0;
int stk_b[MAXN], top_b = 0;

struct Query {
    int l;
    int id;
};
vector<Query> queries[MAXN];
u64 ans[MAXN];

// 线段树节点信息与历史版本懒标记
struct Info {
    u64 len, asum, bsum, absum, hsum;
    Info() : len(0), asum(0), bsum(0), absum(0), hsum(0) {}
};

struct Tag {
    u64 wa, wb, ws, hl, ha, hb, hs;
    Tag() : wa(0), wb(0), ws(0), hl(0), ha(0), hb(0), hs(0) {}
    Tag(u64 a_, u64 b_, u64 c_, u64 d_, u64 e_, u64 f_, u64 g_)
        : wa(a_), wb(b_), ws(c_), hl(d_), ha(e_), hb(f_), hs(g_) {}

    bool empty() const {
        return !wa && !wb && !ws && !hl && !ha && !hb && !hs;
    }
};

Info operator+(const Info& x, const Info& y) {
    Info res;
    res.len = x.len + y.len;
    res.asum = x.asum + y.asum;
    res.bsum = x.bsum + y.bsum;
    res.absum = x.absum + y.absum;
    res.hsum = x.hsum + y.hsum;
    return res;
}

Tag operator+(const Tag& x, const Tag& y) {
    Tag res;
    res.wa = x.wa + y.wa;
    res.wb = x.wb + y.wb;
    res.ws = x.ws + y.ws + x.wa * y.wb + x.wb * y.wa;
    res.hl = x.hl + y.hl + x.wa * y.ha + x.wb * y.hb + x.ws * y.hs;
    res.ha = x.ha + y.ha + x.wb * y.hs;
    res.hb = x.hb + y.hb + x.wa * y.hs;
    res.hs = x.hs + y.hs;
    return res;
}

Info operator+(const Info& x, const Tag& y) {
    Info res;
    res.len = x.len;
    res.asum = x.asum + x.len * y.wa;
    res.bsum = x.bsum + x.len * y.wb;
    res.absum = x.absum + x.len * y.ws + x.asum * y.wb + x.bsum * y.wa;
    res.hsum = x.hsum + x.len * y.hl + x.asum * y.ha + x.bsum * y.hb + x.absum * y.hs;
    return res;
}

Info tree[MAXN << 2];
Tag tag[MAXN << 2];

inline void push_up(int p) {
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

inline void apply_tag(int p, const Tag& v) {
    tree[p] = tree[p] + v;
    tag[p] = tag[p] + v;
}

inline void push_down(int p) {
    if (!tag[p].empty()) {
        apply_tag(p << 1, tag[p]);
        apply_tag(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }
}

void build(int p, int l, int r) {
    tree[p].len = r - l + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void update(int p, int l, int r, int ql, int qr, const Tag& v) {
    if (ql <= l && r <= qr) {
        apply_tag(p, v);
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
    push_up(p);
}

Info query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[p];
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (qr <= mid) return query(p << 1, l, mid, ql, qr);
    if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
    return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> tid >> n)) return 0;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    cin >> q_cnt;
    for (int i = 1; i <= q_cnt; ++i) {
        int l, r;
        cin >> l >> r;
        queries[r].push_back({l, i});
    }

    build(1, 1, n);

    for (int i = 1; i <= n; ++i) {
        // 单调栈维护序列 a 的区间加
        while (top_a && a[i] > a[stk_a[top_a]]) {
            int prev_idx = stk_a[top_a];
            int left_bound = stk_a[top_a - 1] + 1;
            update(1, 1, n, left_bound, prev_idx, Tag(a[i] - a[prev_idx], 0, 0, 0, 0, 0, 0));
            top_a--;
        }
        update(1, 1, n, i, i, Tag(a[i], 0, 0, 0, 0, 0, 0));
        stk_a[++top_a] = i;

        // 单调栈维护序列 b 的区间加
        while (top_b && b[i] > b[stk_b[top_b]]) {
            int prev_idx = stk_b[top_b];
            int left_bound = stk_b[top_b - 1] + 1;
            update(1, 1, n, left_bound, prev_idx, Tag(0, b[i] - b[prev_idx], 0, 0, 0, 0, 0));
            top_b--;
        }
        update(1, 1, n, i, i, Tag(0, b[i], 0, 0, 0, 0, 0));
        stk_b[++top_b] = i;

        // 全局时间前进一步：将当前 ab 累加到历史版本和 hsum 中
        update(1, 1, n, 1, i, Tag(0, 0, 0, 0, 0, 0, 1));

        // 回答以当前 i 为右端点的所有询问
        for (const auto& q : queries[i]) {
            Info res = query(1, 1, n, q.l, i);
            ans[q.id] = res.hsum;
        }
    }

    for (int i = 1; i <= q_cnt; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
