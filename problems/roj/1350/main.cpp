/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:23
 * update_at: 2026-10-05 11:23
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 105;
const ll INF = 0x3F3F3F3F3F3F3F3F;

int n;             // 农场个数
ll g[MAXN][MAXN];  // g[i][j] 表示农场 i 与 j 之间的距离（邻接矩阵）
ll dis[MAXN];      // dis[j] 表示树外点 j 到当前生成树的最短边权；入树后为 INF
bool in_tree[MAXN];// in_tree[j] 表示点 j 是否已进入生成树

int main() {
    scanf("%d", &n);
    // 矩阵按 80 字符折行，逻辑行与物理行不一致，用 token 流读入
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%lld", &g[i][j]);

    // Prim：以 0 号农场为起点，初始只有它在树里
    for (int j = 0; j < n; ++j) dis[j] = g[0][j];
    dis[0] = INF;      // 已入树的点恒为 INF，否则第一轮会重复选中起点
    in_tree[0] = true;

    ll ans = 0;        // 最小生成树的边权总和
    for (int round = 1; round < n; ++round) {
        // 选距离树最近的树外点 k 拉进树（cut 性质保证贪心正确）
        int k = -1;
        for (int j = 0; j < n; ++j)
            if (!in_tree[j] && (k == -1 || dis[j] < dis[k]))
                k = j;
        ans += dis[k];
        in_tree[k] = true;
        dis[k] = INF;

        // 用 k 所在行松弛其余树外点的距离；对角线 g[k][k]=0 不会影响已入树点
        for (int j = 0; j < n; ++j)
            if (!in_tree[j] && g[k][j] < dis[j])
                dis[j] = g[k][j];
    }

    printf("%lld\n", ans);
    return 0;
}
