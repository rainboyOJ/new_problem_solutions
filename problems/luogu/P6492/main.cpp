/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
#include <bits/stdc++.h>
using namespace std;

// 仿照 rbook 模板 segtree-point-add-range-sum 的 build/pull/flip 结构，
// 节点信息从「区间和」换成「最长交替段」五元组：两端字符 + 最长交替前后缀 + 段内最优。
struct SegmentTreeAlternating {
    int n = 0;
    vector<int> first, last; // first[p] / last[p]：节点 p 区间左端、右端的字符值（0 表示 L，1 表示 R）
    vector<int> pref, suff;  // pref[p]：从区间左端起的最长交替段长；suff[p]：到区间右端止的最长交替段长
    vector<int> best;        // best[p]：区间内最长交替段长度

    SegmentTreeAlternating(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        first.assign(n * 4 + 5, 0);
        last.assign(n * 4 + 5, 0);
        pref.assign(n * 4 + 5, 0);
        suff.assign(n * 4 + 5, 0);
        best.assign(n * 4 + 5, 0);
    }

    // 用左右儿子的信息合并出父节点信息。
    // len_left / len_right 是左右子区间的长度，用于判断某半段是否「整段交替」。
    void pull(int p, int len_left, int len_right) {
        int left = p << 1, right = p << 1 | 1;
        bool different = (last[left] != first[right]); // 跨中点的相邻边界是否交替
        first[p] = first[left];
        last[p] = last[right];

        // 左子整段交替且跨中点边界交替时，前缀可以延伸进右子区间
        if (different && pref[left] == len_left)
            pref[p] = len_left + pref[right];
        else
            pref[p] = pref[left];

        // 右子整段交替且跨中点边界交替时，后缀可以延伸进左子区间
        if (different && suff[right] == len_right)
            suff[p] = len_right + suff[left];
        else
            suff[p] = suff[right];

        // 段内最优：左、右两半各自的最优，或跨过中点的前后缀拼接
        best[p] = max(best[left], best[right]);
        if (different)
            best[p] = max(best[p], suff[left] + pref[right]);
    }

    // 建树：初始全部为 L（0），单点交替段长度就是 1。
    void build(int l, int r, int p = 1) {
        if (l == r) {
            first[p] = last[p] = 0;
            pref[p] = suff[p] = best[p] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        pull(p, mid - l + 1, r - mid);
    }

    // 翻转位置 pos：叶子 0/1 取反，再沿路径重新合并所有祖先。
    void flip(int pos, int l, int r, int p = 1) {
        if (l == r) {
            first[p] ^= 1; // L 变 R 或 R 变 L
            last[p] = first[p];
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            flip(pos, l, mid, p << 1);
        else
            flip(pos, mid + 1, r, p << 1 | 1);
        pull(p, mid - l + 1, r - mid);
    }

    // 整个序列的最长交替段长度。
    int get_best() const {
        return best[1];
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
