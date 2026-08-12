/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:14
 */
#include <bits/stdc++.h>
using namespace std;

// 仿照 rbook 模板 segtree-range-assign 的 pull/apply/push 结构，
// 把「区间赋值」扩展成「区间赋值 + 区间加」双懒标记：
// 赋值标记会覆盖旧的加法标记，加法若遇到赋值标记则改写赋值标记，
// 下传时顺序固定为「先赋值、后加法」。
template <typename T>
struct SegmentTreeAssignAddMax {
    int n = 0;
    vector<T> tree;        // tree[p] 表示节点 p 区间的最大值
    vector<T> add_lazy;    // add_lazy[p] 表示节点 p 区间整体还要加多少（未下传）
    vector<T> set_lazy;    // set_lazy[p] 表示节点 p 区间整体被赋成什么值（未下传）
    vector<bool> has_set;  // has_set[p] 表示节点 p 是否有未下传的赋值标记

    SegmentTreeAssignAddMax(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, 0);
        add_lazy.assign(n * 4 + 5, 0);
        set_lazy.assign(n * 4 + 5, 0);
        has_set.assign(n * 4 + 5, false);
    }

    // 用两个儿子的最大值合并出父节点的最大值。
    void pull(int p) {
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
    }

    // 把节点 p 的整段区间赋值为 value：
    // 最大值直接变成 value，旧的加法标记被赋值覆盖，只留下赋值标记。
    void apply_set(int p, T value) {
        tree[p] = value;
        set_lazy[p] = value;
        add_lazy[p] = 0;
        has_set[p] = true;
    }

    // 给节点 p 的整段区间加上 value：
    // 最大值直接加 value；若已有赋值标记，等价于整体赋成 (赋值 + value)，
    // 所以改写 set_lazy；否则累加到加法标记上。
    void apply_add(int p, T value) {
        tree[p] += value;
        if (has_set[p])
            set_lazy[p] += value;
        else
            add_lazy[p] += value;
    }

    // 下传节点 p 的懒标记：必须先传赋值、再传加法，儿子才能得到正确复合结果。
    void push(int p, int l, int r) {
        if (l == r) return;

        if (has_set[p]) {
            apply_set(p << 1, set_lazy[p]);
            apply_set(p << 1 | 1, set_lazy[p]);
            has_set[p] = false;
        }
        if (add_lazy[p] != 0) {
            apply_add(p << 1, add_lazy[p]);
            apply_add(p << 1 | 1, add_lazy[p]);
            add_lazy[p] = 0;
        }
    }

    // 用初始数组 a 建树，叶子存单点值。
    void build(const vector<T> &a, int l, int r, int p = 1) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(a, l, mid, p << 1);
        build(a, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 把区间 [ql, qr] 整体赋值为 value。
    void assign_range(int ql, int qr, T value, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply_set(p, value);
            return;
        }

        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) assign_range(ql, qr, value, l, mid, p << 1);
        if (qr > mid) assign_range(ql, qr, value, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 给区间 [ql, qr] 整体加上 value。
    void add_range(int ql, int qr, T value, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply_add(p, value);
            return;
        }

        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) add_range(ql, qr, value, l, mid, p << 1);
        if (qr > mid) add_range(ql, qr, value, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 查询区间 [ql, qr] 的最大值。
    T query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];

        push(p, l, r);
        int mid = (l + r) >> 1;
        // 初值取很小的数，保证全负数区间也能正确取 max。
        T answer = -(1LL << 60);
        if (ql <= mid) answer = max(answer, query(ql, qr, l, mid, p << 1));
        if (qr > mid) answer = max(answer, query(ql, qr, mid + 1, r, p << 1 | 1));
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTreeAssignAddMax<long long> seg(n);
    seg.build(a, 1, n);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.assign_range(l, r, x, 1, n);
        } else if (op == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.add_range(l, r, x, 1, n);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r, 1, n) << '\n';
        }
    }

    return 0;
}
