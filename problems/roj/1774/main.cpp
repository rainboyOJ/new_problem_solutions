/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:45
 * update_at: 2026-10-08 01:53
 */
// main.cpp：一本通 1774《大逃杀》——树形背包（树上"带主路径"的连通块）。
//
// 题意：地图是一棵树，点 u 有资源 w[u]（>=0，到达即可拿走）和敌人耗时 t[u]（>=0，到达必须支付）。
//   可以从任意点空降，总时间 T，结束时武力值 = 走过的点的资源值之和（每种资源只拿一次）。
//   走过的点构成一棵连通子树 S，走路方式是一条从起点到终点的路线：路线上的边（主路径）走一次，
//   其余边为了去再回来必须走两次。所以总耗时 = Σ_{u∈S} t[u] + Σ_{e∈主路径} c[e] + 2·Σ_{e∈S\主路径} c[e]。
//   在耗时 <= T 的约束下最大化 Σ w。
//
// 算法：把"路线"拆成以最高点 u 为根的若干条腿（腿 = 从 u 往下走进去、不回来的一段）。
//   一条路线最多只有两个端点，故 u 处最多有 2 条开口的腿，其余分支都是"往返"。
//   dp0[u][j]：腿数 0，从 u 出发走遍子树内一部分再回到 u，恰好耗时 j 的最大资源值；
//   dp1[u][j]：腿数 1，从 u 出发，终点在子树内任意点，恰好耗时 j；
//   dp2[u][j]：腿数 2，起点终点都在子树内、路线经过 u，恰好耗时 j。
//   合并儿子 v（边权 c）时是 0/1 背包，v 只有三种接法：
//     往返：耗时多 2c，腿数 +0，收益 dp0[v][...]；
//     单程：耗时多 c，腿数 +1，收益 dp1[v][...]；
//     往返但两条腿都在 v 内部：耗时多 2c，腿数 +2，收益 dp2[v][...]。
//   因为走路总耗时非负、耗时越少越自由，所以"恰好 j"的语义不会漏解：最后对所有点、所有 j 取 max。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;             // n <= 300，多开一点
const ll NEG = -(1LL << 50);      // 负无穷：表示该 (点, 耗时) 状态不可达

int n, T;                         // 点数、总时间
ll weight[MAXN];                  // weight[u]：点 u 的资源值 w[u]
ll fight_time[MAXN];              // fight_time[u]：点 u 的杀敌耗时 t[u]

// dp0/dp1/dp2 的定义见文件头注释，第二维是"恰好耗时"，值为该耗时下的最大资源值
ll dp0[MAXN][MAXN];
ll dp1[MAXN][MAXN];
ll dp2[MAXN][MAXN];

ll buf0[MAXN], buf1[MAXN], buf2[MAXN]; // 合并一个儿子时的中转数组，避免读到本轮刚写进 dp[u] 的值

struct Edge {
    int to;      // 边指向的点
    int next;    // 链式前向星的下一条边
    ll cost;     // 通过这条边的时间 c
};
Edge edge[MAXN * 2];  // 双向边，共 2(n-1) 条
int head[MAXN], edge_cnt;

// 加一条有向边 u -> v，权值 cost
void add_edge(int u, int v, ll cost) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].cost = cost;
    edge[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

// 树上背包：处理以 u 为根的子树（以 1 号为根，parent 是父节点）
void dfs(int u, int parent) {
    // 注意：不能因为 u 自己打不过就剪掉整棵子树——u 的子孙仍然可以空降到达。
    // 所以只在 u 自己可达时填初始状态，子树照常递归。
    if (fight_time[u] <= T) {
        dp0[u][fight_time[u]] = weight[u]; // 只待在 u 一个点上：三种腿数都成立
        dp1[u][fight_time[u]] = weight[u];
        dp2[u][fight_time[u]] = weight[u];
    }
    for (int e = head[u]; e; e = edge[e].next) {
        int v = edge[e].to;
        ll c = edge[e].cost;
        if (v == parent) continue;
        dfs(v, u);
        // 把 u 现有的状态誊进 buf：本轮只从旧状态出发，保证 v 不会被同一个儿子用两次
        for (int j = 0; j <= T; j++) {
            buf0[j] = dp0[u][j];
            buf1[j] = dp1[u][j];
            buf2[j] = dp2[u][j];
        }
        for (int k = fight_time[u]; k <= T; k++) { // k：进 v 之前已经花掉的时间
            ll a0 = dp0[u][k], a1 = dp1[u][k], a2 = dp2[u][k];
            if (a0 <= NEG / 2 && a1 <= NEG / 2 && a2 <= NEG / 2) continue; // 该耗时不可达
            // 接法一：单程进 v（腿数 +1），耗时 k + c + shen
            for (int shen = 0; k + c + shen <= T; shen++) {
                if (dp1[v][shen] <= NEG / 2) continue;
                int j = k + c + shen;
                buf1[j] = max(buf1[j], a0 + dp1[v][shen]); // 原先 0 条腿 -> 1 条
                buf2[j] = max(buf2[j], a1 + dp1[v][shen]); // 原先 1 条腿 -> 2 条
            }
            // 接法二/三：往返进 v（边 (u,v) 走两次），耗时 k + 2c + shen
            for (int shen = 0; k + 2 * c + shen <= T; shen++) {
                int j = k + 2 * c + shen;
                if (dp0[v][shen] > NEG / 2) { // v 内部自己往返：腿数不变
                    buf0[j] = max(buf0[j], a0 + dp0[v][shen]);
                    buf1[j] = max(buf1[j], a1 + dp0[v][shen]);
                    buf2[j] = max(buf2[j], a2 + dp0[v][shen]);
                }
                if (dp2[v][shen] > NEG / 2) // v 内部有两条腿：腿数 +2，只能从 0 条腿的状态接
                    buf2[j] = max(buf2[j], a0 + dp2[v][shen]);
            }
        }
        for (int j = 0; j <= T; j++) { // 把合并结果写回 u
            dp0[u][j] = buf0[j];
            dp1[u][j] = buf1[j];
            dp2[u][j] = buf2[j];
        }
    }
}

int main() {
    scanf("%d %d", &n, &T);
    for (int i = 1; i <= n; i++) scanf("%lld", &weight[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &fight_time[i]);
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    for (int u = 1; u <= n; u++)
        for (int j = 0; j <= T; j++) dp0[u][j] = dp1[u][j] = dp2[u][j] = NEG;
    dfs(1, 0);
    ll ans = 0; // 一个点都去不了时武力值就是 0
    for (int u = 1; u <= n; u++)
        for (int j = 0; j <= T; j++) {
            ans = max(ans, dp0[u][j]);
            ans = max(ans, dp1[u][j]);
            ans = max(ans, dp2[u][j]);
        }
    printf("%lld\n", ans);
    return 0;
}
