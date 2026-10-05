/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:16
 * update_at: 2026-10-05 11:16
 */

#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 205;              // 坐标最大为 200，再多留一圈处理越界边

int n, m;
int W;                           // 点阵实际宽度，含虚拟外圈
int parentArr[MAXN * MAXN];      // parentArr[id] 为并查集中 id 的父节点

// 返回 x 所在连通块的根，并把路径上的点直接挂到根上（路径压缩）
int find_root(int x) {
    int root = x;
    while (parentArr[root] != root) root = parentArr[root];
    while (x != root) {
        int fa = parentArr[x];
        parentArr[x] = root;
        x = fa;
    }
    return root;
}

int main() {
    scanf("%d %d", &n, &m);
    W = n + 1;                     // 真实数据里有 x=n 向下 / y=n 向右的越界边，多开一圈
    int total = W * W;
    for (int i = 0; i < total; ++i) parentArr[i] = i;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        char dir[2];
        scanf("%d %d %1s", &x, &y, dir); // 读入一个非空白字符
        int u = (x - 1) * W + (y - 1);
        int v;
        if (dir[0] == 'D') v = u + W;     // 向下连到下一行同列
        else v = u + 1;                   // 'R'，向右连到同一行下一列

        int ru = find_root(u);
        int rv = find_root(v);
        if (ru == rv) {                // 两端已在同一块，加这条边必成环
            printf("%d\n", i);
            return 0;
        }
        parentArr[rv] = ru;            // 否则合并两个连通块
    }

    printf("draw\n");
    return 0;
}
