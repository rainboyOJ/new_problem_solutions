/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-12 15:09
 */
// main.cpp：中序 + 层序还原二叉树（动态化静态建结点），再先序遍历输出。
//
// 层序遍历里祖先一定排在子孙前面，所以中序区间内层序名次最小的字符就是子树根：
// 建树时把值、左儿子、右儿子聚合成 struct Node，node[u] 就是编号 u 的结点，
// 根在中序里的位置把区间切成左右两段，递归接上左右儿子，最后先序走一遍。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int maxn = 1005; // 题面未给串长上限；字母互不重复，按原实现开 1005 留足余量

struct Node {
    char val; // 结点的字符
    int lch;  // 左儿子编号，0 表示空
    int rch;  // 右儿子编号，0 表示空
};

Node node[maxn];    // node[u]：编号 u 的结点（编号按建树顺序分配）
int node_cnt;       // 已分配的结点个数
char inorder[maxn]; // 中序遍历序列，下标从 1 开始
char level[maxn];   // 层序遍历序列，下标从 1 开始
int rank_pos[256];  // rank_pos[c] = 字符 c 在层序中的名次，名次越小越靠近根
int n;              // 结点个数

// 动态化静态开点：静态数组 + 分配指针 node_cnt，返回新结点的编号
int new_node(char val) {
    node_cnt++;
    node[node_cnt].val = val;
    node[node_cnt].lch = 0;
    node[node_cnt].rch = 0;
    return node_cnt;
}

// 用中序区间 [l, r] 建树，返回根编号；空区间返回 0
int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    // 根 = 区间内层序名次最小的字符：子孙一定排在祖先后面，名次不可能更小
    int best = l;
    for (int i = l + 1; i <= r; i++) {
        if (rank_pos[inorder[i]] < rank_pos[inorder[best]]) {
            best = i;
        }
    }
    int u = new_node(inorder[best]);
    node[u].lch = build(l, best - 1); // 根左边一段是左子树
    node[u].rch = build(best + 1, r); // 根右边一段是右子树
    return u;
}

// 先序遍历：根 -> 左子树 -> 右子树，把结点字符依次输出
void preorder(int u) {
    if (u == 0) {
        return;
    }
    putchar(node[u].val);
    preorder(node[u].lch);
    preorder(node[u].rch);
}

int main() {
    scanf("%s %s", inorder + 1, level + 1);
    n = strlen(inorder + 1);
    for (int i = 1; i <= n; i++) {
        rank_pos[level[i]] = i; // 名次从 1 数，保证"最小名次"就是最先出现的祖先
    }
    preorder(build(1, n));
    putchar('\n');
    return 0;
}
