/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:15
 * update_at: 2026-10-05 11:15
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 20005;

int parent[MAXN]; // parent[x] 表示 x 的父节点，根节点指向自己（代表元）
int sz[MAXN];     // sz[x] 表示 x 所在树的大小（只在根节点上有意义）

// 并查集查找：沿父指针找到代表元，路径减半压缩
int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]]; // 把 x 的父指针提到祖父，路径减半
        x = parent[x];
    }
    return x;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    // 初始化：每个人自成一个集合
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    // 读入 M 条亲戚关系，逐条合并
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            // 按大小合并：小树挂到大树下
            if (sz[ra] < sz[rb]) {
                int t = ra; ra = rb; rb = t;
            }
            parent[rb] = ra;
            sz[ra] += sz[rb];
        }
    }
    int q;
    scanf("%d", &q);
    // 每次询问只需比较两人的代表元
    for (int i = 1; i <= q; i++) {
        int c, d;
        scanf("%d %d", &c, &d);
        if (find(c) == find(d))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
