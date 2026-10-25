/**
 * P1030 [NOIP 2001 普及组] 求先序排列
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-19 20:10
 * update_at: 2026-10-20 10:10
 */

#include <bits/stdc++.h>
using namespace std;

// 结点结构：左右孩子，0 表示空
struct Node {
    int l, r;
} tree[256];
int pos[256];       // 每个字母在中序遍历中的位置，用来 O(1) 切出左右子树
string in, post;    // 中序遍历、后序遍历

// 后序的最后一个字符是根；在中序里找到根，左边是左子树，右边是右子树。
// 用 [post_l, post_r] 和 [in_l, in_r] 两段区间递归建树，返回这棵子树的根。
int build(int post_l, int post_r, int in_l, int in_r) {
    if (post_l > post_r) return 0;

    int root = post[post_r];
    int mid = pos[root];
    int left_size = mid - in_l;

    tree[root].l = build(post_l, post_l + left_size - 1, in_l, mid - 1);
    tree[root].r = build(post_l + left_size, post_r - 1, mid + 1, in_r);
    return root;
}

// 前序遍历：根、左、右
void preorder(int u) {
    if (u == 0) return;
    cout << (char)u;
    preorder(tree[u].l);
    preorder(tree[u].r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> in >> post;
    for (int i = 0; i < (int)in.size(); ++i) {
        pos[(unsigned char)in[i]] = i;
    }

    int root = build(0, (int)post.size() - 1, 0, (int)in.size() - 1);
    preorder(root);
    cout << '\n';
    return 0;
}
