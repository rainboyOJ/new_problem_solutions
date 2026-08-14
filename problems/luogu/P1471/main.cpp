/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-15 22:00
 */
// main.cpp：P1471 正式解，线段树懒标记同时维护区间和与平方和，
// 支持区间加实数、查询区间平均值与方差，单次操作 O(log n)。
#include <bits/stdc++.h>
using namespace std;

// 区间加 + 区间和与平方和线段树（懒标记）
struct SegmentTreeRangeAdd {
    using T = double;

    // 线段树节点：s 为区间和，q 为平方和，lazy 为待下传的加法值
    struct Node {
        T s = 0;        // 当前区间的真实区间和 Σa[i]
        T q = 0;        // 当前区间的真实平方和 Σa[i]^2
        T lazy = 0;     // 待下传的加法值

        // 合并两个孩子：和相加、平方和相加，合并结果不携带懒标记
        Node operator+(const Node &other) const {
            return Node{s + other.s, q + other.q};
        }
    };

    // 左儿子 / 右儿子的节点编号
    static int lson(int p) { return p << 1; }
    static int rson(int p) { return p << 1 | 1; }

    // 区间 [l, r] 的中点
    static int mid(int l, int r) { return (l + r) >> 1; }

    int n = 0;              // 区间大小
    vector<Node> tree;      // 线段树数组

    SegmentTreeRangeAdd(int n = 0) {
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

    // 把节点 p 的整个区间 [l, r] 的每个元素都加上 val。
    // 平方和：Σ(a[i]+val)^2 = Σa[i]^2 + 2*val*Σa[i] + len*val^2，
    // 注意先使用旧的 s 更新 q，再更新 s。
    void apply(int p, int l, int r, T val) {
        int len = r - l + 1;
        tree[p].q += 2 * val * tree[p].s + val * val * len;
        tree[p].s += val * len;
        tree[p].lazy += val;
    }

    // 下推：把节点 p 的加法懒标记传给两个孩子
    void push_down(int p, int l, int r) {
        if (tree[p].lazy == 0 || l == r) return;

        int m = mid(l, r);
        apply(lson(p), l, m, tree[p].lazy);
        apply(rson(p), m + 1, r, tree[p].lazy);
        tree[p].lazy = 0;
    }

    // 用数组 a 建树（下标从 1 开始）
    void build(const vector<T> &a, int l, int r, int p = 1) {
        if (l == r) {
            tree[p].s = a[l];
            tree[p].q = a[l] * a[l];
            return;
        }
        int m = mid(l, r);
        build(a, l, m, lson(p));
        build(a, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间加：把 [ql, qr] 的每个元素都加上 val
    void add_range(int ql, int qr, T val, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, l, r, val);
            return;
        }

        push_down(p, l, r);
        int m = mid(l, r);
        if (ql <= m) add_range(ql, qr, val, l, m, lson(p));
        if (qr > m) add_range(ql, qr, val, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间查询：返回 [ql, qr] 的和与平方和
    Node query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];

        push_down(p, l, r);
        int m = mid(l, r);
        Node answer;
        if (ql <= m) answer = answer + query(ql, qr, l, m, lson(p));
        if (qr > m) answer = answer + query(ql, qr, m + 1, r, rson(p));
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<double> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTreeRangeAdd seg(n);
    seg.build(a, 1, n);

    cout << fixed << setprecision(4); // 输出统一保留 4 位小数

    while (m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 1) {
            double k;
            cin >> k;
            seg.add_range(l, r, k, 1, n);
        } else {
            auto res = seg.query(l, r, 1, n);
            double len = r - l + 1;
            double avg = res.s / len;   // 平均值 = Σa / len
            if (opt == 2) {
                cout << avg << '\n';
            } else {
                // 方差 = E(x^2) - (E(x))^2 = Σa^2/len - (Σa/len)^2
                cout << res.q / len - avg * avg << '\n';
            }
        }
    }

    return 0;
}
