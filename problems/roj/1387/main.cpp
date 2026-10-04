/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */

// 搭配购买：并查集缩连通块 + 0/1 背包
// 买一朵云必须买搭配的云，且关系可传递，所以每个连通块要么整块买、要么不买。
// 把每个连通块看成一件 (总价钱, 总价值) 的物品，跑 0/1 背包即可。

#include <cstdio>

typedef long long ll;

const int MAXN = 10005;  // n <= 10000
const int MAXW = 10005;  // w <= 10000

int n, m, w;
ll cost[MAXN];            // cost[i]：第 i 朵云的价钱
ll val[MAXN];             // val[i]：第 i 朵云的价值
int fa[MAXN];             // 并查集父节点

ll gc[MAXN];              // gc[根]：该连通块的总价钱
ll gv[MAXN];              // gv[根]：该连通块的总价值
ll dp[MAXW];              // dp[j]：花费不超过 j 能获得的最大价值

// 并查集查找（路径减半）
int find(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

int main() {
    scanf("%d %d %d", &n, &m, &w);
    for (int i = 1; i <= n; i++)
        scanf("%lld %lld", &cost[i], &val[i]);

    // 初始化并查集
    for (int i = 1; i <= n; i++) fa[i] = i;

    // 搭配关系逐条合并
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int ru = find(u), rv = find(v);
        if (ru != rv) fa[ru] = rv;
    }

    // 每个连通块捆绑成一件物品：价钱、价值分别求和（下标用根编号）
    for (int i = 1; i <= n; i++) {
        int root = find(i);
        gc[root] += cost[i];
        gv[root] += val[i];
    }

    // 0/1 背包：每件物品（连通块）最多选一次，倒序枚举容量
    for (int i = 1; i <= n; i++) {
        int root = find(i);
        if (root != i) continue;   // 每个连通块只处理它的根一次
        ll c = gc[root];
        if (c > w) continue;       // 整块买不起，跳过
        ll d = gv[root];
        for (ll j = w; j >= c; j--) {
            if (dp[j - c] + d > dp[j])
                dp[j] = dp[j - c] + d;
        }
    }

    printf("%lld\n", dp[w]);
    return 0;
}
