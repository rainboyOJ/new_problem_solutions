#include <bits/stdc++.h>
using namespace std;

// 题意：维护非负序列 A，支持单点改值，以及「从 l 往右/从 r 往左的前缀和
// 第一次达到 t 的位置」。
//
// 关键转化：记前缀和 P[i] = A[1] + ... + A[i]，则
//   查询 2：求最小的 r >= l 使 P[r] >= P[l-1] + t；
//   查询 3：求最大的 l <= r 使 P[l-1] <= P[r] - t，输出 l = 那个下标 + 1。
// 单点改 A[i] 等价于把 P[i..n] 整体加上 d，是区间加。于是问题变成
// 「区间加 + 线段树上二分找第一个 >= x 的位置 / 最后一个 <= x 的位置」。
//
// 因为 A 非负，P 单调不减，第二个二分等价于找「第一个 > P[r]-t」的位置再减一，
// 但这里直接在 P 上维护区间最大值和最小值做二分，不依赖单调性也能写对。

int n, q;

// 区间加 + 区间最值线段树
struct SegmentTree {
    using T = long long;

    struct Node {
        T mx = 0;  // 当前区间最大值
        T mn = 0;  // 当前区间最小值
    };

    static int lson(int p) { return p << 1; }
    static int rson(int p) { return p << 1 | 1; }
    static int mid(int l, int r) { return (l + r) >> 1; }

    int n = 0;
    vector<Node> tree;
    vector<T> lazy;  // 整段加法的懒标记

    SegmentTree(int n = 0) { init(n); }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, Node{});
        lazy.assign(n * 4 + 5, 0);
    }

    void apply(int p, T v) {
        tree[p].mx += v;
        tree[p].mn += v;
        lazy[p] += v;
    }

    void push_down(int p) {
        if (lazy[p] != 0) {
            apply(lson(p), lazy[p]);
            apply(rson(p), lazy[p]);
            lazy[p] = 0;
        }
    }

    void push_up(int p) {
        tree[p].mx = max(tree[lson(p)].mx, tree[rson(p)].mx);
        tree[p].mn = min(tree[lson(p)].mn, tree[rson(p)].mn);
    }

    void build(const vector<T> &a, int l, int r, int p = 1) {
        if (l == r) {
            tree[p].mx = tree[p].mn = a[l];
            return;
        }
        int m = mid(l, r);
        build(a, l, m, lson(p));
        build(a, m + 1, r, rson(p));
        push_up(p);
    }

    // 给 [ql, qr] 每个元素加上 v
    void add(int ql, int qr, T v, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, v);
            return;
        }
        push_down(p);
        int m = mid(l, r);
        if (ql <= m) add(ql, qr, v, l, m, lson(p));
        if (qr > m) add(ql, qr, v, m + 1, r, rson(p));
        push_up(p);
    }

    // 单点查询
    T point(int pos, int l, int r, int p = 1) {
        if (l == r) return tree[p].mx;
        push_down(p);
        int m = mid(l, r);
        if (pos <= m) return point(pos, l, m, lson(p));
        return point(pos, m + 1, r, rson(p));
    }

    // 最小的下标 i >= ql 且 P[i] >= target；不存在返回 -1。
    // 超出 ql 的区间最大值都够不到 target 时整段剪掉。
    int first_ge(int ql, T target, int l, int r, int p = 1) {
        if (r < ql || tree[p].mx < target) return -1;
        if (l == r) return l;
        push_down(p);
        int m = mid(l, r);
        int res = first_ge(ql, target, l, m, lson(p));
        if (res != -1) return res;
        return first_ge(ql, target, m + 1, r, rson(p));
    }

    // 最大的下标 i <= qr 且 P[i] <= target；不存在返回 -1。
    int last_le(int qr, T target, int l, int r, int p = 1) {
        if (l > qr || tree[p].mn > target) return -1;
        if (l == r) return l;
        push_down(p);
        int m = mid(l, r);
        int res = last_le(qr, target, m + 1, r, rson(p));
        if (res != -1) return res;
        return last_le(qr, target, l, m, lson(p));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<long long> a(n + 1, 0);
    vector<long long> pre(n + 1, 0);  // pre[i] = A[1..i] 的和
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    // 下标范围 0..n，其中 0 表示空前缀。
    SegmentTree seg(n + 1);
    seg.build(pre, 0, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            long long x;
            cin >> i >> x;
            long long delta = x - a[i];
            a[i] = x;
            // A[i] 变了，前缀和 pre[i..n] 整体平移 delta。
            if (delta != 0) seg.add(i, n, delta, 0, n);
        } else if (op == 2) {
            int l;
            long long t;
            cin >> l >> t;
            // 要求 sum(A[l..r]) >= t，即 pre[r] >= pre[l-1] + t。
            long long base = seg.point(l - 1, 0, n);
            int r = seg.first_ge(l, base + t, 0, n);
            cout << (r == -1 ? n + 1 : r) << '\n';
        } else {
            int r;
            long long t;
            cin >> r >> t;
            // 要求 sum(A[l..r]) >= t，即 pre[l-1] <= pre[r] - t。
            long long target = seg.point(r, 0, n) - t;
            int j = seg.last_le(r - 1, target, 0, n);
            cout << (j == -1 ? 0 : j + 1) << '\n';
        }
    }

    return 0;
}
