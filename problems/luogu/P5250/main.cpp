/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-10-07 09:37
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 2147483647;

// BST 结点
struct Node {
    int val, l, r, cnt, sz;
} tree[MAXN];
int root, idx;

int new_node(int val) {
    ++idx;
    tree[idx].val = val;
    tree[idx].l = tree[idx].r = 0;
    tree[idx].cnt = tree[idx].sz = 1;
    return idx;
}

void insert(int &u, int val) {
    if (u == 0) { u = new_node(val); return; }
    ++tree[u].sz;
    if (val == tree[u].val) { ++tree[u].cnt; return; }
    if (val < tree[u].val) insert(tree[u].l, val);
    else insert(tree[u].r, val);
}

// 删除一个值（只删一个）
void erase(int &u, int val) {
    if (u == 0) return;
    if (val == tree[u].val) {
        if (tree[u].cnt > 1) { --tree[u].cnt; --tree[u].sz; return; }
        if (!tree[u].l || !tree[u].r) { u = tree[u].l + tree[u].r; return; }
        // 左右子树都存在：找前驱替换
        int v = tree[u].l;
        while (tree[v].r) v = tree[v].r;
        tree[u].val = tree[v].val;
        tree[u].cnt = tree[v].cnt;
        tree[v].cnt = 1;
        erase(tree[u].l, tree[v].val);
        tree[u].sz = tree[tree[u].l].sz + tree[tree[u].r].sz + tree[u].cnt;
        return;
    }
    if (val < tree[u].val) erase(tree[u].l, val);
    else erase(tree[u].r, val);
    tree[u].sz = tree[tree[u].l].sz + tree[tree[u].r].sz + tree[u].cnt;
}

// 查询 val 的排名
int get_rank(int u, int val) {
    if (u == 0) return 1;
    if (val == tree[u].val) return tree[tree[u].l].sz + 1;
    if (val < tree[u].val) return get_rank(tree[u].l, val);
    return tree[tree[u].l].sz + tree[u].cnt + get_rank(tree[u].r, val);
}

// 查询第 k 小
int kth(int u, int k) {
    if (u == 0) return 0;
    int lsz = tree[tree[u].l].sz;
    if (k <= lsz) return kth(tree[u].l, k);
    if (k <= lsz + tree[u].cnt) return tree[u].val;
    return kth(tree[u].r, k - lsz - tree[u].cnt);
}

// 前驱
int pre(int u, int val) {
    if (u == 0) return -INF;
    if (tree[u].val >= val) return pre(tree[u].l, val);
    return max(tree[u].val, pre(tree[u].r, val));
}

// 后继
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
        // get_rank 的语义：x 存在时返回 x 的排名；x 不存在时返回第一个比 x 大的元素（后继）的排名。
        int rk = get_rank(root, x);
        bool exists = (rk <= tree[root].sz) && (kth(root, rk) == x);

        if (op == 1) {
            // 仓库里已经有这个长度就不再放
            if (exists) {
                puts("Already Exist");
            } else {
                insert(root, x);
            }
        } else {
            if (root == 0) {
                puts("Empty");
                continue;
            }

            int target;
            if (exists) {
                // 仓库里刚好有这个长度，直接取它
                target = x;
            } else {
                int prev_rank = rk - 1;  // 比 x 小的最大元素的排名；0 表示不存在
                int next_rank = rk;      // x 不存在时，get_rank 给出的就是后继的排名

                if (prev_rank < 1) {
                    target = kth(root, next_rank);
                } else if (next_rank > tree[root].sz) {
                    target = kth(root, prev_rank);
                } else {
                    int shorter = kth(root, prev_rank);
                    int longer = kth(root, next_rank);
                    // 两根木材距离相同时取较短的那根
                    target = (x - shorter <= longer - x) ? shorter : longer;
                }
            }
            printf("%d\n", target);
            erase(root, target);
        }
    }
    return 0;
}
