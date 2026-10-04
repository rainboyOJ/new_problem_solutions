/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:28
 * update_at: 2026-10-05 07:28
 */

// 挖地雷：DAG 上求点权和最大的路径，倒序线性 DP 并记录后继还原路径。
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 205;

int n;                    // 地窖个数
int a[MAXN];              // a[i]：第 i 个地窖中地雷的个数
bool edge[MAXN][MAXN];    // edge[u][v]：u 到 v 是否有单向通路
ll dp[MAXN];              // dp[u]：从 u 出发一直挖到无路可走能挖到的最多地雷数
int nxt[MAXN];            // nxt[u]：最优路径中 u 的下一个地窖编号，0 表示无路可走

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    // 读边直到 "0 0"，注意是 0 0 而不是 EOF
    int x, y;
    while (scanf("%d %d", &x, &y) == 2) {
        if (x == 0 && y == 0) {
            break;
        }
        edge[x][y] = true;
    }

    // 从大到小逆序 DP：u 的所有后继都比 u 大，此时 dp[v] 已算好
    for (int u = n; u >= 1; --u) {
        dp[u] = a[u];
        nxt[u] = 0;
        for (int v = u + 1; v <= n; ++v) {
            if (edge[u][v] && dp[u] < a[u] + dp[v]) {
                dp[u] = a[u] + dp[v];
                nxt[u] = v;
            }
        }
    }

    // 全局最优起点：dp 最大的那个
    int start = 1;
    for (int i = 2; i <= n; ++i) {
        if (dp[i] > dp[start]) {
            start = i;
        }
    }

    // 沿 nxt 数组输出挖地雷的顺序
    printf("%d", start);
    for (int u = nxt[start]; u != 0; u = nxt[u]) {
        printf("-%d", u);
    }
    printf("\n%lld\n", dp[start]);

    return 0;
}
