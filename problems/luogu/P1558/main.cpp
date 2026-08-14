/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-14 09:00
 */
// P1558 [USACO09OPEN] Count Color S
// 区间赋值 + 区间颜色集合查询（按位或合并）线段树（懒标记）
#include <bits/stdc++.h>
using namespace std;

// 区间赋值 + 区间颜色集合查询线段树（懒标记）
struct SegmentTreeColor {
    // 线段树节点：value 为区间颜色集合掩码，lazy 为待下传的涂色标记
    using T = int;
    struct Node {
        T value = 0;    // 当前区间的真实颜色集合掩码
        T lazy = 0;     // 待下传的涂色值（单色掩码）
        bool has_lazy = false;  // 是否还有未下传的涂色标记

        // 合并两个孩子：颜色集合并集，合并结果不携带懒标记
        Node operator|(const Node &other) const {
            return Node{value | other.value, 0, false};
        }
    };

    // 左儿子 / 右儿子的节点编号
    static int lson(int p) { return p << 1; }
    static int rson(int p) { return p << 1 | 1; }

    // 区间 [l, r] 的中点
    static int mid(int l, int r) { return (l + r) >> 1; }

    int n = 0;              // 区间大小
    vector<Node> tree;      // 线段树数组

    SegmentTreeColor(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, Node{});
    }

    // 上推：用两个孩子合并出当前节点
    void push_up(int p) {
        tree[p] = tree[lson(p)] | tree[rson(p)];
    }

    // 把节点 p 的整个区间 [l, r] 涂成颜色 value（单色掩码）。
    // 整段变成一种颜色后，集合就是该掩码本身，与区间长度无关，
    // 所以与模板 value * len 的写法不同。
    void apply(int p, int, int, T value) {
        tree[p].value = value;
        tree[p].lazy = value;
        tree[p].has_lazy = true;
    }

    // 下推：把节点 p 的懒标记传给两个孩子
    void push_down(int p, int l, int r) {
        if (!tree[p].has_lazy || l == r) return;

        int m = mid(l, r);
        apply(lson(p), l, m, tree[p].lazy);
        apply(rson(p), m + 1, r, tree[p].lazy);
        tree[p].has_lazy = false;
    }

    // 用数组 a 建树（a[i] 是位置 i 的颜色集合掩码，这里全部是颜色 1）
    void build(const vector<T> &a, int l, int r, int p = 1) {
        if (l == r) {
            tree[p].value = a[l];
            return;
        }
        int m = mid(l, r);
        build(a, l, m, lson(p));
        build(a, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间涂色：把 [ql, qr] 全部涂成颜色 value（单色掩码）
    void assign_range(int ql, int qr, T value, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, l, r, value);
            return;
        }

        push_down(p, l, r);
        int m = mid(l, r);
        if (ql <= m) assign_range(ql, qr, value, l, m, lson(p));
        if (qr > m) assign_range(ql, qr, value, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间查询：[ql, qr] 内出现的颜色集合掩码
    T query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p].value;

        push_down(p, l, r);
        int m = mid(l, r);
        T answer = 0;
        if (ql <= m) answer |= query(ql, qr, l, m, lson(p));
        if (qr > m) answer |= query(ql, qr, m + 1, r, rson(p));
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, T, O;
    cin >> L >> T >> O;

    // 初始整块板都是颜色 1，每个位置的颜色集合掩码都是 1
    vector<int> a(L + 1, 1);

    SegmentTreeColor seg(L);
    seg.build(a, 1, L);

    while (O--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (a > b) swap(a, b); // 题目不保证 a <= b，需要交换
        if (op == 'C') {
            int c;
            cin >> c;
            seg.assign_range(a, b, 1 << (c - 1), 1, L); // 颜色 c 用第 c-1 位表示
        } else {
            int mask = seg.query(a, b, 1, L);
            cout << __builtin_popcount((unsigned)mask) << '\n'; // 置位数 = 颜色种类数
        }
    }

    return 0;
}
