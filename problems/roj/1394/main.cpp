/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:44
 * update_at: 2026-10-05 12:44
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1005; // 行列上限 1000，开 1005 防越界
const int MAXV = MAXN * MAXN;

int m, n;           // m 行 n 列的点阵
ll cost;            // 还需要的最小花费
int fa[MAXV];       // fa[i]：点 i（编号 (行-1)*n + 列-1）所在并查集的父节点

// 查找点 x 的根，带路径压缩
int find_root(int x) {
    int root = x;
    while (fa[root] != root)
        root = fa[root];
    while (fa[x] != root) {
        int nxt = fa[x];
        fa[x] = root;
        x = nxt;
    }
    return root;
}

// 若 u、v 尚未连通则合并并返回 true，否则返回 false
bool try_union(int u, int v) {
    int ru = find_root(u);
    int rv = find_root(v);
    if (ru == rv)
        return false;
    fa[ru] = rv;
    return true;
}

int main() {
    scanf("%d %d", &m, &n);

    // 初始化并查集
    for (int i = 0; i < m * n; ++i)
        fa[i] = i;

    // 已有连线花费为 0，先全部合并
    int x1, y1, x2, y2;
    while (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
        int u = (x1 - 1) * n + (y1 - 1);
        int v = (x2 - 1) * n + (y2 - 1);
        try_union(u, v);
    }

    // 阶段一：先加花费 1 的纵向边 ((r,c),(r+1,c))，能合并就累加 1
    for (int r = 0; r < m - 1; ++r)
        for (int c = 0; c < n; ++c)
            if (try_union(r * n + c, (r + 1) * n + c))
                cost += 1;

    // 阶段二：再加花费 2 的横向边 ((r,c),(r,c+1))，能合并就累加 2
    for (int r = 0; r < m; ++r)
        for (int c = 0; c < n - 1; ++c)
            if (try_union(r * n + c, r * n + c + 1))
                cost += 2;

    printf("%lld\n", cost);
    return 0;
}
