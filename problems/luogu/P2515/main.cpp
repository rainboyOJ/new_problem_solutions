/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:30
 * update_at: 2026-10-23 23:30
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 105;
const int MAXM = 505;

ll n, m;
ll w[MAXN], v[MAXN], d[MAXN];

// 原图邻接表（d[i] -> i，表示选了 d[i] 才能选 i）
int head[MAXN], to_e[MAXN], nxt[MAXN], edge_cnt;

void add_edge(int u, int to) {
    edge_cnt++;
    to_e[edge_cnt] = to;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// Tarjan 相关
int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
bool in_stack[MAXN];
int scc_id[MAXN], scc_cnt;
ll scc_w[MAXN], scc_v[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    in_stack[u] = true;

    for (int e = head[u]; e; e = nxt[e]) {
        int v_node = to_e[e];
        if (!dfn[v_node]) {
            tarjan(v_node);
            low[u] = min(low[u], low[v_node]);
        } else if (in_stack[v_node]) {
            low[u] = min(low[u], dfn[v_node]);
        }
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int cur = stk[top--];
            in_stack[cur] = false;
            scc_id[cur] = scc_cnt;
            scc_w[scc_cnt] += w[cur];
            scc_v[scc_cnt] += v[cur];
            if (cur == u) break;
        }
    }
}

// 缩点后新图的树边（从父亲到儿子）
int head_tree[MAXN], to_tree[MAXN * MAXN], nxt_tree[MAXN * MAXN], tree_edge_cnt;
int in_deg[MAXN];
bool has_edge[MAXN][MAXN];

void add_tree_edge(int u, int to) {
    tree_edge_cnt++;
    to_tree[tree_edge_cnt] = to;
    nxt_tree[tree_edge_cnt] = head_tree[u];
    head_tree[u] = tree_edge_cnt;
}

// 树上背包 DP
// dp[u][j] 表示在以 u 为根的子树中选择，占用容量不超过 j 获得的最大价值
ll dp[MAXN][MAXM];

void dfs_dp(int u) {
    // 必须选 u 才能选其子树
    for (int j = scc_w[u]; j <= m; ++j) {
        dp[u][j] = scc_v[u];
    }

    for (int e = head_tree[u]; e; e = nxt_tree[e]) {
        int to = to_tree[e];
        dfs_dp(to);

        // 分组背包：倒序枚举背包容量，防止重复使用子树
        for (int j = m; j >= scc_w[u]; --j) {
            for (int k = 0; k <= j - scc_w[u]; ++k) {
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[to][k]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
        if (d[i] != 0) {
            // 建原图依赖边：i 依赖 d[i]，即 d[i] -> i，表示前置为 d[i]
            // 为了找强连通分量，有向环在 d[i] -> i 或 i -> d[i] 下是等价的（只是环的方向反转）
            add_edge(d[i], i);
        }
    }

    // 1. Tarjan 缩点求强连通分量
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 2. 建立缩点后的 DAG，并接入虚拟根 0
    for (int i = 1; i <= n; ++i) {
        if (d[i] != 0) {
            int u_scc = scc_id[d[i]];
            int v_scc = scc_id[i];
            if (u_scc != v_scc && !has_edge[u_scc][v_scc]) {
                has_edge[u_scc][v_scc] = true;
                add_tree_edge(u_scc, v_scc);
                in_deg[v_scc]++;
            }
        }
    }

    // 入度为 0 的 SCC 挂在虚拟根 0 下（包括孤立环与依赖 0 的点）
    for (int i = 1; i <= scc_cnt; ++i) {
        if (in_deg[i] == 0) {
            add_tree_edge(0, i);
        }
    }

    // 虚拟根 0 本身体积 0，价值 0
    scc_w[0] = 0;
    scc_v[0] = 0;

    // 3. 树上背包 DP
    dfs_dp(0);

    cout << dp[0][m] << "\n";

    return 0;
}
