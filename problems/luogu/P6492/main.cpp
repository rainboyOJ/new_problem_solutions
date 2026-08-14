/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-13 11:42
 */
#include <bits/stdc++.h>
using namespace std;

// 节点信息从「区间和」换成「最长交替段」五元组：两端字符 + 最长交替前后缀 + 段内最优。
struct SegmentTreeAlternating {
    // 线段树节点：最长交替段五元组。
    struct Node {
        int first; // 区间左端的字符值（0 表示 L，1 表示 R）
        int last;  // 区间右端的字符值
        int pref;  // 从区间左端起的最长交替段长
        int suff;  // 到区间右端止的最长交替段长
        int best;  // 区间内最长交替段长度
    };

    int n = 0;
    vector<Node> tree; // tree[p] 表示节点 p 的五元组信息

    SegmentTreeAlternating(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n * 4 + 5, Node{0, 0, 0, 0, 0});
    }

    // 用左右儿子的信息合并出父节点信息。
    // len_left / len_right 是左右子区间的长度，用于判断某半段是否「整段交替」。
    void push_up(int p, int len_left, int len_right) {
        int left = p << 1, right = p << 1 | 1;
        bool different = (tree[left].last != tree[right].first); // 跨中点的相邻边界是否交替
        tree[p].first = tree[left].first;
        tree[p].last = tree[right].last;

        // 左子整段交替且跨中点边界交替时，前缀可以延伸进右子区间
        if (different && tree[left].pref == len_left)
            tree[p].pref = len_left + tree[right].pref;
        else
            tree[p].pref = tree[left].pref;

        // 右子整段交替且跨中点边界交替时，后缀可以延伸进左子区间
        if (different && tree[right].suff == len_right)
            tree[p].suff = len_right + tree[left].suff;
        else
            tree[p].suff = tree[right].suff;

        // 段内最优：左、右两半各自的最优，或跨过中点的前后缀拼接
        tree[p].best = max(tree[left].best, tree[right].best);
        if (different)
            tree[p].best = max(tree[p].best, tree[left].suff + tree[right].pref);
    }

    // 建树：初始全部为 L（0），单点交替段长度就是 1。
    void build(int l, int r, int p = 1) {
        if (l == r) {
            tree[p].first = tree[p].last = 0;
            tree[p].pref = tree[p].suff = tree[p].best = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        push_up(p, mid - l + 1, r - mid);
    }

    // 翻转位置 pos：叶子 0/1 取反，再沿路径重新合并所有祖先。
    void flip(int pos, int l, int r, int p = 1) {
        if (l == r) {
            tree[p].first ^= 1; // L 变 R 或 R 变 L
            tree[p].last = tree[p].first;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            flip(pos, l, mid, p << 1);
        else
            flip(pos, mid + 1, r, p << 1 | 1);
        push_up(p, mid - l + 1, r - mid);
    }

    // 整个序列的最长交替段长度。
    int get_best() const {
        return tree[1].best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    SegmentTreeAlternating seg(n);
    seg.build(1, n);

    while (q--) {
        int x;
        cin >> x;
        seg.flip(x, 1, n);
        cout << seg.get_best() << '\n';
    }

    return 0;
}
