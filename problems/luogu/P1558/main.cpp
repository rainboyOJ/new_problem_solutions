/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
#include <bits/stdc++.h>
using namespace std;

// 仿照 rbook 模板 segtree-range-assign 的 pull/apply/push 结构，
// 把「区间求和 + 区间赋值」改为「颜色集合按位或 + 区间赋值单色」：
// 每个节点用 int 位掩码记录区间内出现的颜色集合，合并用按位或。
struct SegmentTreeColor {
    int n = 0;
    vector<int> tree;      // tree[p] 表示节点 p 区间内出现的颜色集合（第 c-1 位表示颜色 c）
    vector<int> lazy;      // lazy[p] 表示整段待涂成的单色掩码（只有 1 位为 1）
    vector<bool> has_lazy; // has_lazy[p] 表示当前节点是否存有待下传的涂色标记

    SegmentTreeColor(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        // 初始整块板都是颜色 1，所以任意区间的颜色集合都是掩码 1，
        // 直接整体填 1 就等价于建树，不需要逐叶 build。
        tree.assign(n * 4 + 5, 1);
        lazy.assign(n * 4 + 5, 0);
        has_lazy.assign(n * 4 + 5, false);
    }

    // 把两个儿子的颜色集合合并回父节点：按位或。
    void pull(int p) {
        tree[p] = tree[p << 1] | tree[p << 1 | 1];
    }

    // 把节点 p 代表的整段区间涂成颜色 value（value 是单色掩码）。
    // 整段被涂成一种颜色后，区间颜色集合就是这一个掩码本身，
    // 所以这里不依赖区间长度，与模板里 tree[p] = value * len 的写法不同。
    void apply(int p, int value) {
        tree[p] = value;
        lazy[p] = value;
        has_lazy[p] = true;
    }

    // 下传节点 p 的涂色标记到两个儿子，并清空自己的标记。
    // 涂色赋值不依赖区间长度，所以 push 不需要计算 mid。
    void push(int p, int l, int r) {
        if (!has_lazy[p] || l == r) return;

        apply(p << 1, lazy[p]);
        apply(p << 1 | 1, lazy[p]);
        has_lazy[p] = false;
    }

    // 把区间 [ql, qr] 整体涂成颜色 value（单色掩码）。
    void assign_range(int ql, int qr, int value, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, value);
            return;
        }

        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) assign_range(ql, qr, value, l, mid, p << 1);
        if (qr > mid) assign_range(ql, qr, value, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 查询区间 [ql, qr] 内出现的颜色集合（返回位掩码）。
    int query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];

        push(p, l, r);
        int mid = (l + r) >> 1;
        int answer = 0;
        if (ql <= mid) answer |= query(ql, qr, l, mid, p << 1);
        if (qr > mid) answer |= query(ql, qr, mid + 1, r, p << 1 | 1);
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, T, O;
    cin >> L >> T >> O;

    SegmentTreeColor seg(L); // 初始全部是颜色 1

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
