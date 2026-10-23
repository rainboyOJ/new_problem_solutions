/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 15:58
 * update_at: 2026-10-23 16:24
 */
// main.cpp：Tarjan 找桥 + 缩掉边双连通分量 + 桥树上叶子数 / 2
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;  // 点数上界：题面 F <= 5e3，这里留出余量防止数据比题面更大
const int MAXM = 200005;  // 边数上界：每条无向边存两条有向边，题面 R <= 1e4

ll n, m;

// 链式前向星存图：无向边按 (2k, 2k+1) 成对存放，i ^ 1 就是 i 的反向边
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

int dfn[MAXN], low[MAXN], dfs_clock;  // Tarjan 的时间戳数组
bool is_bridge[MAXM];                 // is_bridge[i]：第 i 条有向边（以及它的反向边）是桥

int comp[MAXN];      // comp[u]：点 u 属于哪个边双连通分量（缩点后的编号）
int comp_cnt;        // 边双连通分量个数，也就是桥树的点数
int comp_deg[MAXN];  // comp_deg[c]：缩点后分量 c 在桥树上的度数

// 加一条 u -> v 的有向边
void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// Tarjan 求桥。
// in_edge 是从父节点进入 u 的那条边的编号；
// 因为可能有重边，不能只跳过“父节点”，必须只跳过这条边的反向边。
void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++dfs_clock;

    for (int i = head[u]; i != -1; i = nxt[i]) {
        if (i == (in_edge ^ 1)) {
            continue;  // 这条边就是进来的那条边的反向边，跳过
        }
        int v = to[i];

        if (dfn[v] == 0) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            // v 这棵子树回不到 u 或 u 的祖先，说明 u-v 是桥
            if (low[v] > dfn[u]) {
                is_bridge[i] = true;
                is_bridge[i ^ 1] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 忽略所有桥做 DFS 染色，得到边双连通分量编号
void dfs_comp(int u) {
    comp[u] = comp_cnt;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        if (is_bridge[i]) {
            continue;
        }
        int v = to[i];
        if (comp[v] == 0) {
            dfs_comp(v);
        }
    }
}

void solve() {
    for (ll u = 1; u <= n; u++) {
        if (dfn[u] == 0) {
            tarjan(u, -1);
        }
    }

    for (ll u = 1; u <= n; u++) {
        if (comp[u] == 0) {
            comp_cnt++;
            dfs_comp(u);
        }
    }

    // 统计桥树每个点的度数：每条桥给它两端的边双各贡献 1 度
    for (ll u = 1; u <= n; u++) {
        for (int i = head[u]; i != -1; i = nxt[i]) {
            if (is_bridge[i]) {
                comp_deg[comp[u]]++;
            }
        }
    }

    // 桥树上度数为 1 的点就是叶子，答案是把叶子两两配对所需的最少新边数
    ll leaf = 0;
    for (ll c = 1; c <= comp_cnt; c++) {
        if (comp_deg[c] == 1) {
            leaf++;
        }
    }

    ll ans = (leaf + 1) / 2;  // 叶子数为 0（原图已经是边双连通）时答案正好是 0
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (ll i = 1; i <= m; i++) {
        ll u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    solve();

    return 0;
}
