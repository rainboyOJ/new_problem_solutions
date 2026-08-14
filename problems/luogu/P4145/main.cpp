/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 00:00
 * update_at: 2026-08-15 22:40
 */
// main.cpp：区间开根号（下取整）+ 区间求和。
// 线段树节点维护区间和与最大值，最大值 <= 1 时剪枝跳过整段，不需要懒标记。
#include <bits/stdc++.h>
using namespace std;

// 计算 x 的下取整平方根。
// double 开方可能有一点点误差，用两次乘法把结果校正到正确区间。
long long isqrt_safe(long long x) {
    long long r = (long long)sqrt((double)x);
    while ((r + 1) * (r + 1) <= x) r++;
    while (r * r > x) r--;
    return r;
}

// 区间开方 + 区间求和线段树（最大值剪枝，无懒标记）
struct SegmentTreeSqrt {
    using T = long long;

    // 线段树节点：sum 为区间和，mx 为区间最大值
    struct Node {
        T sum = 0;    // 当前区间的区间和
        T mx = 0;     // 当前区间的最大值

        // 合并两个孩子：和相加，最大值取较大者
        Node operator+(const Node &other) const {
            return Node{sum + other.sum, max(mx, other.mx)};
        }
    };

    // 左儿子 / 右儿子的节点编号
    static int lson(int p) { return p << 1; }
    static int rson(int p) { return p << 1 | 1; }

    // 区间 [l, r] 的中点
    static int mid(int l, int r) { return (l + r) >> 1; }

    int n = 0;              // 区间大小
    vector<Node> tree;      // 线段树数组

    SegmentTreeSqrt(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, Node{});
    }

    // 上推：用两个孩子合并出当前节点
    void push_up(int p) {
        tree[p] = tree[lson(p)] + tree[rson(p)];
    }

    // 用数组 a 建树
    void build(const vector<T> &a, int l, int r, int p = 1) {
        if (l == r) {
            tree[p].sum = tree[p].mx = a[l];
            return;
        }
        int m = mid(l, r);
        build(a, l, m, lson(p));
        build(a, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间开方：把 [ql, qr] 内每个数执行一次下取整开方。
    // 剪枝：开方单调不减，区间最大值不超过 1 时整段全是 0/1，开方后不变，直接跳过。
    void sqrt_update(int ql, int qr, int l, int r, int p = 1) {
        if (tree[p].mx <= 1) return;

        if (l == r) {
            // 真正落到叶子，执行一次开方并同步最大值。
            tree[p].sum = tree[p].mx = isqrt_safe(tree[p].sum);
            return;
        }

        int m = mid(l, r);
        if (ql <= m) sqrt_update(ql, qr, l, m, lson(p));
        if (qr > m) sqrt_update(ql, qr, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间查询：[ql, qr] 的区间和
    T query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p].sum;

        int m = mid(l, r);
        T answer = 0;
        if (ql <= m) answer += query(ql, qr, l, m, lson(p));
        if (qr > m) answer += query(ql, qr, m + 1, r, rson(p));
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTreeSqrt seg(n);
    seg.build(a, 1, n);

    cin >> m;
    while (m--) {
        int k, l, r;
        cin >> k >> l >> r;
        // 数据中有可能 l > r，遇到这种情况需要交换。
        if (l > r) swap(l, r);
        if (k == 0)
            seg.sqrt_update(l, r, 1, n); // 区间开根号
        else
            cout << seg.query(l, r, 1, n) << '\n'; // 区间求和
    }

    return 0;
}
