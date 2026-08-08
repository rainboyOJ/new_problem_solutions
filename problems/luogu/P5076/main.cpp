/**
 * P5076 【深基16.例7】普通二叉树（简化版）
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int INF = 2147483647;

// BST 结点：值、左/右孩子、出现次数、子树大小
struct Node {
    int val, l, r, cnt, sz;
} tree[MAXN];
int root, idx;

// 新建结点
int new_node(int val) {
    ++idx;
    tree[idx].val = val;
    tree[idx].l = tree[idx].r = 0;
    tree[idx].cnt = tree[idx].sz = 1;
    return idx;
}

// 插入，维护子树大小
void insert(int &u, int val) {
    if (u == 0) { u = new_node(val); return; }
    ++tree[u].sz;
    if (val == tree[u].val) { ++tree[u].cnt; return; }
    if (val < tree[u].val) insert(tree[u].l, val);
    else insert(tree[u].r, val);
}

// 查询 val 的排名（比 val 小的个数 + 1）
int get_rank(int u, int val) {
    if (u == 0) return 1;
    if (val == tree[u].val) return tree[tree[u].l].sz + 1;
    if (val < tree[u].val) return get_rank(tree[u].l, val);
    return tree[tree[u].l].sz + tree[u].cnt + get_rank(tree[u].r, val);
}

// 查询第 k 小的值
int kth(int u, int k) {
    if (u == 0) return 0;
    int lsz = tree[tree[u].l].sz;
    if (k <= lsz) return kth(tree[u].l, k);
    if (k <= lsz + tree[u].cnt) return tree[u].val;
    return kth(tree[u].r, k - lsz - tree[u].cnt);
}

// 前驱：小于 val 的最大值
int pre(int u, int val) {
    if (u == 0) return -INF;
    if (tree[u].val >= val) return pre(tree[u].l, val);
    return max(tree[u].val, pre(tree[u].r, val));
}

// 后继：大于 val 的最小值
int nxt(int u, int val) {
    if (u == 0) return INF;
    if (tree[u].val <= val) return nxt(tree[u].r, val);
    return min(tree[u].val, nxt(tree[u].l, val));
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) printf("%d\n", get_rank(root, x));
        else if (op == 2) printf("%d\n", kth(root, x));
        else if (op == 3) printf("%d\n", pre(root, x));
        else if (op == 4) printf("%d\n", nxt(root, x));
        else insert(root, x);
    }
    return 0;
}
