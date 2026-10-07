/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:18
 * update_at: 2026-10-08 02:18
 */
// 死亡之树：统计图 G 中恰含 k 个叶子（度数为 1）的带标号生成树棵数
// n <= 10, m <= 45，状压 DP：f[点集][叶子集]
//
// 不重不漏的关键：一棵树若有 >= 3 个点，就有 >= 2 个叶子。规定每次只剥离
// 「当前树中编号最小的叶子」 j（即 j = leaf 的最低位），那么 j 的剥离位置唯一：
// j 在树中的唯一邻居 k 必须不是叶子（k ∈ mask \ leaf），剥掉 j 得到小一圈的树。
// 反向就得到递推：叶子集不再变（k 原非叶子）或把 k 补进叶子集（k 原为叶子）。
// 每棵树的剥离序列唯一，所以每个状态恰好被统计一次。
//
// 两点情形（一条边）里两个点都是叶子，不满足「k 不是叶子」，单独作为 base。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10;   // 点数上限
const int MAXM = 1 << MAXN;

int n, m, K;
int adj[MAXN][MAXN];   // 邻接矩阵，1 表示有边（题面保证无重边、无自环）
ll f[MAXM][MAXM];      // f[点集][叶子集]：点集内部、叶子集恰为该集合的树棵数

int main() {
    scanf("%d %d %d", &n, &m, &K);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;                        // 转 0-based
        adj[a][b] = adj[b][a] = 1;
    }

    int full = (1 << n) - 1;

    // 按点集大小顺序递推：mask 去掉一个点后必然更小，故 mask 从小到大即可
    for (int mask = 1; mask <= full; mask++) {
        if (__builtin_popcount(mask) == 2) {
            // base：恰两个点，有边则构成一棵树，两点都是叶子
            int x = __builtin_ctz(mask);
            int y = __builtin_ctz(mask ^ (1 << x));
            if (adj[x][y]) f[mask][mask] = 1;
            continue;
        }
        // 枚举叶子集 leaf，必须是 mask 的子集
        for (int leaf = mask; leaf; leaf = (leaf - 1) & mask) {
            int j = __builtin_ctz(leaf);        // 编号最小的叶子 = 最后被加入的点
            int jb = 1 << j;
            int rest = mask ^ jb;               // 剥掉 j 后的点集
            int oldLeaf = leaf ^ jb;            // 情形 (a)：k 在原树里度数 >= 2，叶子集不变
            // 枚举 j 在原树中的唯一邻居 k：k 必须在 mask 里且不是叶子
            for (int k = 0; k < n; k++) {
                int kb = 1 << k;
                if (!(mask & kb) || (leaf & kb)) continue;
                if (!adj[j][k]) continue;
                f[mask][leaf] += f[rest][oldLeaf]               // (a) k 原非叶子
                               + f[rest][oldLeaf | kb];         // (b) k 原为叶子，补进叶子集
            }
        }
    }

    ll ans = 0;
    for (int leaf = 1; leaf <= full; leaf++)
        if (__builtin_popcount(leaf) == K) ans += f[full][leaf];
    printf("%lld\n", ans);
    return 0;
}
