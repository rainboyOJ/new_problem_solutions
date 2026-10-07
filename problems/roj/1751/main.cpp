/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:10
 * update_at: 2026-10-07 21:10
 *
 * 一本通 1751《字符串排序》（同源原题：Codeforces 558E A Simple Task）
 *
 * 题意：长度为 n 的小写字母串，m 次操作，每次把区间 [l, r] 升序或降序排序，求最终串。
 * 注意：题面散文写"每行三个整数 x,l,r"，但输入样例 `1 3 1` / `3 5 0` 只有按 (l, r, x)
 *       解释才能得到样例输出 abdcc，故本题实际输入顺序为 l r x（数据生成脚本同此）。
 *
 * 算法：每个字母 c（0..25）维护一棵线段树，位置 i 上是 1 当且仅当 S_i == c。
 *   一次排序 (l, r, x)：
 *     1) 对 c = 0..25 求 cnt[c] = 「c 在 [l, r] 中的个数」；
 *     2) 把 [l, r] 中所有出现过的字母（cnt[c] > 0）各自整段清零 —— 26 棵树彼此独立，
 *        赋值不会顺带清掉别的字母，必须先清；
 *     3) 按 x 决定字母顺序（升序 a→z，降序 z→a），把 cnt[c] 个 c 整段赋值回
 *        [pos, pos + cnt[c] - 1]，pos 依次右移。
 *   cnt[] 是对 [l, r] 的一个划分，所以覆盖完成后区间内每个位置恰好属于一个字母。
 *
 * 复杂度：单次操作 26 次区间求和 + 最多 26 次区间清零 + 最多 26 次区间覆盖，
 *         即 O(26 log n)；总 O((n + 78 m) log n)，空间 O(26 n)。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n, m;             // n 为串长，m 为操作次数
char s[MAXN + 1];    // 题面给定的字符串，下标从 1 开始
char res[MAXN + 1];  // 最终答案串，下标从 1 开始

// 线段树节点：区间和 + 区间覆盖标记，聚合成 struct（避免平行数组）
struct SegNode {
    int sum;           // 该节点区间内「本树的字母」出现次数，不超过 n，用 int 省内存
    signed char lazy;  // -1 表示无覆盖标记；0 / 1 表示整段被覆盖成 0 / 1
};

// 字母 c 的线段树就是 tree[c]；26 * 4n 个节点，值域只有 0/1
SegNode tree[26][4 * MAXN];

// 建树：叶子 i 为 1 当且仅当 s[i] == 'a' + c
void build(ll c, ll node, ll l, ll r) {
    tree[c][node].lazy = -1;
    if (l == r) {
        tree[c][node].sum = (s[l] - 'a' == c) ? 1 : 0;
        return;
    }
    ll mid = (l + r) >> 1;
    build(c, node << 1, l, mid);
    build(c, node << 1 | 1, mid + 1, r);
    tree[c][node].sum = tree[c][node << 1].sum + tree[c][node << 1 | 1].sum;
}

// 把节点 node 的整段 [l, r] 覆盖成 v（v = 0 或 1）
void apply(ll c, ll node, ll l, ll r, ll v) {
    tree[c][node].sum = v ? int(r - l + 1) : 0;
    tree[c][node].lazy = (signed char)v;
}

// 下传覆盖标记（叶子不需要下传）
void push_down(ll c, ll node, ll l, ll r) {
    if (tree[c][node].lazy == -1 || l == r) return;
    ll mid = (l + r) >> 1;
    ll v = tree[c][node].lazy;
    apply(c, node << 1, l, mid, v);
    apply(c, node << 1 | 1, mid + 1, r, v);
    tree[c][node].lazy = -1;
}

// 查询字母 c 在 [ql, qr] 中的出现次数
ll query(ll c, ll node, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) return tree[c][node].sum;
    push_down(c, node, l, r);
    ll mid = (l + r) >> 1;
    ll tot = 0;
    if (ql <= mid) tot += query(c, node << 1, l, mid, ql, qr);
    if (qr > mid) tot += query(c, node << 1 | 1, mid + 1, r, ql, qr);
    return tot;
}

// 把 [ql, qr] 整段覆盖成 v（v = 0 表示这一段都不是字母 c，v = 1 表示都是）
void assign_range(ll c, ll node, ll l, ll r, ll ql, ll qr, ll v) {
    if (ql > qr) return;  // 空区间（某字母出现次数为 0 时可能被调用）
    if (ql <= l && r <= qr) {
        apply(c, node, l, r, v);
        return;
    }
    push_down(c, node, l, r);
    ll mid = (l + r) >> 1;
    if (ql <= mid) assign_range(c, node << 1, l, mid, ql, qr, v);
    if (qr > mid) assign_range(c, node << 1 | 1, mid + 1, r, ql, qr, v);
    tree[c][node].sum = tree[c][node << 1].sum + tree[c][node << 1 | 1].sum;
}

// 收集字母 c 出现的位置写入答案（整段为 0 的子树直接剪掉，总量 O(26 n) 以内）
void collect(ll c, ll node, ll l, ll r) {
    if (tree[c][node].sum == 0) return;
    if (l == r) {
        res[l] = (char)('a' + c);
        return;
    }
    push_down(c, node, l, r);
    ll mid = (l + r) >> 1;
    collect(c, node << 1, l, mid);
    collect(c, node << 1 | 1, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> (s + 1);

    // 26 个字母各建一棵线段树
    for (ll c = 0; c < 26; c++) build(c, 1, 1, n);

    ll cnt[26];  // cnt[c] = 当前区间里字母 c 的个数
    for (ll q = 0; q < m; q++) {
        ll l, r, x;
        cin >> l >> r >> x;  // 输入顺序：左端点、右端点、方向（1 升序 / 0 降序）

        for (ll c = 0; c < 26; c++) cnt[c] = query(c, 1, 1, n, l, r);

        // 先清空区间内出现过的字母，否则旧字母会残留在自己的树里
        for (ll c = 0; c < 26; c++)
            if (cnt[c] > 0) assign_range(c, 1, 1, n, l, r, 0);

        // 再按升序 / 降序把各字母的计数整段铺回去
        ll pos = l;
        if (x == 1) {
            for (ll c = 0; c < 26 && pos <= r; c++) {
                if (cnt[c] > 0) {
                    assign_range(c, 1, 1, n, pos, pos + cnt[c] - 1, 1);
                    pos += cnt[c];
                }
            }
        } else {
            for (ll c = 25; c >= 0 && pos <= r; c--) {
                if (cnt[c] > 0) {
                    assign_range(c, 1, 1, n, pos, pos + cnt[c] - 1, 1);
                    pos += cnt[c];
                }
            }
        }
    }

    for (ll c = 0; c < 26; c++) collect(c, 1, 1, n);
    res[n + 1] = '\0';
    cout << (res + 1) << '\n';
    return 0;
}
