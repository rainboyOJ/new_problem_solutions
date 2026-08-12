/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:11
 * update_at: 2026-08-12 22:15
 */
#include <bits/stdc++.h>
using namespace std;

// P2572 [SCOI2010] 序列操作
// 五种操作：区间赋值 0 / 区间赋值 1 / 区间翻转 / 查询区间 1 的个数 / 查询区间最长连续 1。
// 仿照 rbook 模板 segtree-range-assign 的 pull / apply / push 结构改造而来。
// 题目下标从 0 开始，代码内部统一转换成 1 开始。

// 节点信息：同时维护 0 和 1 两套"前缀 / 后缀 / 最长连续段"统计量。
struct Node {
    int sum;   // 区间内 1 的个数（查询 3 的答案）
    int pref1; // 从区间左端起的最长连续 1 长度
    int suff1; // 到区间右端止的最长连续 1 长度
    int best1; // 区间内最长连续 1 长度（查询 4 的答案）
    int pref0; // 从区间左端起的最长连续 0 长度
    int suff0; // 到区间右端止的最长连续 0 长度
    int best0; // 区间内最长连续 0 长度
};

struct SegmentTree {
    int n = 0;
    vector<Node> tree;    // tree[p]：节点 p 代表的区间的一整套统计量
    vector<int> assign;   // assign[p] = -1 表示没有赋值懒标记；0/1 表示整段待赋值
    vector<bool> flip;    // flip[p] 表示是否有一整段翻转等待下传

    SegmentTree(int size = 0) {
        init(size);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, Node{});
        assign.assign(n * 4 + 5, -1);
        flip.assign(n * 4 + 5, false);
    }

    // 把左儿子 a（覆盖长度 lenL）与右儿子 b（覆盖长度 lenR）合并成一个新节点。
    // pull 与部分区间查询共用这套合并公式。
    Node merge_info(const Node &a, const Node &b, int lenL, int lenR) {
        Node x;
        x.sum = a.sum + b.sum;
        // 左半整段全是 1 时，前缀才能接到右半的前缀上，否则前缀只取左半的。
        x.pref1 = (a.pref1 == lenL) ? lenL + b.pref1 : a.pref1;
        x.suff1 = (b.suff1 == lenR) ? lenR + a.suff1 : b.suff1;
        x.best1 = max(a.best1, max(b.best1, a.suff1 + b.pref1));
        x.pref0 = (a.pref0 == lenL) ? lenL + b.pref0 : a.pref0;
        x.suff0 = (b.suff0 == lenR) ? lenR + a.suff0 : b.suff0;
        x.best0 = max(a.best0, max(b.best0, a.suff0 + b.pref0));
        return x;
    }

    // 把左右儿子的信息上推合并到父节点 p。
    void pull(int p, int l, int r) {
        int mid = (l + r) >> 1;
        tree[p] = merge_info(tree[p << 1], tree[p << 1 | 1], mid - l + 1, r - mid);
    }

    // 把节点 p 代表的整段区间赋值为 v（0 或 1），v 取 1 时长度 len 传给 1 套统计，0 同理。
    void apply_assign(int p, int v, int len) {
        tree[p].sum = v * len;
        tree[p].pref1 = tree[p].suff1 = tree[p].best1 = v * len;
        tree[p].pref0 = tree[p].suff0 = tree[p].best0 = (1 - v) * len;
        assign[p] = v;   // 赋值懒标记覆盖掉之前的翻转懒标记
        flip[p] = false;
    }

    // 把节点 p 代表的整段区间翻转：交换 1 / 0 两套统计量，1 的个数变为 len - sum。
    void apply_flip(int p, int len) {
        tree[p].sum = len - tree[p].sum;
        swap(tree[p].pref1, tree[p].pref0);
        swap(tree[p].suff1, tree[p].suff0);
        swap(tree[p].best1, tree[p].best0);
        // 懒标记优先级：赋值覆盖翻转。
        // 有赋值标记时翻转等价于把赋值目标取反；没有时才累计翻转标记。
        if (assign[p] != -1)
            assign[p] ^= 1;
        else
            flip[p] = !flip[p];
    }

    // 下传节点 p 的懒标记到两个儿子。先传赋值再传翻转（赋值覆盖翻转）。
    void push(int p, int l, int r) {
        if (l == r) return; // 叶子没有儿子，不需要下传

        int mid = (l + r) >> 1;
        if (assign[p] != -1) {
            apply_assign(p << 1, assign[p], mid - l + 1);
            apply_assign(p << 1 | 1, assign[p], r - mid);
            assign[p] = -1;
        }
        if (flip[p]) {
            apply_flip(p << 1, mid - l + 1);
            apply_flip(p << 1 | 1, r - mid);
            flip[p] = false;
        }
    }

    void build(const vector<int> &a, int l, int r, int p = 1) {
        if (l == r) {
            apply_assign(p, a[l], 1);
            assign[p] = -1; // 叶子不保留懒标记
            return;
        }
        int mid = (l + r) >> 1;
        build(a, l, mid, p << 1);
        build(a, mid + 1, r, p << 1 | 1);
        pull(p, l, r);
    }

    // 区间操作：kind = 0 赋值 0，kind = 1 赋值 1，kind = 2 翻转。
    void update(int ql, int qr, int kind, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) { // 整段命中，就地结算并打懒标记
            if (kind == 2)
                apply_flip(p, r - l + 1);
            else
                apply_assign(p, kind, r - l + 1);
            return;
        }
        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(ql, qr, kind, l, mid, p << 1);
        if (qr > mid) update(ql, qr, kind, mid + 1, r, p << 1 | 1);
        pull(p, l, r);
    }

    // 区间查询：返回覆盖 [ql, qr] 的统计量，sum 是 1 的个数、best1 是最长连续 1。
    Node query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];
        push(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(ql, qr, l, mid, p << 1);
        if (ql > mid) return query(ql, qr, mid + 1, r, p << 1 | 1);
        // 查询区间跨两个儿子：分别查询后再合并。
        // 合并用的长度必须是查询实际覆盖部分的长度（左覆盖到 mid，右从 mid+1 开始）。
        Node a = query(ql, qr, l, mid, p << 1);
        Node b = query(ql, qr, mid + 1, r, p << 1 | 1);
        return merge_info(a, b, mid - max(ql, l) + 1, min(qr, r) - mid);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTree seg(n);
    seg.build(a, 1, n);

    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        l++; // 题目下标从 0 开始，转成内部 1 开始
        r++;
        if (op <= 2) {
            seg.update(l, r, op, 1, n);
        } else {
            Node res = seg.query(l, r, 1, n);
            if (op == 3)
                cout << res.sum << '\n';   // 区间 1 的个数
            else
                cout << res.best1 << '\n'; // 区间最长连续 1
        }
    }

    return 0;
}
