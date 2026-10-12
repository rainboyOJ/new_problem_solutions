/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:08
 * update_at: 2026-10-12 15:09
 */
// main.cpp：先序 + 中序还原二叉树，按凹入表示法输出（结点长度 = 子树叶子数）。
//
// 先序首字符是根，它在中序里的位置把左右子树切开，递归建树；
// 结点的值、左儿子、右儿子、长度聚合成 struct Node，node[u] 就是编号 u 的结点：
// 叶子长度为 1，非叶长度等于左右子树长度之和（空子树记 0），
// 建树时顺手算好 node[u].len，最后按先序输出「字符 × 长度」。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int maxn = 100005; // 题面未给串长上限（字母互不重复），按原实现开足够大

struct Node {
    char val; // 结点的字符
    int lch;  // 左儿子编号，0 表示空
    int rch;  // 右儿子编号，0 表示空
    int len;  // 结点长度 = 子树叶子数：叶为 1，非叶为左右之和，空子树为 0
};

Node node[maxn]; // node[u]：编号 u 的结点（编号按建树顺序分配）
int node_cnt;    // 已分配的结点个数
char pre[maxn];  // 先序遍历序列
char ino[maxn];  // 中序遍历序列，只用来建 pos 表
int pos[256];    // pos[c] = 字符 c 在中序中的下标，用于 O(1) 定位切分点
int n;           // 结点个数

// 动态化静态开点：静态数组 + 分配指针 node_cnt，返回新结点的编号
int new_node(char val) {
    node_cnt++;
    node[node_cnt].val = val;
    node[node_cnt].lch = 0;
    node[node_cnt].rch = 0;
    node[node_cnt].len = 0;
    return node_cnt;
}

// 用先序 [pl, pl+cnt) 与中序 [il, il+cnt) 建树，返回根编号；空子树返回 0
int build(int pl, int il, int cnt) {
    if (cnt == 0) {
        return 0;
    }
    int u = new_node(pre[pl]);        // 先序首字符就是根
    int left_cnt = pos[pre[pl]] - il; // 根在中序中的位置给出左子树大小
    node[u].lch = build(pl + 1, il, left_cnt);
    node[u].rch = build(pl + 1 + left_cnt, il + left_cnt + 1, cnt - 1 - left_cnt);
    // 长度 = 子树叶子数：叶为 1，非叶为左右之和
    if (node[u].lch == 0 && node[u].rch == 0) {
        node[u].len = 1;
    } else {
        node[u].len = node[node[u].lch].len + node[node[u].rch].len;
    }
    return u;
}

// 按先序输出凹入表示：先根那一行（字符重复 len 次），再递归左右子树
void walk(int u) {
    if (u == 0) {
        return;
    }
    for (int i = 0; i < node[u].len; i++) {
        putchar(node[u].val);
    }
    putchar('\n');
    walk(node[u].lch);
    walk(node[u].rch);
}

int main() {
    scanf("%s %s", pre, ino);
    n = strlen(pre);
    for (int i = 0; i < n; i++) {
        pos[ino[i]] = i; // 字符互不重复，中序下标就是唯一的切分点
    }
    walk(build(0, 0, n));
    return 0;
}
