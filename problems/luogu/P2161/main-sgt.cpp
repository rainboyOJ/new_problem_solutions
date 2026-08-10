/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 13:21
 * update_at: 2026-08-10 13:21
 */
#include <bits/stdc++.h>
using namespace std;

// 权值线段树版本：和 main.cpp 是同一个模型（01 桶 + 按秩查找），
// 只是把 Fenwick 换成权值线段树，kth 用"往左/往右走"实现，更直观。
// 模板来自 rbook 文章 权值线段树 (segtree-weight)。
struct WeightSegmentTree {
    struct Node {
        int left = 0;
        int right = 0;
        int sum = 0;
    };

    vector<Node> tree;
    int root = 0;
    int min_value;
    int max_value;

    WeightSegmentTree(int min_value, int max_value)
        : min_value(min_value), max_value(max_value) {
        tree.push_back(Node{});
    }

    int new_node() {
        tree.push_back(Node{});
        return (int)tree.size() - 1;
    }

    int add(int u, int l, int r, int pos, int delta) {
        if (u == 0) u = new_node();
        tree[u].sum += delta;
        if (l == r) return u;

        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            tree[u].left = add(tree[u].left, l, mid, pos, delta);
        } else {
            tree[u].right = add(tree[u].right, mid + 1, r, pos, delta);
        }
        return u;
    }

    void add(int pos, int delta) {
        root = add(root, min_value, max_value, pos, delta);
    }

    int query(int u, int l, int r, int ql, int qr) const {
        if (u == 0 || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[u].sum;

        int mid = l + (r - l) / 2;
        return query(tree[u].left, l, mid, ql, qr) +
               query(tree[u].right, mid + 1, r, ql, qr);
    }

    int count_less(int x) const {
        if (x <= min_value) return 0;
        return query(root, min_value, max_value, min_value, x - 1);
    }

    int count_leq(int x) const {
        if (x < min_value) return 0;
        if (x >= max_value) return tree[root].sum;
        return query(root, min_value, max_value, min_value, x);
    }

    // 第 k 个 1 的位置（k 从 1 开始）：左子树和 >= k 走左，否则走右。
    int kth(int u, int l, int r, int k) const {
        if (l == r) return l;

        int left_sum = tree[u].left ? tree[tree[u].left].sum : 0;
        int mid = l + (r - l) / 2;
        if (k <= left_sum) return kth(tree[u].left, l, mid, k);
        return kth(tree[u].right, mid + 1, r, k - left_sum);
    }

    int kth(int k) const {
        return kth(root, min_value, max_value, k);
    }

    int size() const {
        return root == 0 ? 0 : tree[root].sum;
    }
};

const int MAX = 100000;

int end_at[MAX + 1]; // end_at[start] 保存该起点区间的终点

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    WeightSegmentTree seg(1, MAX); // 每个起点位置是否有区间（0/1）
    int active = 0;                // 当前区间数

    int n;
    cin >> n;
    while (n--) {
        char op;
        cin >> op;
        if (op == 'B') {
            cout << active << '\n';
            continue;
        }
        int l, r;
        cin >> l >> r;
        int removed = 0;
        // 起点 <= l 的区间中，只有最后一个可能延伸到 l
        int before = seg.count_leq(l);
        if (before) {
            int start = seg.kth(before);
            if (end_at[start] >= l) {
                seg.add(start, -1);
                end_at[start] = 0;
                active--;
                removed++;
            }
        }
        // 起点 >= l 的区间，只要起点 <= r 就必然相交（终点 >= 起点 >= l）
        while (true) {
            int cnt = seg.count_less(l);
            if (cnt == seg.size()) break; // 已经没有起点 >= l 的区间
            int start = seg.kth(cnt + 1); // 第一个起点 >= l 的区间
            if (start > r) {
                break;
            }
            seg.add(start, -1);
            end_at[start] = 0;
            active--;
            removed++;
        }
        seg.add(l, 1);
        end_at[l] = r;
        active++;
        cout << removed << '\n';
    }

    return 0;
}
