/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:05
 * update_at: 2026-11-11 00:05
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 500005;
const int MAXM = 1000005;

struct Edge {
    int to;
    int id;
};

vector<Edge> g[MAXN];
vector<int> tree[MAXN];

// Tarjan 边双连通分量
int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
int dcc[MAXN], dcc_cnt;
bool is_bridge[MAXM];

// 每个缩点的点数与内部边数
int dcc_v[MAXN];
int dcc_e[MAXN];

// 子树边数
int s_e[MAXN];

// 2 的幂次
ll pow2[MAXM];

// 树形 DP
ll f[MAXN][2];
ll ans = 0;
int total_m;

void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;

    for (const auto& e : g[u]) {
        if (e.id == in_edge) continue;
        int v = e.to;
        if (!dfn[v]) {
            tarjan(v, e.id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                is_bridge[e.id] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        dcc_cnt++;
        while (true) {
            int x = stk[top--];
            dcc[x] = dcc_cnt;
            dcc_v[dcc_cnt]++;
            if (x == u) break;
        }
    }
}

// 预处理子树内部边数
void dfs_edge_count(int u, int fa) {
    s_e[u] = dcc_e[u];
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs_edge_count(v, u);
        s_e[u] += s_e[v] + 1; // +1 为桥边 (u, v)
    }
}

// 树形 DP 求解
void dfs_dp(int u, int fa) {
    // 初始状态（只考虑自身分量）
    f[u][0] = pow2[dcc_e[u]];
    f[u][1] = (pow2[dcc_v[u]] - 1 + MOD) % MOD * pow2[dcc_e[u]] % MOD;

    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs_dp(v, u);

        ll new_f0 = f[u][0] * (2 * f[v][0] % MOD) % MOD;
        ll new_f1 = (f[u][1] * ((2 * f[v][0] % MOD + f[v][1]) % MOD) % MOD +
                     f[u][0] * f[v][1] % MOD) % MOD;

        f[u][0] = new_f0;
        f[u][1] = new_f1;
    }

    // 统计以 u 为所有军营的 LCA 时的贡献
    if (u == 1) {
        ans = (ans + f[u][1]) % MOD;
    } else {
        // 外界未确定的边数为 total_m - s_e[u] - 1
        ll ext_ways = pow2[total_m - s_e[u] - 1];
        ans = (ans + f[u][1] * ext_ways) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    total_m = m;

    pow2[0] = 1;
    for (int i = 1; i <= m; ++i) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }

    vector<pair<int, int>> edges(m + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        edges[i] = {u, v};
    }

    // 边双缩点
    tarjan(1, 0);

    // 统计各缩点内部边数与建立缩点树
    for (int i = 1; i <= m; ++i) {
        int u = dcc[edges[i].first];
        int v = dcc[edges[i].second];
        if (u == v) {
            dcc_e[u]++;
        } else {
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
    }

    // DFS 预处理子树边数
    dfs_edge_count(1, 0);

    // 树形 DP
    dfs_dp(1, 0);

    cout << ans << "\n";

    return 0;
}
