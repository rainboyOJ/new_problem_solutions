/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:14
 * update_at: 2026-10-05 12:14
 */

// 中序查找二叉树：孩子链表存树，先找根，再中序遍历数到值为 x 的结点。

#include <cstdio>
#include <cstdlib>

const int MAXN = 105;

typedef long long ll;

int n;                 // 结点个数
ll x;                  // 要查找的结点值
ll val[MAXN];          // val[i]：编号 i 的结点的值
int lc[MAXN], rc[MAXN]; // lc[i], rc[i]：左、右儿子编号，0 表示空
bool is_son[MAXN];     // is_son[i]：编号 i 是否当过别人的儿子
int cnt;               // 中序访问计数器

// 中序遍历：左 -> 根 -> 右，访问到值为 x 的结点就输出名次
void inorder(int u) {
    if (u == 0)
        return;
    inorder(lc[u]);
    cnt++; // 第 cnt 个被访问的结点
    if (val[u] == x) {
        printf("%d\n", cnt);
        exit(0); // 命中即停
    }
    inorder(rc[u]);
}

int main() {
    scanf("%d %lld", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %d %d", &val[i], &lc[i], &rc[i]);
        if (lc[i])
            is_son[lc[i]] = true;
        if (rc[i])
            is_son[rc[i]] = true;
    }

    // 根是唯一没当过儿子的结点
    int root = 1;
    for (int i = 1; i <= n; i++)
        if (!is_son[i])
            root = i;

    inorder(root);
    return 0;
}
