/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-05 12:07
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 1005;          // 字符串长度上限

char inorder[MAXN];             // 中序遍历序列
char level[MAXN];               // 层序遍历序列
int rank_pos[MAXN];             // 字符在层序中的排名（字符用下标 0~25 或 ASCII 映射）
char out[MAXN];                 // 先序遍历输出序列
int out_len;                    // 已输出长度
int n;                          // 序列长度

// 递归输出中序区间 [l, r)（左闭右开）对应的子树的先序序列
void preorder(int l, int r) {
    if (l >= r) return;         // 空区间
    // 根 = 该区间内层序排名最小的字符（层序保证祖先排在子孙前面）
    int best = l;
    for (int i = l + 1; i < r; i++) {
        if (rank_pos[(int)inorder[i]] < rank_pos[(int)inorder[best]]) {
            best = i;
        }
    }
    char root = inorder[best];
    out[out_len++] = root;      // 先序先输出根
    // 在中序里定位根的位置，把区间切成左、右子树两段
    int mid = l;
    while (mid < r && inorder[mid] != root) mid++;
    preorder(l, mid);           // 左子树 [l, mid)
    preorder(mid + 1, r);       // 右子树 [mid+1, r)
}

int main() {
    scanf("%s %s", inorder + 1, level + 1);
    n = strlen(inorder + 1);
    // 按层序建立排名表
    for (int i = 1; i <= n; i++) {
        rank_pos[(int)level[i]] = i;
    }
    // 因为输入字符串从位置 1 开始，中序区间 [1, n+1)
    preorder(1, n + 1);
    out[out_len] = '\0';
    printf("%s\n", out);
    return 0;
}
