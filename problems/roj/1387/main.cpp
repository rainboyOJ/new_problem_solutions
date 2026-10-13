/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-13 22:33
 */

// 搭配购买：并查集缩连通块 + 0/1 背包
// 买一朵云必须买搭配的云，且关系可传递，所以每个连通块要么整块买、要么不买。
// 把每个连通块看成一件 (总价钱, 总价值) 的物品，跑 0/1 背包即可。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 10005;  // n <= 10000
const int maxw = 10005;  // w <= 10000

// 并查集竞赛精简版（不用 struct）：路径压缩 + 按大小合并
// 口诀：find 找根压到底，unite 小树挂大树
// 易错点：init 别只写 fa[i] = i，sz[i] 也要置 1；合并后 sz 只在新根上有效
// 和别的模板一起用时 maxn 只留一份

int fa[maxn], sz[maxn];  // sz[x] 仅在根上有效

void init(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
}

// 查 x 的根，顺手把整条链压到根上
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool same(int x, int y) { return find(x) == find(y); }

// 小树挂大树，返回是否真的发生了合并
bool unite(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    if (sz[fx] < sz[fy]) swap(fx, fy);
    fa[fy] = fx;
    sz[fx] += sz[fy];
    return true;
}

int n, m, w;
ll cost[maxn];            // cost[i]：第 i 朵云的价钱
ll val[maxn];             // val[i]：第 i 朵云的价值

ll gc[maxn];              // gc[根]：该连通块的总价钱
ll gv[maxn];              // gv[根]：该连通块的总价值
ll dp[maxw];              // dp[j]：花费不超过 j 能获得的最大价值

int main() {
    scanf("%d %d %d", &n, &m, &w);
    for (int i = 1; i <= n; i++)
        scanf("%lld %lld", &cost[i], &val[i]);

    // 初始化并查集
    init(n);

    // 搭配关系逐条合并
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    // 每个连通块捆绑成一件物品：价钱、价值分别求和（下标用根编号）
    for (int i = 1; i <= n; i++) {
        int root = find(i);
        gc[root] += cost[i];
        gv[root] += val[i];
    }

    // 0/1 背包：每件物品（连通块）最多选一次，倒序枚举容量
    for (int i = 1; i <= n; i++) {
        if (find(i) != i) continue;   // 每个连通块只处理它的根一次
        ll c = gc[i];
        if (c > w) continue;          // 整块买不起，跳过
        ll d = gv[i];
        for (int j = w; j >= c; j--) {
            if (dp[j - c] + d > dp[j])
                dp[j] = dp[j - c] + d;
        }
    }

    printf("%lld\n", dp[w]);
    return 0;
}
