/**
 * P4913 【深基16.例3】二叉树深度
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

// 结点结构：左孩子、右孩子编号（0 表示无）
struct Node {
    int l, r;
} tree[MAXN];
int n;

// DFS 求深度
int dfs(int u) {
    if (u == 0) return 0;
    return max(dfs(tree[u].l), dfs(tree[u].r)) + 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &tree[i].l, &tree[i].r);
    }
    printf("%d\n", dfs(1));
    return 0;
}
