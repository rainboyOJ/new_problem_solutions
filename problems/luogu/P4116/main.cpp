/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:05
 * update_at: 2026-10-23 21:40
 */
// main.cpp：双 dfs 序 + 线段树二分，O((n+q) log n)（本题目解主解，解法一）。
// 关键性质：u 是 v 的祖先 <=> dfn[u] <= dfn[v] 且 rdfn[u] <= rdfn[v]，
// 其中 dfn 是先序进入时间，rdfn 是把儿子列表翻转后再 DFS 的进入时间。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

int n, q;
vector<int> g[MAXN]; // 邻接表存树

int dfn[MAXN];      // dfn[u]：先序 DFS 的进入时间
int rdfn[MAXN];     // rdfn[u]：把每个节点的儿子列表翻转后再 DFS 的进入时间
int node_at[MAXN];  // node_at[i]：dfn 为 i 的节点
int timer;          // 先序编号计数器，从 1 递增到 n
int reverse_timer;  // 退出编号计数器，从 n 递减到 1

bool black[MAXN];   // black[u]：节点 u 当前是否为黑点
int tree[MAXN * 4]; // tree[p]：该区间内黑点 rdfn 的最小值，INF 表示区间内没有黑点

// 一遍 DFS 同时求两个序：进入时 dfn 正向编号，退出时 rdfn 倒着编号。
// rdfn 倒着编号的依据：翻转儿子列表的 DFS 的进入序，正是原 DFS 退出序的逆序。
void dfs(int u, int fa) {
    dfn[u] = ++timer;
    node_at[timer] = u;
    for (int v : g[u])
        if (v != fa) dfs(v, u);
    rdfn[u] = reverse_timer--;
}

// 点更新：把位置 pos 的叶子值改成 value，并向上合并区间最小值。
void seg_update(int p, int l, int r, int pos, int value) {
    if (l == r) {
        tree[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        seg_update(p << 1, l, mid, pos, value);
    else
        seg_update(p << 1 | 1, mid + 1, r, pos, value);
    tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

// 在线段树上找最小的下标 i 使叶子值 <= limit（线段树二分），不存在返回 0。
int find_first(int p, int l, int r, int limit) {
    if (tree[p] > limit) return 0; // 整个区间的最小值都超限，区间内没有答案
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (tree[p << 1] <= limit) return find_first(p << 1, l, mid, limit); // 左半边有答案就进左半边
    return find_first(p << 1 | 1, mid + 1, r, limit);
}

// 查询根 1 到 v 的路径上最浅的黑点编号，没有则返回 -1。
int query_first_black(int v) {
    int pos = find_first(1, 1, n, rdfn[v]); // 最小的 dfn，其节点 rdfn 不超过 rdfn[v]
    if (pos == 0 || pos > dfn[v]) return -1; // 不在 dfn[v] 左侧，说明路径上没有黑点
    return node_at[pos];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    timer = 0;
    reverse_timer = n;
    dfs(1, 0);

    fill(tree, tree + 4 * n + 4, INF); // 初始全白，所有叶子的值都是 INF

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0) {
            black[x] = !black[x];
            seg_update(1, 1, n, dfn[x], black[x] ? rdfn[x] : INF);
        } else {
            cout << query_first_black(x) << '\n';
        }
    }

    return 0;
}
