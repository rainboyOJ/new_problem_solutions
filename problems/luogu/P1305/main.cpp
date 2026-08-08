/**
 * P1305 新二叉树
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 结点结构：左右孩子，'*' 表示空
struct Node {
    int l, r;
} tree[128];
bool has_parent[128];
int n;

// 前序遍历
void preorder(int u) {
    if (u == '*') return;
    putchar(u);
    preorder(tree[u].l);
    preorder(tree[u].r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        char s[4];
        scanf("%s", s);
        int u = s[0], l = s[1], r = s[2];
        tree[u].l = l;
        tree[u].r = r;
        if (l != '*') has_parent[l] = true;
        if (r != '*') has_parent[r] = true;
    }
    // 找根：没有父结点的就是根
    int root = ' ';
    for (int c = 'a'; c <= 'z'; ++c) {
        if (tree[c].l || tree[c].r) {
            if (!has_parent[c]) { root = c; break; }
        }
    }
    preorder(root);
    putchar('\n');
    return 0;
}
