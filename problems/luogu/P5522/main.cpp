/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 22:12
 */
// main.cpp：P5522 正式主解。线段树按位或合并区间的 0/1 约束，单点修改、区间查询。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m, q;
char s[MAXN][35];   // s[i]：第 i 年信的内容，只含 0 / 1 / ?
int zero[MAXN * 4]; // zero[p]：节点 p 区间内所有串「这一位固定为 0」的位置集合（位掩码）
int one[MAXN * 4];  // one[p]：节点 p 区间内所有串「这一位固定为 1」的位置集合（位掩码）

// 把字符串 t 编码成两个位掩码：第 i 个字符对应二进制第 i 位（从 0 开始）。
void encode(const char* t, int& z, int& o) {
    z = 0;
    o = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == '0')
            z |= (1 << i);
        else if (t[i] == '1')
            o |= (1 << i);
    }
}

// 合并两个儿子的约束：被固定的位置集合分别按位或（合并规则见题解）。
void pull(int p) {
    zero[p] = zero[p << 1] | zero[p << 1 | 1];
    one[p] = one[p << 1] | one[p << 1 | 1];
}

// 建树：叶子编码对应字符串，内部节点由两个儿子 OR 合并。
void build(int l, int r, int p) {
    if (l == r) {
        encode(s[l], zero[p], one[p]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    pull(p);
}

// 单点修改：把第 pos 个字符串改成 t，并沿路径把受影响的祖先重新合并。
void modify(int pos, const char* t, int l, int r, int p) {
    if (l == r) {
        encode(t, zero[p], one[p]);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(pos, t, l, mid, p << 1);
    else
        modify(pos, t, mid + 1, r, p << 1 | 1);
    pull(p);
}

// 区间查询：把 [ql, qr] 内所有约束 OR 合并进 z / o。
// z：区间内被固定为 0 的位置集合；o：区间内被固定为 1 的位置集合。
void query(int ql, int qr, int l, int r, int p, int& z, int& o) {
    if (ql <= l && r <= qr) {
        z |= zero[p];
        o |= one[p];
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) query(ql, qr, l, mid, p << 1, z, o);
    if (qr > mid) query(ql, qr, mid + 1, r, p << 1 | 1, z, o);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
        cin >> s[i];

    build(1, m, 1);

    int ans_xor = 0; // 所有查询答案的异或和
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int pos;
            char t[35];
            cin >> pos >> t;
            modify(pos, t, 1, m, 1);
        } else {
            int l, r;
            cin >> l >> r;
            int z = 0, o = 0;
            query(l, r, 1, m, 1, z, o);
            if ((z & o) == 0) {
                // 无冲突：没有被任何串固定的位置都可自由选 0/1，答案 = 2^自由位个数
                int free_cnt = n - __builtin_popcount(z | o);
                ans_xor ^= (1 << free_cnt);
            }
            // 若 z & o != 0，某一位同时被固定为 0 和 1，答案为 0，异或 0 不变
        }
    }
    cout << ans_xor << '\n';
    return 0;
}
