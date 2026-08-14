/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-15 22:30
 */
// main.cpp：P5522 正式主解。线段树按位或合并区间的 0/1 约束，单点修改、区间查询。
#include <bits/stdc++.h>
using namespace std;

// 按位或合并区间约束的线段树（单点修改、区间查询）
struct SegmentTreeBitOr {
    // 线段树节点：zero / one 为区间内所有串的约束掩码
    struct Node {
        int zero = 0;   // 区间内被固定为 0 的位置集合（位掩码）
        int one = 0;    // 区间内被固定为 1 的位置集合（位掩码）

        // 合并两个孩子：两个掩码分别按位或，合并结果与顺序无关
        Node operator+(const Node &other) const {
            return Node{zero | other.zero, one | other.one};
        }
    };

    // 左儿子 / 右儿子的节点编号
    static int lson(int p) { return p << 1; }
    static int rson(int p) { return p << 1 | 1; }

    // 区间 [l, r] 的中点
    static int mid(int l, int r) { return (l + r) >> 1; }

    int n = 0;              // 区间大小
    vector<Node> tree;      // 线段树数组

    SegmentTreeBitOr(int n = 0) {
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

    // 把字符串 t 编码成两个位掩码：第 i 个字符对应二进制第 i 位（从 0 开始）。
    // '0' 把第 i 位置进 zero，'1' 把第 i 位置进 one，'?' 不设置任何位。
    static Node encode(const string &t) {
        int z = 0, o = 0;
        for (int i = 0; i < (int)t.size(); i++) {
            if (t[i] == '0') z |= (1 << i);
            else if (t[i] == '1') o |= (1 << i);
        }
        return Node{z, o};
    }

    // 用字符串数组 s 建树（下标从 1 开始）
    void build(const vector<string> &s, int l, int r, int p = 1) {
        if (l == r) {
            tree[p] = encode(s[l]);
            return;
        }
        int m = mid(l, r);
        build(s, l, m, lson(p));
        build(s, m + 1, r, rson(p));
        push_up(p);
    }

    // 单点修改：把位置 pos 的字符串整体替换为 t
    void modify(int pos, const string &t, int l, int r, int p = 1) {
        if (l == r) {
            tree[p] = encode(t);
            return;
        }
        int m = mid(l, r);
        if (pos <= m) modify(pos, t, l, m, lson(p));
        else modify(pos, t, m + 1, r, rson(p));
        push_up(p);
    }

    // 区间查询：返回 [ql, qr] 内所有约束 OR 合并后的结果
    Node query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return tree[p];

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

    int n, m, q;
    cin >> n >> m >> q;

    vector<string> s(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> s[i];
    }

    SegmentTreeBitOr seg(m);
    seg.build(s, 1, m);

    int ans_xor = 0; // 所有查询答案的异或和
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int pos;
            string t;
            cin >> pos >> t;
            seg.modify(pos, t, 1, m);
        } else {
            int l, r;
            cin >> l >> r;
            auto res = seg.query(l, r, 1, m);
            if ((res.zero & res.one) == 0) {
                // 无冲突：没有被任何串固定的位置都可自由选 0/1，答案 = 2^自由位个数
                int free_cnt = n - __builtin_popcount(res.zero | res.one);
                ans_xor ^= (1 << free_cnt);
            }
            // 若 zero & one != 0，某一位同时被固定为 0 和 1，答案为 0，异或 0 不变
        }
    }

    cout << ans_xor << '\n';
    return 0;
}
