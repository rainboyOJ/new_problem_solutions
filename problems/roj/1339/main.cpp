/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-05 10:38
 */
// main.cpp：由先序 + 中序 还原二叉树并输出后序遍历。
// 思路：先序串首字符就是根；中序串中根左边的 k 个字符属于左子树，
//       同时也是左子树的结点个数。两串按 k 同步切分，递归到底，
//       按"左子树后序 + 右子树后序 + 根"拼接即得后序。

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 105;

char pre[MAXN];   // 前序遍历串
char ino[MAXN];   // 中序遍历串
int n;            // 树的结点数（串长）

// 在中序段 [inL, inR] 中查找字符 ch 的下标；结点字母互不相同，找到即可。
int find_pos(int inL, int inR, char ch) {
    for (int i = inL; i <= inR; i++) {
        if (ino[i] == ch) {
            return i;
        }
    }
    return -1;
}

// 由先序 [pL, pR] 与中序 [inL, inR] 还原后序，按"左 + 右 + 根"拼到 out[pos..]
void build(int pL, int pR, int inL, int inR, char out[], int &pos) {
    if (pL > pR) {
        return; // 空子树
    }
    char root = pre[pL];                       // 先序首字符定根
    int k = find_pos(inL, inR, root) - inL;    // 根在中序中的偏移 = 左子树结点数

    // 左子树：先序 [pL+1, pL+k]，中序 [inL, inL+k-1]
    build(pL + 1, pL + k, inL, inL + k - 1, out, pos);
    // 右子树：先序 [pL+k+1, pR]，中序 [inL+k+1, inR]
    build(pL + k + 1, pR, inL + k + 1, inR, out, pos);
    // 根放最后
    out[pos++] = root;
}

void solve() {
    // 两行字符串：先序、中序。用 scanf 读入一整行。
    scanf("%s", pre + 1);
    scanf("%s", ino + 1);
    n = (int)strlen(pre + 1);

    char post[MAXN];
    int pos = 1;
    build(1, n, 1, n, post, pos);
    post[pos] = '\0';

    printf("%s\n", post + 1);
}

int main() {
    solve();
    return 0;
}