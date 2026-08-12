/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 21:54
 * update_at: 2026-08-12 21:54
 */
#include <bits/stdc++.h>
using namespace std;

// 仿照 rbook 模板 segtree-range-assign 的 pull/apply/push 结构，
// 把「区间赋值」改为「区间翻转」：整段数量取反，懒标记用 bool 异或。
struct SegmentTreeRangeFlip {
    int n = 0;
    vector<int> tree;   // tree[p] 表示节点 p 区间内亮灯的数量
    vector<bool> lazy;  // lazy[p] 表示节点 p 区间是否整段待翻转

    SegmentTreeRangeFlip(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, 0); // 初始全灭，整棵树隐含为全 0，不需要 build
        lazy.assign(n * 4 + 5, false);
    }

    // 把两个儿子的信息合并回父节点。
    void pull(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }

    // 把节点 p 代表的整段区间 [l, r] 翻转：亮灯数量变为 长度 - 亮灯数量。
    void apply(int p, int l, int r) {
        tree[p] = (r - l + 1) - tree[p];
        lazy[p] = !lazy[p];
    }

    // 下传节点 p 的翻转懒标记到两个儿子。
    void push(int p, int l, int r) {
        if (!lazy[p] || l == r) return;

        int mid = (l + r) >> 1;
        apply(p << 1, l, mid);
        apply(p << 1 | 1, mid + 1, r);
        lazy[p] = false;
    }

    // 把区间 [ql, qr] 整体取反。
    void flip_range(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, l, r);
            return;
        }

        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) flip_range(ql, qr, l, mid, p << 1);
        if (qr > mid) flip_range(ql, qr, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 查询区间 [ql, qr] 内亮灯的数量。
    int query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];

        push(p, l, r);
        int mid = (l + r) >> 1;
        int answer = 0;
        if (ql <= mid) answer += query(ql, qr, l, mid, p << 1);
        if (qr > mid) answer += query(ql, qr, mid + 1, r, p << 1 | 1);
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTreeRangeFlip seg(n); // 初始全部关着，无需 build

    while (m--) {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 0)
            seg.flip_range(a, b, 1, n);
        else
            cout << seg.query(a, b, 1, n) << '\n';
    }

    return 0;
}
