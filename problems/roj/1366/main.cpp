/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:08
 * update_at: 2026-10-05 12:08
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 100005; // 结点数上限（题面未给，取足够大）

char buf[MAXN];   // 读入缓冲
int pre[MAXN];    // 先序序列，存字符编码
int ino[MAXN];    // 中序序列，存字符编码
int pos[256];     // pos[字符编码] = 该字符在中序序列中的下标，用于 O(1) 定位切分点
int n;            // 结点个数

// 返回先序 [pl, pl+cnt) 与中序 [il, il+cnt) 这棵子树的叶子数。
// 题面中结点的「长度」就等于子树的叶子数：叶为 1，非叶为左右之和。
// 空子树（cnt == 0）返回 0，于是只有一个孩子时缺失的那侧自然贡献 0。
int leaf_count(int pl, int il, int cnt) {
    if (cnt <= 1) {
        return cnt;
    }
    int left_cnt = pos[pre[pl]] - il; // 先序首字符是根，它在中序中的位置给出左子树大小
    return leaf_count(pl + 1, il, left_cnt)
         + leaf_count(pl + 1 + left_cnt, il + left_cnt + 1, cnt - 1 - left_cnt);
}

// 按先序输出这棵子树：先输出根那一行（字符重复「叶子数」次），再递归左右子树。
void walk(int pl, int il, int cnt) {
    if (cnt == 0) {
        return;
    }
    int line_cnt = leaf_count(pl, il, cnt); // 该结点字符要重复的次数
    for (int i = 0; i < line_cnt; i++) {
        putchar(pre[pl]);
    }
    putchar('\n');
    int left_cnt = pos[pre[pl]] - il; // 左子树大小
    walk(pl + 1, il, left_cnt);
    walk(pl + 1 + left_cnt, il + left_cnt + 1, cnt - 1 - left_cnt);
}

int main() {
    scanf("%s", buf);
    n = 0;
    while (buf[n] != '\0') {
        pre[n] = buf[n];
        n++;
    }
    scanf("%s", buf);
    for (int i = 0; i < n; i++) {
        ino[i] = buf[i];
        pos[ino[i]] = i;
    }

    walk(0, 0, n);
    return 0;
}
