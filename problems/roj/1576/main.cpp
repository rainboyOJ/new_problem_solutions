/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:41
 * update_at: 2026-10-05 09:41
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXM = 305;   // 课程数上限
const int MAXN = 305;   // 可选课程数上限
const ll NEG = -1e18;   // 不可达方案标记

// pre[i]   : 课 i 的先修课号（0 表示无先修课，即挂在虚拟根 0 下）
// credit[i]: 课 i 的学分，credit[0] = 0（虚拟根不占名额、不计学分）
int pre[MAXM], credit[MAXM];
// g[u][0..g_cnt[u]-1]：节点 u 的孩子列表（选了 u 才有资格选孩子）
int g[MAXM][MAXM], g_cnt[MAXM];

int m, n;                // 待选课程数 / 可选课程数
ll dp[MAXM][MAXN];       // dp[u][k]：子树 u 中选 k 门课（选课必含 u）的最大学分
ll best[MAXN];           // pack_child 与父层交换结果的方案表

// 用父层方案表 f 与孩子 v 的方案表 dv 合并：best[a+b] = max(f[a] + dv[b])
// f 是父层的局部数组，防止递归中全局 best 被孩子层覆盖
void pack_child(const ll f[], const ll dv[], int cap) {
    static ll tmp[MAXN]; // 合并结果临时表
    for (int a = 0; a <= cap; a++) tmp[a] = NEG;
    // a = 子树 u 中除 v 外已选门数，b = v 子树中选的门数
    for (int a = 0; a <= cap; a++) {
        if (f[a] == NEG) continue;
        for (int b = 0; a + b <= cap; b++) {
            if (dv[b] == NEG) continue;
            if (f[a] + dv[b] > tmp[a + b])
                tmp[a + b] = f[a] + dv[b];
        }
    }
    for (int a = 0; a <= cap; a++) best[a] = tmp[a];
}

// 计算子树 u 的方案表 dp[u][0..n]：选 k 门课的最大学分，选课必含 u
void dfs(int u) {
    ll cur[MAXN]; // 本层方案表（局部保存，避免被孩子递归覆盖）
    // 初始只含 u 自己（虚拟根 0 学分为 0 且不占名额，从 cur[0] 出发）
    for (int k = 0; k <= n; k++) cur[k] = NEG;
    if (u == 0) cur[0] = 0;
    else cur[1] = credit[u];

    for (int i = 0; i < g_cnt[u]; i++) { // 逐个孩子卷积合并
        int v = g[u][i];
        dfs(v);
        pack_child(cur, dp[v], n);
        for (int k = 0; k <= n; k++) cur[k] = best[k];
    }

    cur[0] = 0; // 一门不选恒合法，供父节点表示"跳过该子树"
    for (int k = 0; k <= n; k++) dp[u][k] = cur[k];
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &pre[i], &credit[i]);
        g_cnt[pre[i]]++;              // 先修为 0 的课挂在虚拟根 0 下
        g[pre[i]][g_cnt[pre[i]] - 1] = i; // 先修课号可能大于本课号，不能依赖输入顺序
    }
    dfs(0);
    // 学分全为正，任何 k < n 门的方案都能再补一门课，"恰好 n 门"与"至多 n 门"等价
    printf("%lld\n", dp[0][n]);
    return 0;
}
