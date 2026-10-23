/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 02:28
 * update_at: 2026-10-23 22:33
 */
// P3469 [POI 2008] BLO-Blockade
// 割点 + 子树大小统计，计算封锁每个点后的作废访问数
// 核心：Tarjan 求割点时顺手统计被切下的子树大小，answer[u] = 2*(n-1) + 跨块损失
#include <bits/stdc++.h>
using namespace std;

// 邻接表存图：to 为邻居编号，rev 为反向边在邻接表中的下标（用于跳过父边）
struct Edge {
    int to, rev;
};

const int MAXN = 100005;

int n, m;
vector<Edge> g[MAXN];          // 邻接表

int dfn[MAXN], low[MAXN];      // Tarjan 时间戳 / 能回溯到的最小 dfn
int parent_node[MAXN];         // DFS 树上的父节点
int parent_rev[MAXN];          // 父边反向边在 g[u] 中的下标，用于跳过
int sub_size[MAXN];            // 以 u 为根的子树大小
int child_cnt[MAXN];           // DFS 树上 u 的儿子个数
int dfs_clock;                 // 时间戳计数器

long long cut_sum[MAXN];       // 已被割下的子树块大小之和
long long answer[MAXN];        // 封锁 u 后无法发生的有序访问次数

// 加无向边 (u, v)，rev 互相记录反向边位置
void add_edge(int u, int v) {
    g[u].push_back({v, (int)g[v].size()});
    g[v].push_back({u, (int)g[u].size() - 1});
}

// Tarjan 求割点，同时统计每个点的作废访问数
void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    sub_size[u] = 1;
    child_cnt[u] = 0;
    cut_sum[u] = 0;
    answer[u] = 2LL * (n - 1);  // 固定损失：封锁 u 后 u 与外界的 2*(n-1) 次访问全部作废

    for (int i = 0; i < (int)g[u].size(); i++) {
        if (i == parent_rev[u]) continue;  // 跳过回到父节点的反向边
        int v = g[u][i].to;

        if (!dfn[v]) {
            // 树边：递归处理子节点 v
            parent_node[v] = u;
            parent_rev[v] = g[u][i].rev;
            child_cnt[u]++;
            tarjan(v);

            sub_size[u] += sub_size[v];
            low[u] = min(low[u], low[v]);

            // 若 v 子树无法回溯到 u 之前，则删除 u 后 v 子树单独成块
            // 此时 v 子树与 u 的 cut_sum 块之间产生跨块损失
            if (low[v] >= dfn[u]) {
                answer[u] += 2LL * cut_sum[u] * sub_size[v];
                cut_sum[u] += sub_size[v];
            }
        } else if (dfn[v] < dfn[u]) {
            // 后向边：更新 low（只考虑 dfn 比 u 小的，即祖先方向）
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 补上"剩余大块"（u 的祖先方向 + 可回溯子树）与已切下块之间的跨块损失
    answer[u] += 2LL * cut_sum[u] * (n - 1 - cut_sum[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            parent_node[i] = 0;
            parent_rev[i] = -1;
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
