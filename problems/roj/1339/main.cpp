/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-12 14:55
 */
// main.cpp：由先序 + 中序还原二叉树，按"左 + 右 + 根"递归输出后序。
//
// 不显式建结点，直接在两个字符串上下标递归：先序串首字符就是根，
// 在中序串里找到根的位置，根左边 k 个字符属于左子树，两串按 k 同步切分，
// 递归到底后按"左子树后序 + 右子树后序 + 根"拼出后序。
// 结点字母互不相同，所以根在中序中的位置唯一。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int maxn = 35; // 题面结点用小写字母、结点数 ≤ 30，按上界开

char pre[maxn]; // 先序遍历串，从 pre[1] 开始存放
char ino[maxn]; // 中序遍历串，从 ino[1] 开始存放
int n;          // 树的结点数，也就是串长

// 在中序段 [inL, inR] 中查找根字符 ch 的下标
int find_pos(int inL, int inR, char ch) {
    for (int i = inL; i <= inR; i++) {
        if (ino[i] == ch) {
            return i;
        }
    }
    return -1; // 题面保证是合法的两串遍历，走到这里说明输入不合法
}

// 由先序段 [pL, pR] 与中序段 [inL, inR] 还原子树，把后序按"左 + 右 + 根"写到 out[pos..]
// pos 传引用一路追加，省掉字符串反复拼接
void build(int pL, int pR, int inL, int inR, char out[], int &pos) {
    if (pL > pR) {
        return; // 空子树
    }
    char root = pre[pL];                    // 先序首字符定根
    int k = find_pos(inL, inR, root) - inL; // 根在中序中的偏移 = 左子树的结点数

    // 左子树：先序 [pL+1, pL+k]，中序 [inL, inL+k-1]
    build(pL + 1, pL + k, inL, inL + k - 1, out, pos);
    // 右子树：先序 [pL+k+1, pR]，中序 [inL+k+1, inR]
    build(pL + k + 1, pR, inL + k + 1, inR, out, pos);
    out[pos++] = root; // 根最后写，这正是后序
}

// 读入先序、中序两行，输出后序一行
void solve() {
    scanf("%s", pre + 1); // 串从下标 1 开始存，下标 0 空着，段边界才好用闭区间
    scanf("%s", ino + 1);
    n = strlen(pre + 1); // 两串等长，结点数就是串长

    char post[maxn];
    int pos = 1;
    build(1, n, 1, n, post, pos);
    post[pos] = '\0';

    printf("%s\n", post + 1);
}

int main() {
    solve();
    return 0;
}
