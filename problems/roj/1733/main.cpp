/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 19:20
 * update_at: 2026-10-07 19:20
 */

// 连续数字区间：扫右端点 + 线段树维护「左端点的相邻值对数」
//
// 记 cnt(l, r) 为满足「值 v 与 v+1 都落在 [l, r] 内」的 v 的个数。排列内部的值互不相同，
// 把它排序后相邻两数之差全为 1 ⟺ 这样的 v 恰有 r - l 个，故
//     [l, r] 连续 ⟺ l + cnt(l, r) == r。
// 于是扫右端点 i = 1..n，只维护关于左端点 l 的 mx[l] = l + cnt(l, i)：加入 a[i] = w 时，
// 值对 (w-1, w)、(w, w+1) 中「两端下标都不超过 i」的那些，会让所有 l <= 较小下标 的
// mx[l] 加一（一次前缀加）。mx[l] <= i 恒成立，且 mx[l] == i ⟺ [l, i] 连续。
// 询问按右端点 y 分桶，扫到 i 时把 y == i 的询问按 x 从大到小检查：x 最大的都做不到，
// 其余 x 更小的更做不到。前缀加 + 前缀最大用差分数组换成单点加 + 最大前缀和。
//
// 复杂度：O((n + m) log n) 时间、O(n + m) 空间。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const ll NEG = -1000000000;  // 空节点的哨兵：绝不可能被选为最大前缀和

ll n, m;
ll a[MAXN];           // 输入排列，下标 1..n
ll pos_of_val[MAXN];  // pos_of_val[v]：值 v 在排列中的下标

// 线段树节点：维护差分数组 d 的一段，d 的前缀和就是 mx[l]
struct SegNode {
    ll sum;   // 这一段 d 的和
    ll best;  // 这一段内「从本段左端起算的前缀和」的最大值，即这一段里 mx 的最大值
    ll arg;   // 取到 best 的最大的 l（1-based）
};
SegNode seg[MAXN * 4];

struct Ask {
    ll x;   // 询问左端点
    ll id;  // 询问编号
};

struct Answer {
    ll l;   // 最短连续区间的左端点
    ll r;   // 最短连续区间的右端点
};

vector<Ask> by_y[MAXN];                  // by_y[y]：右端点为 y 的全部询问
priority_queue<pair<ll, ll> > heap_ask;  // (x, id) 大根堆，按 x 从大到小结算
Answer ans[MAXN];                        // 每个询问的答案

// 按从左到右的顺序把两段合并成一段；前缀和最大值平手时取更大的 l（即右段的答案）。
SegNode merge_node(const SegNode &left_part, const SegNode &right_part) {
    SegNode res;
    res.sum = left_part.sum + right_part.sum;
    if (left_part.sum + right_part.best >= left_part.best) {
        res.best = left_part.sum + right_part.best;
        res.arg = right_part.arg;
    } else {
        res.best = left_part.best;
        res.arg = left_part.arg;
    }
    return res;
}

// 由两个孩子重算节点 now。
void pull_up(ll now) {
    seg[now] = merge_node(seg[now << 1], seg[now << 1 | 1]);
}

// 建树：d 的初值全为 1，此时 mx[l] = l。
void build(ll now, ll l, ll r) {
    if (l == r) {
        seg[now].sum = 1;
        seg[now].best = 1;
        seg[now].arg = l;
        return;
    }
    ll mid = (l + r) >> 1;
    build(now << 1, l, mid);
    build(now << 1 | 1, mid + 1, r);
    pull_up(now);
}

// 给 d[pos] 加上 c（单点加），并自底向上重算沿途节点。
void point_add(ll now, ll l, ll r, ll pos, ll c) {
    if (l == r) {
        seg[now].sum += c;
        seg[now].best += c;
        return;
    }
    ll mid = (l + r) >> 1;
    if (pos <= mid) point_add(now << 1, l, mid, pos, c);
    else point_add(now << 1 | 1, mid + 1, r, pos, c);
    pull_up(now);
}

// 询问 l ∈ [1, x] 内 mx[l] 的最大值以及取到它的最大 l。
SegNode query_prefix(ll now, ll l, ll r, ll x) {
    if (r <= x) return seg[now];
    ll mid = (l + r) >> 1;
    if (x <= mid) return query_prefix(now << 1, l, mid, x);
    return merge_node(seg[now << 1], query_prefix(now << 1 | 1, mid + 1, r, x));
}

// 把 mx[1..p] 全部加一：差分数组 d 上只需 d[1] += 1、d[p+1] -= 1。
void add_prefix(ll p) {
    point_add(1, 1, n, 1, 1);
    if (p < n) point_add(1, 1, n, p + 1, -1);
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        pos_of_val[a[i]] = i;
    }
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        Ask ask;
        ll y;
        cin >> ask.x >> y;
        ask.id = i;
        by_y[y].push_back(ask);
    }
}

void solve() {
    build(1, 1, n);
    for (ll i = 1; i <= n; i++) {
        ll w = a[i];
        // 值对 (w-1, w) 与 (w, w+1)：另一端的下标不超过 i 时，从 i 起对每个
        // l <= 那个下标 的区间 [l, i] 都成立，于是给前缀 [1, 那个下标] 加一。
        if (w - 1 >= 1 && pos_of_val[w - 1] <= i) add_prefix(pos_of_val[w - 1]);
        if (w + 1 <= n && pos_of_val[w + 1] <= i) add_prefix(pos_of_val[w + 1]);

        for (size_t j = 0; j < by_y[i].size(); j++) {
            heap_ask.push(make_pair(by_y[i][j].x, by_y[i][j].id));
        }
        // 堆顶是 x 最大的询问；它都做不到时，x 更小的询问更做不到。
        while (!heap_ask.empty()) {
            pair<ll, ll> top = heap_ask.top();
            SegNode res = query_prefix(1, 1, n, top.first);
            if (res.best != i) break;
            ans[top.second].l = res.arg;
            ans[top.second].r = i;
            heap_ask.pop();
        }
    }
    for (ll i = 1; i <= m; i++) cout << ans[i].l << ' ' << ans[i].r << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
